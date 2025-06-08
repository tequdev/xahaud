#!/bin/bash 
# We use set -e and bash with -u to bail on first non zero exit code of any
# processes launched or upon any unbound variable.
# We use set -x to print commands before running them to help with
# debugging.

echo "START BUILDING (HOST)"

echo "Cleaning previously built binary"
rm -f release-build/xahaud

BUILD_CORES=$(echo "scale=0 ; `nproc` / 1.337" | bc)

if [[ "$GITHUB_REPOSITORY" == "" ]]; then
  #Default
  BUILD_CORES=8
fi

# Ensure still works outside of GH Actions by setting these to /dev/null
# GA will run this script and then delete it at the end of the job
JOB_CLEANUP_SCRIPT=${JOB_CLEANUP_SCRIPT:-/dev/null}
NORMALIZED_WORKFLOW=$(echo "$GITHUB_WORKFLOW" | tr -c 'a-zA-Z0-9' '-')
NORMALIZED_REF=$(echo "$GITHUB_REF" | tr -c 'a-zA-Z0-9' '-')
CONTAINER_NAME="xahaud_cached_builder_${NORMALIZED_WORKFLOW}-${NORMALIZED_REF}"

echo "-- BUILD CORES:       $BUILD_CORES"
echo "-- GITHUB_REPOSITORY: $GITHUB_REPOSITORY"
echo "-- GITHUB_SHA:        $GITHUB_SHA"
echo "-- GITHUB_RUN_NUMBER: $GITHUB_RUN_NUMBER"
echo "-- CONTAINER_NAME:    $CONTAINER_NAME"

which docker 2> /dev/null 2> /dev/null
if [ "$?" -eq "1" ]
then
  echo 'Docker not found. Install it first.'
  exit 1
fi

stat .git 2> /dev/null 2> /dev/null
if [ "$?" -eq "1" ]
then
  echo 'Run this inside the source directory. (.git dir not found).'
  exit 1
fi

STATIC_CONTAINER=$(docker ps -a | grep $CONTAINER_NAME |wc -l)

# if [[ "$STATIC_CONTAINER" -gt "0" && "$GITHUB_REPOSITORY" != "" ]]; then
if false; then
  echo "Static container, execute in static container to have max. cache"
  docker start $CONTAINER_NAME
  docker exec -i $CONTAINER_NAME /hbb_exe/activate-exec bash -c "source /opt/rh/gcc-toolset-10/enable && bash -x /io/build-core.sh '$GITHUB_REPOSITORY' '$GITHUB_SHA' '$BUILD_CORES' '$GITHUB_RUN_NUMBER'"
  docker stop $CONTAINER_NAME
else
  echo "No static container, build on temp container"
  rm -rf release-build;
  mkdir -p release-build;

  docker volume create cache-volume

  # Create inline Dockerfile with environment setup for build-full.sh
  DOCKERFILE_CONTENT=$(cat <<'DOCKERFILE_EOF'
FROM ghcr.io/phusion/holy-build-box:4.0.1-amd64

ARG BUILD_CORES=8

# Enable repositories and install dependencies
RUN /hbb_exe/activate-exec dnf install -y epel-release && \
    /hbb_exe/activate-exec dnf config-manager --set-enabled powertools || /hbb_exe/activate-exec dnf config-manager --set-enabled crb && \
    /hbb_exe/activate-exec dnf install -y \
    wget lz4 lz4-devel git gcc-toolset-10-binutils zlib-static ncurses-devel \
    gcc-toolset-10-gcc-c++ \
    snappy snappy-devel \
    zlib zlib-devel \
    lz4-devel \
    libasan \
    python3 python3-pip \
    ccache \
    ninja-build \
    patch \
    gcc-toolset-10-libatomic-devel \
    glibc-devel \
    libxml2-devel \
    glibc-static \
    autoconf \
    automake \
    libtool

# Build static ncurses/tinfo library
RUN /hbb_exe/activate-exec bash -c "source /opt/rh/gcc-toolset-10/enable && \
    cd /tmp && \
    wget -q https://ftp.gnu.org/gnu/ncurses/ncurses-6.3.tar.gz && \
    tar -xzf ncurses-6.3.tar.gz && \
    cd ncurses-6.3 && \
    ./configure --prefix=/usr --libdir=/usr/lib64 --enable-static --disable-shared --without-cxx-binding --without-ada --without-manpages --without-progs --without-tests && \
    make -j\$(nproc) && \
    make install && \
    [ -f /usr/lib64/libncurses.a ] && ln -sf /usr/lib64/libncurses.a /usr/lib64/libtinfo.a || \
    [ -f /usr/lib/libncurses.a ] && cp /usr/lib/libncurses.a /usr/lib64/libtinfo.a || \
    ar rcs /usr/lib64/libtinfo.a && \
    cd /tmp && \
    rm -rf ncurses-6.3 ncurses-6.3.tar.gz"

# Install Conan and CMake
RUN /hbb_exe/activate-exec pip3 install "conan==1.66.0" && \
    /hbb_exe/activate-exec wget -q https://github.com/Kitware/CMake/releases/download/v3.23.1/cmake-3.23.1-linux-x86_64.tar.gz && \
    /hbb_exe/activate-exec tar -xzf cmake-3.23.1-linux-x86_64.tar.gz --strip-components=1 -C /usr/local && \
    rm cmake-3.23.1-linux-x86_64.tar.gz

# Install Boost 1.86.0
RUN /hbb_exe/activate-exec bash -c "cd /tmp && \
    wget -q https://archives.boost.io/release/1.86.0/source/boost_1_86_0.tar.gz && \
    tar -xzf boost_1_86_0.tar.gz && \
    cd boost_1_86_0 && \
    ./bootstrap.sh && \
    ./b2 link=static -j${BUILD_CORES} && \
    ./b2 install && \
    cd /tmp && \
    rm -rf boost_1_86_0 boost_1_86_0.tar.gz"

# Build LLVM 13
RUN bash -c "source /opt/rh/gcc-toolset-10/enable && \
    export CC=gcc CXX=g++ && \
    unset CFLAGS CXXFLAGS LDFLAGS && \
    cd /tmp && \
    wget -nc -q https://github.com/llvm/llvm-project/releases/download/llvmorg-13.0.1/llvm-13.0.1.src.tar.xz && \
    tar -xf llvm-13.0.1.src.tar.xz && \
    cd llvm-13.0.1.src && \
    mkdir -p build && \
    cd build && \
    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/usr/lib64/llvm13 \
        -DLLVM_BUILD_LLVM_CONFIG=ON \
        -DLLVM_INSTALL_UTILS=ON \
        -DLLVM_INCLUDE_TESTS=OFF \
        -DLLVM_INCLUDE_BENCHMARKS=OFF \
        -DLLVM_BUILD_TESTS=OFF \
        -DLLVM_BUILD_BENCHMARKS=OFF \
        -DLLVM_BUILD_RUNTIME=OFF \
        -DLLVM_BUILD_DOCS=OFF && \
    make -j\$(nproc) install && \
    ln -sf /usr/lib64/llvm13/bin/llvm-config /usr/bin/llvm-config && \
    ln -sf /usr/lib64/llvm13/bin/llvm-config /usr/bin/llvm-config-13"

# Build LLD with libunwind
RUN /hbb_exe/activate-exec bash -c "source /opt/rh/gcc-toolset-10/enable && \
    cd /tmp && \
    wget -nc -q https://github.com/llvm/llvm-project/releases/download/llvmorg-13.0.1/lld-13.0.1.src.tar.xz && \
    wget -nc -q https://github.com/llvm/llvm-project/releases/download/llvmorg-13.0.1/libunwind-13.0.1.src.tar.xz && \
    tar -xf lld-13.0.1.src.tar.xz && \
    tar -xf libunwind-13.0.1.src.tar.xz && \
    cp -r libunwind-13.0.1.src/include libunwind-13.0.1.src/src lld-13.0.1.src/ && \
    cd lld-13.0.1.src && \
    mkdir -p build && \
    cd build && \
    cmake .. -DLLVM_LIBRARY_DIR=/usr/lib64/llvm13/lib/ -DCMAKE_INSTALL_PREFIX=/usr/lib64/llvm13/ -DCMAKE_BUILD_TYPE=Release -DLLVM_CONFIG_PATH=/usr/lib64/llvm13/bin/llvm-config && \
    make -j\$(nproc) install && \
    ln -s /usr/lib64/llvm13/lib/include/lld /usr/include/lld && \
    cp /usr/lib64/llvm13/lib/liblld*.a /usr/local/lib/ && \
    cd ../../ && \
    rm -rf lld-13.0.1.src libunwind-13.0.1.src *.tar.xz"

# Build and install WasmEdge
RUN cd /tmp && \
    git clone --branch 0.11.2 --depth 1 https://github.com/WasmEdge/WasmEdge.git && \
    cd WasmEdge && \
    mkdir -p build && \
    cd build && \
    export BOOST_ROOT='/usr/local/src/boost_1_86_0' && \
    export Boost_LIBRARY_DIRS='/usr/local/lib' && \
    export BOOST_INCLUDEDIR='/usr/local/src/boost_1_86_0' && \
    /hbb_exe/activate-exec bash -c "source /opt/rh/gcc-toolset-10/enable && \
    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/usr/local \
        -DWASMEDGE_BUILD_SHARED_LIB=OFF \
        -DWASMEDGE_BUILD_STATIC_LIB=ON \
        -DWASMEDGE_BUILD_AOT_RUNTIME=ON \
        -DWASMEDGE_FORCE_DISABLE_LTO=ON \
        -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
        -DWASMEDGE_LINK_LLVM_STATIC=ON \
        -DWASMEDGE_BUILD_PLUGINS=OFF \
        -DWASMEDGE_BUILD_TOOLS=ON \
        -DWASMEDGE_LINK_TOOLS_STATIC=ON \
        -DBoost_NO_BOOST_CMAKE=ON \
        -DLLVM_DIR=/usr/lib64/llvm13/lib/cmake/llvm/ \
        -DLLVM_LIBRARY_DIR=/usr/lib64/llvm13/lib/ \
        -DCMAKE_CXX_FLAGS='-Wno-error=clobbered -Wno-clobbered' && \
    make -j\$(nproc) install" && \
    cp -r include/api/wasmedge /usr/include/ && \
    rm -rf WasmEdge

# Set environment variables
ENV PATH=/usr/local/bin:$PATH
ENV CC='ccache gcc'
ENV CXX='ccache g++'
ENV LLVM_DIR=/usr/lib64/llvm13/lib/cmake/llvm
ENV WasmEdge_LIB=/usr/local/lib64/libwasmedge.a
ENV BOOST_ROOT=/usr/local/src/boost_1_86_0
ENV Boost_LIBRARY_DIRS=/usr/local/lib
ENV BOOST_INCLUDEDIR=/usr/local/src/boost_1_86_0

# Configure ccache and Conan
RUN /hbb_exe/activate-exec ccache -M 10G && \
    /hbb_exe/activate-exec ccache -o cache_dir=/cache/ccache && \
    /hbb_exe/activate-exec bash -c "conan config set storage.path=/cache/conan && \
    (conan profile new default --detect || true) && \
    conan profile update settings.compiler.cppstd=20 default"

DOCKERFILE_EOF
)

  # Build custom Docker image
  IMAGE_NAME="xahaud-builder:latest"
  echo "Building custom Docker image with dependencies..."
  echo "$DOCKERFILE_CONTENT" | docker build --build-arg BUILD_CORES="$BUILD_CORES" -t "$IMAGE_NAME" - || exit 1

  if [[ "$GITHUB_REPOSITORY" == "" ]]; then
    # Non GH, local building
    echo "Non-GH runner, local building, temp container"
    docker run -i --user 0:$(id -g) --rm -v /data/builds:/data/builds -v `pwd`:/io -v cache-volume:/cache --network host "$IMAGE_NAME" /hbb_exe/activate-exec bash -c "source /opt/rh/gcc-toolset-10/enable && bash -x /io/build-full.sh '$GITHUB_REPOSITORY' '$GITHUB_SHA' '$BUILD_CORES' '$GITHUB_RUN_NUMBER'"
  else
    # GH Action, runner
    echo "GH Action, runner, clean & re-create create persistent container"
    docker rm -f $CONTAINER_NAME
    echo "echo 'Stopping container: $CONTAINER_NAME'" >> "$JOB_CLEANUP_SCRIPT"
    echo "docker stop --time=15 \"$CONTAINER_NAME\" || echo 'Failed to stop container or container not running'" >> "$JOB_CLEANUP_SCRIPT"
    docker run -di --user 0:$(id -g) --name $CONTAINER_NAME -v /data/builds:/data/builds -v `pwd`:/io -v cache-volume:/cache --network host "$IMAGE_NAME" /hbb_exe/activate-exec bash
    docker exec -i $CONTAINER_NAME /hbb_exe/activate-exec bash -c "source /opt/rh/gcc-toolset-10/enable && bash -x /io/build-full.sh '$GITHUB_REPOSITORY' '$GITHUB_SHA' '$BUILD_CORES' '$GITHUB_RUN_NUMBER'"
    docker stop $CONTAINER_NAME
  fi
fi

echo "DONE BUILDING (HOST)"
