#!/bin/bash -u
# We use set -e and bash with -u to bail on first non zero exit code of any
# processes launched or upon any unbound variable.
# We use set -x to print commands before running them to help with
# debugging.
set -e

echo "START INSIDE CONTAINER - FULL"

echo "-- BUILD CORES:       $3"
echo "-- GITHUB_REPOSITORY: $1"
echo "-- GITHUB_SHA:        $2"
echo "-- GITHUB_RUN_NUMBER: $4"

umask 0000;

####

cd /io;
mkdir -p src/certs;
curl --silent -k https://raw.githubusercontent.com/RichardAH/rippled-release-builder/main/ca-bundle/certbundle.h -o src/certs/certbundle.h;
if [ "`grep certbundle.h src/ripple/net/impl/RegisterSSLCerts.cpp | wc -l`" -eq "0" ]
then
    cp src/ripple/net/impl/RegisterSSLCerts.cpp src/ripple/net/impl/RegisterSSLCerts.cpp.old
    perl -i -pe "s/^{/{
    #ifdef EMBEDDED_CA_BUNDLE
    BIO *cbio = BIO_new_mem_buf(ca_bundle.data(), ca_bundle.size());
    X509_STORE  *cts = SSL_CTX_get_cert_store(ctx.native_handle());
    if(!cts || !cbio)
        JLOG(j.warn())
            << \"Failed to create cts\/cbio when loading embedded certs.\";
    else
    {
        X509_INFO *itmp;
        int i, count = 0, type = X509_FILETYPE_PEM;
        STACK_OF(X509_INFO) *inf = PEM_X509_INFO_read_bio(cbio, NULL, NULL, NULL);

        if (!inf)
        {
            BIO_free(cbio);
            JLOG(j.warn())
                << \"Failed to read cbio when loading embedded certs.\";
        }
        else
        {
            for (i = 0; i < sk_X509_INFO_num(inf); i++)
            {
                itmp = sk_X509_INFO_value(inf, i);
                if (itmp->x509)
                {
                      X509_STORE_add_cert(cts, itmp->x509);
                      count++;
                }
                if (itmp->crl)
                {
                      X509_STORE_add_crl(cts, itmp->crl);
                      count++;
                }
            }
            sk_X509_INFO_pop_free(inf, X509_INFO_free);
            BIO_free(cbio);
        }
    }
    #endif/g" src/ripple/net/impl/RegisterSSLCerts.cpp &&
    sed -i "s/#include <ripple\/net\/RegisterSSLCerts.h>/\0\n#include <certs\/certbundle.h>/g" src/ripple/net/impl/RegisterSSLCerts.cpp
fi
# Enable EPEL and PowerTools/CRB repositories
dnf install -y epel-release
dnf config-manager --set-enabled powertools || dnf config-manager --set-enabled crb
# Install dependencies using dnf and gcc-toolset-10
dnf install -y wget lz4 lz4-devel git llvm-static llvm-devel gcc-toolset-10-binutils zlib-static ncurses-devel \
  gcc-toolset-10-gcc-c++ \
  snappy snappy-devel \
  zlib zlib-devel \
  lz4-devel \
  libasan
source /opt/rh/gcc-toolset-10/enable
echo "-- Install Conan 1.66.0 --" &&
dnf install -y python3 python3-pip && # Use dnf and add python3-pip
pip3 install "conan==1.66.0" &&
conan config set storage.path=/cache/conan &&
(conan profile new default --detect || true) &&
conan profile update settings.compiler.cppstd=20 default &&
echo "-- Install Cmake 3.23.1 --" &&
pwd &&
( wget -nc -q https://github.com/Kitware/CMake/releases/download/v3.23.1/cmake-3.23.1-linux-x86_64.tar.gz; echo "" ) &&
# Extract CMake to /usr/local and add to PATH
tar -xzf cmake-3.23.1-linux-x86_64.tar.gz --strip-components=1 -C /usr/local &&
export PATH=/usr/local/bin:$PATH
echo "-- Install ccache --" &&
dnf install -y ccache &&
ccache -M 10G &&
ccache -o cache_dir=/cache/ccache &&
export CC='ccache gcc' &&
export CXX='ccache g++' &&
echo "-- Build Rippled --" &&
pwd &&
cp Builds/CMake/deps/Rocksdb.cmake Builds/CMake/deps/Rocksdb.cmake.old &&

echo "MOVING TO [ build-core.sh ]";

printenv > .env.temp;
cat .env.temp | grep '=' | sed s/\\\(^[^=]\\+=\\\)/\\1\\\"/g|sed s/\$/\\\"/g > .env;
rm .env.temp;

echo "Persisting ENV:"
cat .env

./build-core.sh "$1" "$2" "$3" "$4"

echo $?
if [[ "$?" -ne "0" ]]; then
  echo "ERR build-core.sh non 0 exit code"
  exit 127
fi

echo "END [ build-core.sh ]"

echo "END INSIDE CONTAINER - FULL"

echo "-- Built with env vars:"
