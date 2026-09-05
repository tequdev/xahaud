/**
 * HookAPICost benchmark hooks (Phase 1).
 *
 * One section of this file is compiled per invocation of build.sh, selected
 * by a single -DB_<name> define. Each section provides a `hook()` entry
 * point that either runs a bounded loop (reading the iteration count N from
 * a 4-byte big-endian HookParameter named "N") or, for the terminal
 * variants (accept0/rollback0/noexit), does a single fixed thing.
 *
 * See docs/hook-api-cost/DESIGN.md sections 2 and 3 for the measurement
 * this feeds.
 */
#include "hookapi.h"

/* Phase 2: raw-serialize helpers for the emit family. */

#define atACCOUNT 1U
#define atDESTINATION 3U
#define ENCODE_DROPS_SIZE 9
#define ENCODE_DROPS(buf_out, drops, amount_type)                \
    {                                                            \
        uint8_t uat = amount_type;                               \
        uint64_t udrops = drops;                                 \
        buf_out[0] = 0x60U + (uat & 0x0FU);                      \
        buf_out[1] = 0b01000000 + ((udrops >> 56) & 0b00111111); \
        buf_out[2] = (udrops >> 48) & 0xFFU;                     \
        buf_out[3] = (udrops >> 40) & 0xFFU;                     \
        buf_out[4] = (udrops >> 32) & 0xFFU;                     \
        buf_out[5] = (udrops >> 24) & 0xFFU;                     \
        buf_out[6] = (udrops >> 16) & 0xFFU;                     \
        buf_out[7] = (udrops >> 8) & 0xFFU;                      \
        buf_out[8] = (udrops >> 0) & 0xFFU;                      \
        buf_out += ENCODE_DROPS_SIZE;                            \
    }
#define _06_01_ENCODE_DROPS_AMOUNT(buf_out, drops) \
    ENCODE_DROPS(buf_out, drops, 1U);
#define _06_08_ENCODE_DROPS_FEE(buf_out, drops) \
    ENCODE_DROPS(buf_out, drops, 8U);
#define ENCODE_TT_SIZE 3
#define _01_02_ENCODE_TT(buf_out, tt)    \
    {                                    \
        uint8_t utt = tt;                \
        buf_out[0] = 0x12U;              \
        buf_out[1] = (utt >> 8) & 0xFFU; \
        buf_out[2] = (utt >> 0) & 0xFFU; \
        buf_out += ENCODE_TT_SIZE;       \
    }
#define ENCODE_ACCOUNT_SIZE 22
#define ENCODE_ACCOUNT(buf_out, account_id, account_type) \
    {                                                     \
        uint8_t uat = account_type;                       \
        buf_out[0] = 0x80U + uat;                         \
        buf_out[1] = 0x14U;                               \
        for (int _k = 0; _k < 20; ++_k)                   \
            buf_out[2 + _k] = account_id[_k];             \
        buf_out += ENCODE_ACCOUNT_SIZE;                   \
    }
#define _08_01_ENCODE_ACCOUNT_SRC(buf_out, account_id) \
    ENCODE_ACCOUNT(buf_out, account_id, atACCOUNT);
#define _08_03_ENCODE_ACCOUNT_DST(buf_out, account_id) \
    ENCODE_ACCOUNT(buf_out, account_id, atDESTINATION);
#define ENCODE_UINT32_COMMON_SIZE 5U
#define ENCODE_UINT32_COMMON(buf_out, i, field) \
    {                                           \
        uint32_t ui = i;                        \
        uint8_t uf = field;                     \
        buf_out[0] = 0x20U + (uf & 0x0FU);      \
        buf_out[1] = (ui >> 24) & 0xFFU;        \
        buf_out[2] = (ui >> 16) & 0xFFU;        \
        buf_out[3] = (ui >> 8) & 0xFFU;         \
        buf_out[4] = (ui >> 0) & 0xFFU;         \
        buf_out += ENCODE_UINT32_COMMON_SIZE;   \
    }
#define ENCODE_UINT32_UNCOMMON_SIZE 6U
#define ENCODE_UINT32_UNCOMMON(buf_out, i, field) \
    {                                             \
        uint32_t ui = i;                          \
        uint8_t uf = field;                       \
        buf_out[0] = 0x20U;                       \
        buf_out[1] = uf;                          \
        buf_out[2] = (ui >> 24) & 0xFFU;          \
        buf_out[3] = (ui >> 16) & 0xFFU;          \
        buf_out[4] = (ui >> 8) & 0xFFU;           \
        buf_out[5] = (ui >> 0) & 0xFFU;           \
        buf_out += ENCODE_UINT32_UNCOMMON_SIZE;   \
    }
#define _02_26_ENCODE_FLS(buf_out, fls) \
    ENCODE_UINT32_UNCOMMON(buf_out, fls, 0x1A);
#define _02_27_ENCODE_LLS(buf_out, lls) \
    ENCODE_UINT32_UNCOMMON(buf_out, lls, 0x1B);
#define _02_03_ENCODE_TAG_SRC(buf_out, tag) \
    ENCODE_UINT32_COMMON(buf_out, tag, 0x3U);
#define _02_14_ENCODE_TAG_DST(buf_out, tag) \
    ENCODE_UINT32_COMMON(buf_out, tag, 0xEU);
#define _02_04_ENCODE_SEQUENCE(buf_out, sequence) \
    ENCODE_UINT32_COMMON(buf_out, sequence, 0x4U);
#define _02_02_ENCODE_FLAGS(buf_out, tag) \
    ENCODE_UINT32_COMMON(buf_out, tag, 0x2U);
#define ENCODE_SIGNING_PUBKEY_NULL_SIZE 35
#define _07_03_ENCODE_SIGNING_PUBKEY_NULL(buf_out)  \
    {                                               \
        buf_out[0] = 0x73U;                         \
        buf_out[1] = 0x21U;                         \
        for (int _k = 0; _k < 33; ++_k)             \
            buf_out[2 + _k] = 0;                    \
        buf_out += ENCODE_SIGNING_PUBKEY_NULL_SIZE; \
    }
/* 132B header (TT3+Flags5+SrcTag5+Seq5+DstTag5+FLS6+LLS6+Amount9+Fee9+
 * SigningPubKey35+SrcAccount22+DstAccount22) + 116B EmitDetails (no
 * callback: 1+6+9+33+33+33+1, HookAPI.cpp's etxn_details) = 248B. Was
 * previously (wrongly) 270U, 22 bytes past the real content -- the extra
 * bytes are zero-initialized static-array padding that a strict STTx parse
 * (emit()/etxn_fee_base()) tries to read as more fields and throws on. */
#define PREPARE_PAYMENT_SIMPLE_SIZE 248U
#define PREPARE_PAYMENT_SIMPLE(                                              \
    buf_out_master, drops_amount_raw, to_address, dest_tag_raw, src_tag_raw) \
    {                                                                        \
        uint8_t* buf_out = buf_out_master;                                   \
        uint8_t pacc[20];                                                    \
        uint64_t drops_amount = (drops_amount_raw);                          \
        uint32_t dest_tag = (dest_tag_raw);                                  \
        uint32_t src_tag = (src_tag_raw);                                    \
        uint32_t cls = (uint32_t)ledger_seq();                               \
        hook_account(SBUF(pacc));                                            \
        _01_02_ENCODE_TT(buf_out, 0 /*ttPAYMENT*/);                          \
        _02_02_ENCODE_FLAGS(buf_out, 0x80000000UL);                          \
        _02_03_ENCODE_TAG_SRC(buf_out, src_tag);                             \
        _02_04_ENCODE_SEQUENCE(buf_out, 0);                                  \
        _02_14_ENCODE_TAG_DST(buf_out, dest_tag);                            \
        _02_26_ENCODE_FLS(buf_out, cls + 1);                                 \
        _02_27_ENCODE_LLS(buf_out, cls + 5);                                 \
        _06_01_ENCODE_DROPS_AMOUNT(buf_out, drops_amount);                   \
        uint8_t* fee_ptr = buf_out;                                          \
        _06_08_ENCODE_DROPS_FEE(buf_out, 0);                                 \
        _07_03_ENCODE_SIGNING_PUBKEY_NULL(buf_out);                          \
        _08_01_ENCODE_ACCOUNT_SRC(buf_out, pacc);                            \
        _08_03_ENCODE_ACCOUNT_DST(buf_out, to_address);                      \
        etxn_details((uint32_t)buf_out, PREPARE_PAYMENT_SIMPLE_SIZE);        \
        int64_t pfee =                                                       \
            etxn_fee_base(buf_out_master, PREPARE_PAYMENT_SIMPLE_SIZE);      \
        _06_08_ENCODE_DROPS_FEE(fee_ptr, pfee);                              \
    }

/* ttINVOKE + sfBlob raw tx, used by the prepare/etxn_fee_base/emit 1KiB
 * measurements (Phase 3). Only the common REQUIRED fields (TransactionType,
 * Sequence, Fee, SigningPubKey, Account -- TxFormats.cpp's commonFields) plus
 * sfBlob are written; Invoke has no required fields of its own. EmitDetails
 * is always appended (and Fee back-patched from etxn_fee_base) so the same
 * buffer is also a valid emit()-able transaction -- mirrors what
 * PREPARE_PAYMENT_SIMPLE above does for the Payment case. */
#define ENCODE_SIGNING_PUBKEY_EMPTY_SIZE 2U
#define ENCODE_SIGNING_PUBKEY_EMPTY(buf_out)         \
    {                                                \
        buf_out[0] = 0x73U;                          \
        buf_out[1] = 0x00U;                          \
        buf_out += ENCODE_SIGNING_PUBKEY_EMPTY_SIZE; \
    }
#define _07_26_ENCODE_BLOB_SIZE(n) (4U + (uint32_t)(n))
/* `fillbyte` is unused: the data bytes are left as whatever is already in
 * `buf_out`'s backing storage (zero, since every caller's tx buffer is a
 * `static` array) rather than looped over -- a byte-fill loop over ~1KiB
 * either gets recognised as a memset() idiom at -O2 (hooks may only import
 * hook_api functions, so `call $memset` is rejected as malformed) or, once
 * defeated with a non-constant per-byte value, blows the 65535 static
 * worst-case instruction budget on its own. The Blob field's *content*
 * doesn't matter for this benchmark, only its declared VL length. */
#define _07_26_ENCODE_BLOB(buf_out, fillbyte, n)             \
    {                                                        \
        uint32_t _bl = (uint32_t)(n) - 193U;                 \
        buf_out[0] = 0x70U;                                  \
        buf_out[1] = 0x1AU;                                  \
        buf_out[2] = (uint8_t)(193U + ((_bl >> 8) & 0xFFU)); \
        buf_out[3] = (uint8_t)(_bl & 0xFFU);                 \
        buf_out += _07_26_ENCODE_BLOB_SIZE(n);               \
    }
#define PREPARE_INVOKE_BLOB_SIZE(blob_len)                             \
    (3U + 5U + 6U + 6U + 9U + ENCODE_SIGNING_PUBKEY_EMPTY_SIZE + 22U + \
     _07_26_ENCODE_BLOB_SIZE(blob_len) + 116U)
#define PREPARE_INVOKE_BLOB(buf_out_master, blob_len)              \
    {                                                              \
        uint8_t* buf_out = buf_out_master;                         \
        uint8_t pacc[20];                                          \
        uint32_t cls = (uint32_t)ledger_seq();                     \
        hook_account(SBUF(pacc));                                  \
        _01_02_ENCODE_TT(buf_out, 99 /*ttINVOKE*/);                \
        _02_04_ENCODE_SEQUENCE(buf_out, 0);                        \
        _02_26_ENCODE_FLS(buf_out, cls + 1);                       \
        _02_27_ENCODE_LLS(buf_out, cls + 5);                       \
        uint8_t* fee_ptr = buf_out;                                \
        _06_08_ENCODE_DROPS_FEE(buf_out, 0);                       \
        ENCODE_SIGNING_PUBKEY_EMPTY(buf_out);                      \
        _08_01_ENCODE_ACCOUNT_SRC(buf_out, pacc);                  \
        _07_26_ENCODE_BLOB(buf_out, 'x', (blob_len));              \
        int64_t detlen = etxn_details((uint32_t)buf_out, 200);     \
        buf_out += detlen;                                         \
        int64_t pfee = etxn_fee_base(                              \
            buf_out_master, (uint32_t)(buf_out - buf_out_master)); \
        _06_08_ENCODE_DROPS_FEE(fee_ptr, pfee);                    \
    }

/* ---- loop scaffold shared by every loopable variant -------------------- */
#define BENCH_BEGIN(MAXITER)                           \
    uint8_t nbuf[4];                                   \
    uint32_t n = (otxn_param(SBUF(nbuf), "N", 1) == 4) \
        ? (uint32_t)UINT32_FROM_BUF(nbuf)              \
        : 0;                                           \
    int64_t acc = 0;                                   \
    for (uint32_t i = 0; GUARD(MAXITER), i < n; ++i)   \
    {
/* Return-value discipline (team-lead review): if the first iteration's
 * accumulated API result is negative, the API call under test errored
 * immediately (e.g. INVALID_ARGUMENT on a malformed operand) rather than
 * doing real work -- roll back with that code so the rep shows up as
 * tecHOOK_REJECTED (mismatched TER) and gets skipped/counted instead of
 * silently recording the cost of an error path. */
/* acc accumulates every call's raw return value across the whole N-loop,
 * unreset. Real host-API error codes are all small (hook/error.h: -1..-45),
 * but float_* successes return XFL-encoded bit patterns (magnitude ~1e18)
 * that legitimately overflow int64_t after a couple of loop iterations of
 * summing -- an overflowed/wrapped acc is not an error. -100000 comfortably
 * separates "real error code" from "XFL bit pattern (or overflow of same)". */
#define BENCH_END                 \
    if (acc < 0 && acc > -100000) \
        rollback(0, 0, acc);      \
    }                             \
    accept(0, 0, acc);            \
    return 0;

/* accumulate 4 unrolled calls of a zero-arg API into acc (cheap-API group) */
#define BENCH4(CALL)   \
    {                  \
        acc += (CALL); \
        acc += (CALL); \
        acc += (CALL); \
        acc += (CALL); \
    }

/* ======================================================================= */
/* Baselines: pure-wasm loop bodies, no host calls.                        */
/* ======================================================================= */

#if defined(B_base1)

static uint8_t buf[64];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(1300)
    acc ^= buf[(i + 0) & 63];
    buf[(i * 7 + 0) & 63] = (uint8_t)(acc + 0);
    BENCH_END
}

#elif defined(B_base2)

static uint8_t buf[64];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(700)
    acc ^= buf[(i + 0) & 63];
    buf[(i * 7 + 0) & 63] = (uint8_t)(acc + 0);
    acc ^= buf[(i + 1) & 63];
    buf[(i * 7 + 1) & 63] = (uint8_t)(acc + 1);
    BENCH_END
}

#elif defined(B_base4)

static uint8_t buf[64];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(400)
    acc ^= buf[(i + 0) & 63];
    buf[(i * 7 + 0) & 63] = (uint8_t)(acc + 0);
    acc ^= buf[(i + 1) & 63];
    buf[(i * 7 + 1) & 63] = (uint8_t)(acc + 1);
    acc ^= buf[(i + 2) & 63];
    buf[(i * 7 + 2) & 63] = (uint8_t)(acc + 2);
    acc ^= buf[(i + 3) & 63];
    buf[(i * 7 + 3) & 63] = (uint8_t)(acc + 3);
    BENCH_END
}

#elif defined(B_base8)

static uint8_t buf[64];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(250)
    acc ^= buf[(i + 0) & 63];
    buf[(i * 7 + 0) & 63] = (uint8_t)(acc + 0);
    acc ^= buf[(i + 1) & 63];
    buf[(i * 7 + 1) & 63] = (uint8_t)(acc + 1);
    acc ^= buf[(i + 2) & 63];
    buf[(i * 7 + 2) & 63] = (uint8_t)(acc + 2);
    acc ^= buf[(i + 3) & 63];
    buf[(i * 7 + 3) & 63] = (uint8_t)(acc + 3);
    acc ^= buf[(i + 4) & 63];
    buf[(i * 7 + 4) & 63] = (uint8_t)(acc + 4);
    acc ^= buf[(i + 5) & 63];
    buf[(i * 7 + 5) & 63] = (uint8_t)(acc + 5);
    acc ^= buf[(i + 6) & 63];
    buf[(i * 7 + 6) & 63] = (uint8_t)(acc + 6);
    acc ^= buf[(i + 7) & 63];
    buf[(i * 7 + 7) & 63] = (uint8_t)(acc + 7);
    BENCH_END
}

#elif defined(B_base16)

static uint8_t buf[64];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(50)
    acc ^= buf[(i + 0) & 63];
    buf[(i * 7 + 0) & 63] = (uint8_t)(acc + 0);
    acc ^= buf[(i + 1) & 63];
    buf[(i * 7 + 1) & 63] = (uint8_t)(acc + 1);
    acc ^= buf[(i + 2) & 63];
    buf[(i * 7 + 2) & 63] = (uint8_t)(acc + 2);
    acc ^= buf[(i + 3) & 63];
    buf[(i * 7 + 3) & 63] = (uint8_t)(acc + 3);
    acc ^= buf[(i + 4) & 63];
    buf[(i * 7 + 4) & 63] = (uint8_t)(acc + 4);
    acc ^= buf[(i + 5) & 63];
    buf[(i * 7 + 5) & 63] = (uint8_t)(acc + 5);
    acc ^= buf[(i + 6) & 63];
    buf[(i * 7 + 6) & 63] = (uint8_t)(acc + 6);
    acc ^= buf[(i + 7) & 63];
    buf[(i * 7 + 7) & 63] = (uint8_t)(acc + 7);
    acc ^= buf[(i + 8) & 63];
    buf[(i * 7 + 8) & 63] = (uint8_t)(acc + 8);
    acc ^= buf[(i + 9) & 63];
    buf[(i * 7 + 9) & 63] = (uint8_t)(acc + 9);
    acc ^= buf[(i + 10) & 63];
    buf[(i * 7 + 10) & 63] = (uint8_t)(acc + 10);
    acc ^= buf[(i + 11) & 63];
    buf[(i * 7 + 11) & 63] = (uint8_t)(acc + 11);
    acc ^= buf[(i + 12) & 63];
    buf[(i * 7 + 12) & 63] = (uint8_t)(acc + 12);
    acc ^= buf[(i + 13) & 63];
    buf[(i * 7 + 13) & 63] = (uint8_t)(acc + 13);
    acc ^= buf[(i + 14) & 63];
    buf[(i * 7 + 14) & 63] = (uint8_t)(acc + 14);
    acc ^= buf[(i + 15) & 63];
    buf[(i * 7 + 15) & 63] = (uint8_t)(acc + 15);
    BENCH_END
}

#elif defined(B_base64)

static uint8_t buf[64];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(38)
    acc ^= buf[(i + 0) & 63];
    buf[(i * 7 + 0) & 63] = (uint8_t)(acc + 0);
    acc ^= buf[(i + 1) & 63];
    buf[(i * 7 + 1) & 63] = (uint8_t)(acc + 1);
    acc ^= buf[(i + 2) & 63];
    buf[(i * 7 + 2) & 63] = (uint8_t)(acc + 2);
    acc ^= buf[(i + 3) & 63];
    buf[(i * 7 + 3) & 63] = (uint8_t)(acc + 3);
    acc ^= buf[(i + 4) & 63];
    buf[(i * 7 + 4) & 63] = (uint8_t)(acc + 4);
    acc ^= buf[(i + 5) & 63];
    buf[(i * 7 + 5) & 63] = (uint8_t)(acc + 5);
    acc ^= buf[(i + 6) & 63];
    buf[(i * 7 + 6) & 63] = (uint8_t)(acc + 6);
    acc ^= buf[(i + 7) & 63];
    buf[(i * 7 + 7) & 63] = (uint8_t)(acc + 7);
    acc ^= buf[(i + 8) & 63];
    buf[(i * 7 + 8) & 63] = (uint8_t)(acc + 8);
    acc ^= buf[(i + 9) & 63];
    buf[(i * 7 + 9) & 63] = (uint8_t)(acc + 9);
    acc ^= buf[(i + 10) & 63];
    buf[(i * 7 + 10) & 63] = (uint8_t)(acc + 10);
    acc ^= buf[(i + 11) & 63];
    buf[(i * 7 + 11) & 63] = (uint8_t)(acc + 11);
    acc ^= buf[(i + 12) & 63];
    buf[(i * 7 + 12) & 63] = (uint8_t)(acc + 12);
    acc ^= buf[(i + 13) & 63];
    buf[(i * 7 + 13) & 63] = (uint8_t)(acc + 13);
    acc ^= buf[(i + 14) & 63];
    buf[(i * 7 + 14) & 63] = (uint8_t)(acc + 14);
    acc ^= buf[(i + 15) & 63];
    buf[(i * 7 + 15) & 63] = (uint8_t)(acc + 15);
    acc ^= buf[(i + 16) & 63];
    buf[(i * 7 + 16) & 63] = (uint8_t)(acc + 16);
    acc ^= buf[(i + 17) & 63];
    buf[(i * 7 + 17) & 63] = (uint8_t)(acc + 17);
    acc ^= buf[(i + 18) & 63];
    buf[(i * 7 + 18) & 63] = (uint8_t)(acc + 18);
    acc ^= buf[(i + 19) & 63];
    buf[(i * 7 + 19) & 63] = (uint8_t)(acc + 19);
    acc ^= buf[(i + 20) & 63];
    buf[(i * 7 + 20) & 63] = (uint8_t)(acc + 20);
    acc ^= buf[(i + 21) & 63];
    buf[(i * 7 + 21) & 63] = (uint8_t)(acc + 21);
    acc ^= buf[(i + 22) & 63];
    buf[(i * 7 + 22) & 63] = (uint8_t)(acc + 22);
    acc ^= buf[(i + 23) & 63];
    buf[(i * 7 + 23) & 63] = (uint8_t)(acc + 23);
    acc ^= buf[(i + 24) & 63];
    buf[(i * 7 + 24) & 63] = (uint8_t)(acc + 24);
    acc ^= buf[(i + 25) & 63];
    buf[(i * 7 + 25) & 63] = (uint8_t)(acc + 25);
    acc ^= buf[(i + 26) & 63];
    buf[(i * 7 + 26) & 63] = (uint8_t)(acc + 26);
    acc ^= buf[(i + 27) & 63];
    buf[(i * 7 + 27) & 63] = (uint8_t)(acc + 27);
    acc ^= buf[(i + 28) & 63];
    buf[(i * 7 + 28) & 63] = (uint8_t)(acc + 28);
    acc ^= buf[(i + 29) & 63];
    buf[(i * 7 + 29) & 63] = (uint8_t)(acc + 29);
    acc ^= buf[(i + 30) & 63];
    buf[(i * 7 + 30) & 63] = (uint8_t)(acc + 30);
    acc ^= buf[(i + 31) & 63];
    buf[(i * 7 + 31) & 63] = (uint8_t)(acc + 31);
    acc ^= buf[(i + 32) & 63];
    buf[(i * 7 + 32) & 63] = (uint8_t)(acc + 32);
    acc ^= buf[(i + 33) & 63];
    buf[(i * 7 + 33) & 63] = (uint8_t)(acc + 33);
    acc ^= buf[(i + 34) & 63];
    buf[(i * 7 + 34) & 63] = (uint8_t)(acc + 34);
    acc ^= buf[(i + 35) & 63];
    buf[(i * 7 + 35) & 63] = (uint8_t)(acc + 35);
    acc ^= buf[(i + 36) & 63];
    buf[(i * 7 + 36) & 63] = (uint8_t)(acc + 36);
    acc ^= buf[(i + 37) & 63];
    buf[(i * 7 + 37) & 63] = (uint8_t)(acc + 37);
    acc ^= buf[(i + 38) & 63];
    buf[(i * 7 + 38) & 63] = (uint8_t)(acc + 38);
    acc ^= buf[(i + 39) & 63];
    buf[(i * 7 + 39) & 63] = (uint8_t)(acc + 39);
    acc ^= buf[(i + 40) & 63];
    buf[(i * 7 + 40) & 63] = (uint8_t)(acc + 40);
    acc ^= buf[(i + 41) & 63];
    buf[(i * 7 + 41) & 63] = (uint8_t)(acc + 41);
    acc ^= buf[(i + 42) & 63];
    buf[(i * 7 + 42) & 63] = (uint8_t)(acc + 42);
    acc ^= buf[(i + 43) & 63];
    buf[(i * 7 + 43) & 63] = (uint8_t)(acc + 43);
    acc ^= buf[(i + 44) & 63];
    buf[(i * 7 + 44) & 63] = (uint8_t)(acc + 44);
    acc ^= buf[(i + 45) & 63];
    buf[(i * 7 + 45) & 63] = (uint8_t)(acc + 45);
    acc ^= buf[(i + 46) & 63];
    buf[(i * 7 + 46) & 63] = (uint8_t)(acc + 46);
    acc ^= buf[(i + 47) & 63];
    buf[(i * 7 + 47) & 63] = (uint8_t)(acc + 47);
    acc ^= buf[(i + 48) & 63];
    buf[(i * 7 + 48) & 63] = (uint8_t)(acc + 48);
    acc ^= buf[(i + 49) & 63];
    buf[(i * 7 + 49) & 63] = (uint8_t)(acc + 49);
    acc ^= buf[(i + 50) & 63];
    buf[(i * 7 + 50) & 63] = (uint8_t)(acc + 50);
    acc ^= buf[(i + 51) & 63];
    buf[(i * 7 + 51) & 63] = (uint8_t)(acc + 51);
    acc ^= buf[(i + 52) & 63];
    buf[(i * 7 + 52) & 63] = (uint8_t)(acc + 52);
    acc ^= buf[(i + 53) & 63];
    buf[(i * 7 + 53) & 63] = (uint8_t)(acc + 53);
    acc ^= buf[(i + 54) & 63];
    buf[(i * 7 + 54) & 63] = (uint8_t)(acc + 54);
    acc ^= buf[(i + 55) & 63];
    buf[(i * 7 + 55) & 63] = (uint8_t)(acc + 55);
    acc ^= buf[(i + 56) & 63];
    buf[(i * 7 + 56) & 63] = (uint8_t)(acc + 56);
    acc ^= buf[(i + 57) & 63];
    buf[(i * 7 + 57) & 63] = (uint8_t)(acc + 57);
    acc ^= buf[(i + 58) & 63];
    buf[(i * 7 + 58) & 63] = (uint8_t)(acc + 58);
    acc ^= buf[(i + 59) & 63];
    buf[(i * 7 + 59) & 63] = (uint8_t)(acc + 59);
    acc ^= buf[(i + 60) & 63];
    buf[(i * 7 + 60) & 63] = (uint8_t)(acc + 60);
    acc ^= buf[(i + 61) & 63];
    buf[(i * 7 + 61) & 63] = (uint8_t)(acc + 61);
    acc ^= buf[(i + 62) & 63];
    buf[(i * 7 + 62) & 63] = (uint8_t)(acc + 62);
    acc ^= buf[(i + 63) & 63];
    buf[(i * 7 + 63) & 63] = (uint8_t)(acc + 63);
    BENCH_END
}

#elif defined(B_basei64)

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(290)
    acc = acc * 6364136223846793005LL + (int64_t)i + 0;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 1;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 2;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 3;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 4;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 5;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 6;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 7;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 8;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 9;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 10;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 11;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 12;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 13;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 14;
    acc ^= (acc >> 13);
    acc = acc * 6364136223846793005LL + (int64_t)i + 15;
    acc ^= (acc >> 13);
    BENCH_END
}

#elif defined(B_basemem)

static uint8_t src[64];
static uint8_t dst[64];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(470)
    *(uint64_t*)(dst + 0) = *(uint64_t*)(src + 0);
    *(uint64_t*)(dst + 8) = *(uint64_t*)(src + 8);
    *(uint64_t*)(dst + 16) = *(uint64_t*)(src + 16);
    *(uint64_t*)(dst + 24) = *(uint64_t*)(src + 24);
    *(uint64_t*)(dst + 32) = *(uint64_t*)(src + 32);
    *(uint64_t*)(dst + 40) = *(uint64_t*)(src + 40);
    *(uint64_t*)(dst + 48) = *(uint64_t*)(src + 48);
    *(uint64_t*)(dst + 56) = *(uint64_t*)(src + 56);
    src[i & 63] = (uint8_t)(i ^ (unsigned)acc);
    dst[(i + 1) & 63] = src[i & 63];
    acc += (int64_t)dst[i & 63];
    acc ^= (int64_t)src[(i + 1) & 63];
    dst[(i + 2) & 63] = src[(i + 1) & 63];
    acc += (int64_t)dst[(i + 2) & 63];
    dst[(i + 3) & 63] = src[(i + 2) & 63];
    acc ^= (int64_t)dst[(i + 3) & 63];
    BENCH_END
}

/* ======================================================================= */
/* Cheap zero-argument APIs: K=4 unrolled calls per iteration.             */
/* ======================================================================= */

#elif defined(B_fee_base)

int64_t
hook(uint32_t r){BENCH_BEGIN(1800) BENCH4(fee_base()) BENCH_END}

#elif defined(B_ledger_seq)

int64_t
hook(uint32_t r){BENCH_BEGIN(1800) BENCH4(ledger_seq()) BENCH_END}

#elif defined(B_hook_pos)

int64_t
hook(uint32_t r){BENCH_BEGIN(1800) BENCH4(hook_pos()) BENCH_END}

#elif defined(B_hook_pos_k16)

/* review #3: direct t_call measurement. hook_pos's own body is ~0, so the
 * per-iteration excess over dI*t_instr is (K+1)*t_call (K real calls + the
 * loop-head _g call), measured the same way as the baselines (Tw - Tg
 * differencing at N1/N2, not the closed-ledger cross-check). */
int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    acc += hook_pos();
    acc += hook_pos();
    acc += hook_pos();
    acc += hook_pos();
    acc += hook_pos();
    acc += hook_pos();
    acc += hook_pos();
    acc += hook_pos();
    acc += hook_pos();
    acc += hook_pos();
    acc += hook_pos();
    acc += hook_pos();
    acc += hook_pos();
    acc += hook_pos();
    acc += hook_pos();
    acc += hook_pos();
    BENCH_END
}

#elif defined(B_float_one)

int64_t
hook(uint32_t r){BENCH_BEGIN(1800) BENCH4(float_one()) BENCH_END}

#elif defined(B_otxn_type)

int64_t
hook(uint32_t r){BENCH_BEGIN(1800) BENCH4(otxn_type()) BENCH_END}

#elif defined(B_etxn_generation)

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(1800)
    BENCH4(etxn_generation())
    BENCH_END
}

/* ======================================================================= */
/* util_sha512h at three input sizes: one call per iteration.              */
/* ======================================================================= */

#elif defined(B_util_sha512h_32)

static uint8_t shabuf[32];

int64_t
hook(uint32_t r)
{
    uint8_t shaout[32];
    BENCH_BEGIN(1400)
    shabuf[i & 31] = (uint8_t)i;
    acc += util_sha512h(SBUF(shaout), SBUF(shabuf));
    BENCH_END
}

#elif defined(B_util_sha512h_1k)

static uint8_t shabuf[1024];

int64_t
hook(uint32_t r)
{
    uint8_t shaout[32];
    BENCH_BEGIN(1400)
    shabuf[i & 1023] = (uint8_t)i;
    acc += util_sha512h(SBUF(shaout), SBUF(shabuf));
    BENCH_END
}

#elif defined(B_util_sha512h_16k)

static uint8_t shabuf[16384];

int64_t
hook(uint32_t r)
{
    uint8_t shaout[32];
    BENCH_BEGIN(1400)
    shabuf[i & 16383] = (uint8_t)i;
    acc += util_sha512h(SBUF(shaout), SBUF(shabuf));
    BENCH_END
}

/* ======================================================================= */
/* Hook state: setup hooks pre-create 200 distinct keys; bench hooks then  */
/* read or (re)write those same 200 keys, one call per iteration.         */
/* Key = 32 bytes, first 4 bytes = big-endian i, rest zero.                */
/* ======================================================================= */

#elif defined(B_state_w_setup_32)

static uint8_t key[32];
static uint8_t val[32];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(256)
    UINT32_TO_BUF(key, i);
    val[0] = (uint8_t)i;
    acc += state_set(SBUF(val), SBUF(key));
    BENCH_END
}

#elif defined(B_state_w_setup_256)

static uint8_t key[32];
static uint8_t val[256];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(256)
    UINT32_TO_BUF(key, i);
    val[0] = (uint8_t)i;
    acc += state_set(SBUF(val), SBUF(key));
    BENCH_END
}

#elif defined(B_state_r_32)

static uint8_t key[32];

int64_t
hook(uint32_t r)
{
    uint8_t out[32];
    BENCH_BEGIN(256)
    UINT32_TO_BUF(key, i);
    acc += state(SBUF(out), SBUF(key));
    BENCH_END
}

#elif defined(B_state_r_256)

static uint8_t key[32];

int64_t
hook(uint32_t r)
{
    uint8_t out[256];
    BENCH_BEGIN(256)
    UINT32_TO_BUF(key, i);
    acc += state(SBUF(out), SBUF(key));
    BENCH_END
}

#elif defined(B_state_w_32)

static uint8_t key[32];
static uint8_t val[32];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(256)
    UINT32_TO_BUF(key, i);
    val[0] = (uint8_t)(acc);
    acc += state_set(SBUF(val), SBUF(key));
    BENCH_END
}

#elif defined(B_state_w_create_32)

/* review #6: state_set on fresh keys every rep (key = salt*1000+i, salt =
 * 4-byte HookParameter "S" set to the rep number), vs. B_state_w_32's
 * fixed keys (the modify path). */
static uint8_t key[32];
static uint8_t val[32];

int64_t
hook(uint32_t r)
{
    uint8_t sbuf[4];
    uint32_t salt =
        (otxn_param(SBUF(sbuf), "S", 1) == 4) ? UINT32_FROM_BUF(sbuf) : 0;
    BENCH_BEGIN(256)
    UINT32_TO_BUF(key, salt * 1000u + i);
    val[0] = (uint8_t)(acc);
    acc += state_set(SBUF(val), SBUF(key));
    BENCH_END
}

#elif defined(B_state_w_256)

static uint8_t key[32];
static uint8_t val[256];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(256)
    UINT32_TO_BUF(key, i);
    val[0] = (uint8_t)(acc);
    acc += state_set(SBUF(val), SBUF(key));
    BENCH_END
}

/* ======================================================================= */
/* Terminal / trivial hooks: no loop.                                      */
/* ======================================================================= */

#elif defined(B_accept0)

int64_t
hook(uint32_t r)
{
    _g(1, 1);
    accept(0, 0, 0);
    return 0;
}

#elif defined(B_rollback0)

int64_t
hook(uint32_t r)
{
    _g(1, 1);
    rollback(0, 0, 0);
    return 0;
}

#elif defined(B_noexit)

int64_t
hook(uint32_t r)
{
    _g(1, 1);
    return 0;
}

/* ======================================================================= */
/* Phase 2 additions (see docs/hook-api-cost/README.md).                    */
/* ======================================================================= */

#elif defined(B_util_raddr)

static uint8_t acc20[20];
static uint8_t rbuf[40];

int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));

    BENCH_BEGIN(300)
    BENCH4(util_raddr(SBUF(rbuf), SBUF(acc20)))

    BENCH_END
}

#elif defined(B_util_accid)

static uint8_t raddr[35] = "rHb9CJAWyB4rj91VRWn96DkukG4bwdtyTh";
static uint8_t abuf[20];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(util_accid(SBUF(abuf), SBUF(raddr)))

    BENCH_END
}

#elif defined(B_util_keylet_account)

static uint8_t acc20[20];
static uint8_t klbuf[34];

int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));

    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 3, (uint32_t)acc20, 20, 0, 0, 0, 0))

    BENCH_END
}

#elif defined(B_util_keylet_child)

static uint8_t hash32[32];
static uint8_t klbuf[34];

int64_t
hook(uint32_t r)
{
    hook_hash(SBUF(hash32), 0);

    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 5, (uint32_t)hash32, 32, 0, 0, 0, 0))

    BENCH_END
}

#elif defined(B_util_keylet_escrow)

static uint8_t acc20[20];
static uint8_t klbuf[34];

int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));

    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 20, (uint32_t)acc20, 20, 1, 0, 0, 0))

    BENCH_END
}

#elif defined(B_util_keylet_line)

static uint8_t acc20[20];
static uint8_t acc20b[20] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 2};
static uint8_t cur3[3] = {'U', 'S', 'D'};
static uint8_t klbuf[34];

int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));

    BENCH_BEGIN(300)
    BENCH4(util_keylet(
        SBUF(klbuf),
        9,
        (uint32_t)acc20,
        20,
        (uint32_t)acc20b,
        20,
        (uint32_t)cur3,
        3))

    BENCH_END
}

#elif defined(B_util_keylet_amendments)

static uint8_t klbuf[34];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 4, 0, 0, 0, 0, 0, 0))

    BENCH_END
}

#elif defined(B_util_keylet_quality)

static uint8_t dirkey[34] = {0, 0x64};
static uint8_t klbuf[34];

int64_t
hook(uint32_t r){
    BENCH_BEGIN(300)
        BENCH4(util_keylet(SBUF(klbuf), 11, (uint32_t)dirkey, 34, 1, 0, 0, 0))

            BENCH_END}

#elif defined(B_etxn_burden)

/* etxn_burden() requires etxn_reserve() first (HookAPI.cpp:
 * expected_etxn_count <= -1 -> PREREQUISITE_NOT_MET). */
int64_t
hook(uint32_t r)
{
    etxn_reserve(1);
    BENCH_BEGIN(300)
    BENCH4(etxn_burden())

    BENCH_END
}

#elif defined(B_otxn_burden)

int64_t
hook(uint32_t r){BENCH_BEGIN(300) BENCH4(otxn_burden())

                     BENCH_END}

#elif defined(B_otxn_generation)

int64_t
hook(uint32_t r){BENCH_BEGIN(300) BENCH4(otxn_generation())

                     BENCH_END}

#elif defined(B_ledger_last_time)

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(ledger_last_time())

    BENCH_END
}

#elif defined(B_ledger_last_hash)

static uint8_t hbuf[32];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(ledger_last_hash(SBUF(hbuf)))

    BENCH_END
}

#elif defined(B_hook_account_api)

static uint8_t hbuf[20];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(hook_account(SBUF(hbuf)))

    BENCH_END
}

#elif defined(B_hook_hash_0)

static uint8_t hbuf[32];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(hook_hash(SBUF(hbuf), 0))

    BENCH_END
}

#elif defined(B_hook_hash_neg1)

static uint8_t hbuf[32];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(hook_hash(SBUF(hbuf), -1))

    BENCH_END
}

#elif defined(B_otxn_id_0)

static uint8_t hbuf[32];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(otxn_id(SBUF(hbuf), 0))

    BENCH_END
}

#elif defined(B_otxn_id_1)

static uint8_t hbuf[32];

int64_t
hook(uint32_t r){BENCH_BEGIN(300) BENCH4(otxn_id(SBUF(hbuf), 1))

                     BENCH_END}

#elif defined(B_float_multiply)

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(float_multiply(fone, fone))

    BENCH_END
}

#elif defined(B_float_mulratio)

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(float_mulratio(fone, 0, 1, 2))

    BENCH_END
}

#elif defined(B_float_negate)

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(float_negate(fone))

    BENCH_END
}

#elif defined(B_float_compare)

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    /* mode 0 is INVALID_ARGUMENT (HookAPI.cpp: mode==0 explicitly rejected);
     * COMPARE_EQUAL=1 on fone==fone is a real, always-successful call. */
    BENCH_BEGIN(300)
    BENCH4(float_compare(fone, fone, 1 /*COMPARE_EQUAL*/))

    BENCH_END
}

#elif defined(B_float_compare_le)

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(float_compare(fone, fone, 3 /*COMPARE_LESS|COMPARE_EQUAL*/))

    BENCH_END
}

#elif defined(B_float_sum)

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(float_sum(fone, fone))

    BENCH_END
}

#elif defined(B_float_invert)

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(float_invert(fone))

    BENCH_END
}

#elif defined(B_float_divide)

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(float_divide(fone, fone))

    BENCH_END
}

#elif defined(B_float_mantissa)

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(float_mantissa(fone))

    BENCH_END
}

#elif defined(B_float_sign)

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(float_sign(fone))

    BENCH_END
}

#elif defined(B_float_int)

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(float_int(fone, 0, 0))

    BENCH_END
}

#elif defined(B_float_log)

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(float_log(fone))

    BENCH_END
}

#elif defined(B_float_root)

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(float_root(fone, 2))

    BENCH_END
}

#elif defined(B_float_set)

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(float_set(0, 1000000000000000LL))

    BENCH_END
}

#elif defined(B_float_sto_xrp)

/* HookAPI::float_sto: is_xrp = (field_code == 0) -- sfAmount (0x60001) is
 * NOT 0, so passing it here always hit the "!is_xrp && !is_short" ->
 * INVALID_ARGUMENT branch. field_code 0 is what "XRP, no field header"
 * actually means. */
static uint8_t sbuf[48];

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(float_sto(SBUF(sbuf), 0, 0, 0, 0, fone, 0 /*is_xrp*/))

    BENCH_END
}

#elif defined(B_float_sto_iou)

/* bytes_needed = 8 (amount) + 1 (1-byte field header, field=1<16 &&
 * type=6<16) + 40 (currency+issuer) = 49; sbuf was 48, one short ->
 * TOO_SMALL on every call. */
static uint8_t cur20[20] = {0, 0, 0,   0,   0,   0, 0, 0, 0, 0,
                            0, 0, 'U', 'S', 'D', 0, 0, 0, 0, 0};
static uint8_t acc20[20] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 2};
static uint8_t sbuf[64];

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(
        float_sto(SBUF(sbuf), SBUF(cur20), (uint32_t)acc20, 20, fone, sfAmount))

    BENCH_END
}

#elif defined(B_float_sto_short)

/* is_short = (field_code == 0xFFFFFFFF). currency/issuer must both be
 * absent (HookAPI.cpp: issuer XOR currency present -> INVALID_ARGUMENT;
 * the old code passed a currency with no issuer, always invalid). */
static uint8_t sbuf[48];

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(float_sto(SBUF(sbuf), 0, 0, 0, 0, fone, 0xFFFFFFFFU /*is_short*/))

    BENCH_END
}

#elif defined(B_float_sto_set)

static uint8_t sbuf[48];

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();
    float_sto(SBUF(sbuf), 0, 0, 0, 0, fone, sfAmount);

    BENCH_BEGIN(300)
    BENCH4(float_sto_set(SBUF(sbuf)))

    BENCH_END
}

#elif defined(B_trace_32)

static uint8_t msg[2] = "m";
static uint8_t tbuf[32];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(trace(SBUF(msg), SBUF(tbuf), 0))

    BENCH_END
}

#elif defined(B_trace_1k_hex)

static uint8_t msg[2] = "m";
static uint8_t tbuf[1024];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(trace(SBUF(msg), SBUF(tbuf), 1))

    BENCH_END
}

#elif defined(B_trace_num)

static uint8_t msg[2] = "m";

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(trace_num(SBUF(msg), (int64_t)i))

    BENCH_END
}

#elif defined(B_trace_float)

static uint8_t msg[2] = "m";

int64_t
hook(uint32_t r)
{
    int64_t fone = float_one();

    BENCH_BEGIN(300)
    BENCH4(trace_float(SBUF(msg), fone))

    BENCH_END
}

#elif defined(B_otxn_param_32)

static uint8_t pbuf[32];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(otxn_param(SBUF(pbuf), "P", 1))

    BENCH_END
}

#elif defined(B_otxn_param_256)

static uint8_t pbuf[256];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(otxn_param(SBUF(pbuf), "P", 1))

    BENCH_END
}

#elif defined(B_hook_param_32)

static uint8_t pbuf[32];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(hook_param(SBUF(pbuf), "P", 1))

    BENCH_END
}

#elif defined(B_hook_param_256)

static uint8_t pbuf[256];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(hook_param(SBUF(pbuf), "P", 1))

    BENCH_END
}

#elif defined(B_otxn_field_acc)

static uint8_t fbuf[64];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    acc += otxn_field(SBUF(fbuf), sfAccount);

    BENCH_END
}

#elif defined(B_otxn_field_1k)

static uint8_t fbuf[1200];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    acc += otxn_field(SBUF(fbuf), sfBlob);

    BENCH_END
}

#elif defined(B_otxn_field_16k)

static uint8_t fbuf[17000];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    acc += otxn_field(SBUF(fbuf), sfBlob);

    BENCH_END
}

#elif defined(B_otxn_slot_small)

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    acc += otxn_slot(1);

    BENCH_END
}

#elif defined(B_otxn_slot_1k)

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    acc += otxn_slot(1);

    BENCH_END
}

#elif defined(B_otxn_slot_16k)

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    acc += otxn_slot(1);

    BENCH_END
}

#elif defined(B_slot_1k)

static uint8_t sbuf[1200];

int64_t
hook(uint32_t r)
{
    otxn_slot(1);

    BENCH_BEGIN(300)
    acc += slot(SBUF(sbuf), 1);

    BENCH_END
}

#elif defined(B_slot_16k)

static uint8_t sbuf[17000];

int64_t
hook(uint32_t r)
{
    otxn_slot(1);

    BENCH_BEGIN(300)
    acc += slot(SBUF(sbuf), 1);

    BENCH_END
}

#elif defined(B_slot_size)

int64_t
hook(uint32_t r)
{
    otxn_slot(1);

    BENCH_BEGIN(300)
    acc += slot_size(1);

    BENCH_END
}

#elif defined(B_slot_type_0)

int64_t
hook(uint32_t r)
{
    otxn_slot(1);

    BENCH_BEGIN(300)
    acc += slot_type(1, 0);

    BENCH_END
}

#elif defined(B_slot_type_1)

/* flags=1 requires the slot to hold an STAmount (HookAPI.cpp: obj.getSType()
 * != STI_AMOUNT -> NOT_AN_AMOUNT); the whole-tx slot from otxn_slot() is an
 * STObject, not an STAmount. sfFee is always present and always an amount. */
int64_t
hook(uint32_t r)
{
    otxn_slot(1);
    slot_subfield(1, sfFee, 2);

    BENCH_BEGIN(300)
    acc += slot_type(2, 1);

    BENCH_END
}

#elif defined(B_slot_count)

int64_t
hook(uint32_t r)
{
    otxn_slot(1);
    slot_subfield(1, sfMemos, 2);

    BENCH_BEGIN(300)
    acc += slot_count(2);

    BENCH_END
}

#elif defined(B_slot_subfield)

int64_t
hook(uint32_t r)
{
    otxn_slot(1);

    BENCH_BEGIN(300)
    acc += slot_subfield(1, sfAccount, 2);

    BENCH_END
}

#elif defined(B_slot_subarray)

int64_t
hook(uint32_t r)
{
    otxn_slot(1);
    slot_subfield(1, sfMemos, 2);

    BENCH_BEGIN(300)
    acc += slot_subarray(2, 0, 3);

    BENCH_END
}

#elif defined(B_slot_float)

int64_t
hook(uint32_t r)
{
    otxn_slot(1);
    slot_subfield(1, sfAmount, 2);

    BENCH_BEGIN(300)
    acc += slot_float(2);

    BENCH_END
}

#elif defined(B_slot_set_34)

static uint8_t klbuf[34];

int64_t
hook(uint32_t r)
{
    uint8_t acc20[20];
    hook_account(SBUF(acc20));
    util_keylet(SBUF(klbuf), 3, (uint32_t)acc20, 20, 0, 0, 0, 0);

    BENCH_BEGIN(300)
    acc += slot_set(SBUF(klbuf), 1);

    BENCH_END
}

#elif defined(B_slot_clear)

static uint8_t klbuf[34];

int64_t
hook(uint32_t r)
{
    uint8_t acc20[20];
    hook_account(SBUF(acc20));
    util_keylet(SBUF(klbuf), 3, (uint32_t)acc20, 20, 0, 0, 0, 0);

    BENCH_BEGIN(300)
    slot_set(SBUF(klbuf), 1);
    acc += slot_clear(1);

    BENCH_END
}

#elif defined(B_sto_validate_small)

static uint8_t sobj[128];
static uint32_t sobj_len;

int64_t
hook(uint32_t r)
{
    /* hand-built STObject: sfAccount (22B) + sfAmount (9B, XRP drops) */
    uint8_t acc20[20];
    hook_account(SBUF(acc20));
    uint8_t* p = sobj;
    p[0] = 0x81U;
    p[1] = 0x14U; /* sfAccount, VL 20 */
    for (int k = 0; k < 20; ++k)
        p[2 + k] = acc20[k];
    p += 22;
    p[0] = 0x61U; /* sfAmount, native */
    p[1] = 0b01000000;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0x64U;
    sobj_len = 31;

    BENCH_BEGIN(300)
    acc += sto_validate(SBUF(sobj));

    BENCH_END
}

#elif defined(B_sto_subfield_small)

static uint8_t sobj[128];
static uint32_t sobj_len;

int64_t
hook(uint32_t r)
{
    /* hand-built STObject: sfAccount (22B) + sfAmount (9B, XRP drops) */
    uint8_t acc20[20];
    hook_account(SBUF(acc20));
    uint8_t* p = sobj;
    p[0] = 0x81U;
    p[1] = 0x14U; /* sfAccount, VL 20 */
    for (int k = 0; k < 20; ++k)
        p[2 + k] = acc20[k];
    p += 22;
    p[0] = 0x61U; /* sfAmount, native */
    p[1] = 0b01000000;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0x64U;
    sobj_len = 31;

    BENCH_BEGIN(300)
    acc += sto_subfield(sobj, sobj_len, sfAccount);

    BENCH_END
}

#elif defined(B_sto_emplace_small)

static uint8_t sobj[128];
static uint32_t sobj_len;
static uint8_t outbuf[160];
static uint8_t newfield[34] = {0x50U, 17U};

int64_t
hook(uint32_t r)
{
    /* hand-built STObject: sfAccount (22B) + sfAmount (9B, XRP drops) */
    uint8_t acc20[20];
    hook_account(SBUF(acc20));
    uint8_t* p = sobj;
    p[0] = 0x81U;
    p[1] = 0x14U; /* sfAccount, VL 20 */
    for (int k = 0; k < 20; ++k)
        p[2 + k] = acc20[k];
    p += 22;
    p[0] = 0x61U; /* sfAmount, native */
    p[1] = 0b01000000;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0x64U;
    sobj_len = 31;

    BENCH_BEGIN(300)
    acc +=
        sto_emplace(SBUF(outbuf), sobj, sobj_len, SBUF(newfield), sfInvoiceID);

    BENCH_END
}

#elif defined(B_sto_erase_small)

static uint8_t sobj[128];
static uint32_t sobj_len;
static uint8_t outbuf[160];

int64_t
hook(uint32_t r)
{
    /* hand-built STObject: sfAmount (9B, XRP drops) + sfAccount (22B), in
     * CANONICAL (type,field) order -- unlike sto_subfield/sto_validate,
     * sto_emplace/sto_erase's field search relies on ascending order to
     * find the insertion/erase point (applyHook.cpp: "type<<16)+field >
     * field_id" early-exits as "not present"). sfAccount(0x80001) before
     * sfAmount(0x60001) made every erase see the target as already passed,
     * so it always reported the field absent (DOESNT_EXIST). */
    uint8_t acc20[20];
    hook_account(SBUF(acc20));
    uint8_t* p = sobj;
    p[0] = 0x61U; /* sfAmount, native */
    p[1] = 0b01000000;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0x64U;
    p += 9;
    p[0] = 0x81U;
    p[1] = 0x14U; /* sfAccount, VL 20 */
    for (int k = 0; k < 20; ++k)
        p[2 + k] = acc20[k];
    sobj_len = 31;

    BENCH_BEGIN(300)
    acc += sto_erase(SBUF(outbuf), sobj, sobj_len, sfAmount);

    BENCH_END
}

#elif defined(B_sto_validate_tx)

static uint8_t sobj[4400];
static uint32_t sobj_len;

int64_t
hook(uint32_t r)
{
    otxn_slot(1);
    sobj_len = (uint32_t)slot(sobj, sizeof(sobj), 1);

    BENCH_BEGIN(300)
    acc += sto_validate(sobj, sobj_len);

    BENCH_END
}

#elif defined(B_sto_subfield_tx)

static uint8_t sobj[4400];
static uint32_t sobj_len;

int64_t
hook(uint32_t r)
{
    otxn_slot(1);
    sobj_len = (uint32_t)slot(sobj, sizeof(sobj), 1);

    BENCH_BEGIN(300)
    acc += sto_subfield(sobj, sobj_len, sfAccount);

    BENCH_END
}

#elif defined(B_sto_subarray_tx)

static uint8_t sobj[4400];
static uint32_t sobj_len;
static uint8_t memobuf[1100];
static int64_t memobuf_len;

int64_t
hook(uint32_t r)
{
    otxn_slot(1);
    sobj_len = (uint32_t)slot(sobj, sizeof(sobj), 1);
    {
        int64_t sub = sto_subfield(sobj, sobj_len, sfMemos);
        uint32_t off = SUB_OFFSET(sub), len = SUB_LENGTH(sub);
        /* Copy 8 bytes/iteration, not 1: the largest fixture (one ~1KiB
         * memo among 3, ~1050B serialized) needs ~1050 iterations of a
         * byte-at-a-time loop, which pushes this hook's static worst-case
         * instruction count over the 65535 guard-checker limit (measured:
         * 85920 at a byte-loop GUARD(1100)). Index 0 (what sto_subarray
         * below extracts) is the first, small memo, so only a prefix of
         * this copy needs to be exact; an 8-byte tail rounding error is
         * harmless. */
        uint32_t k = 0;
        for (; GUARD(140), k + 8 <= len && k + 8 <= sizeof(memobuf); k += 8)
            UINT64_TO_BUF(memobuf + k, UINT64_FROM_BUF(sobj + off + k));
        memobuf_len = len;
    }

    BENCH_BEGIN(300)
    acc += sto_subarray(memobuf, memobuf_len, 0);

    BENCH_END
}

#elif defined(B_sto_emplace_tx)

static uint8_t sobj[4400];
static uint32_t sobj_len;
static uint8_t outbuf[4500];
static uint8_t newfield[34] = {0x50U, 17U};

int64_t
hook(uint32_t r)
{
    otxn_slot(1);
    sobj_len = (uint32_t)slot(sobj, sizeof(sobj), 1);

    BENCH_BEGIN(300)
    acc +=
        sto_emplace(SBUF(outbuf), sobj, sobj_len, SBUF(newfield), sfInvoiceID);

    BENCH_END
}

#elif defined(B_sto_erase_tx)

static uint8_t sobj[4400];
static uint32_t sobj_len;
static uint8_t outbuf[4500];

int64_t
hook(uint32_t r)
{
    otxn_slot(1);
    sobj_len = (uint32_t)slot(sobj, sizeof(sobj), 1);

    BENCH_BEGIN(300)
    acc += sto_erase(SBUF(outbuf), sobj, sobj_len, sfSequence);

    BENCH_END
}

#elif defined(B_state_foreign_r_32)

/* state_foreign requires an explicit 32B namespace whenever a foreign
 * account is passed (applyHook.cpp: is_foreign && nread_len==0 ->
 * INVALID_ARGUMENT) -- nread_len=0 only means "use my own namespace" for
 * LOCAL (non-foreign) reads. bob's keys live in his default namespace
 * (all-zero, hso() pins HookNamespace=0), so pass that explicitly. */
static uint8_t key[32];
static uint8_t facc[20];
static uint8_t ns[32] = {0};
static uint8_t out[32];

int64_t
hook(uint32_t r)
{
    otxn_param(SBUF(facc), "F", 1);

    BENCH_BEGIN(256)
    UINT32_TO_BUF(key, i);
    acc += state_foreign(SBUF(out), SBUF(key), SBUF(ns), (uint32_t)facc, 20);

    BENCH_END
}

#elif defined(B_state_foreign_r_256)

static uint8_t key[32];
static uint8_t facc[20];
static uint8_t ns[32] = {0};
static uint8_t out[256];

int64_t
hook(uint32_t r)
{
    otxn_param(SBUF(facc), "F", 1);

    BENCH_BEGIN(256)
    UINT32_TO_BUF(key, i);
    acc += state_foreign(SBUF(out), SBUF(key), SBUF(ns), (uint32_t)facc, 20);

    BENCH_END
}

#elif defined(B_state_foreign_w)

/* state_foreign_set: same rule (applyHook.cpp line ~1398) -- a foreign
 * account with no namespace is INVALID_ARGUMENT. */
static uint8_t key[32];
static uint8_t facc[20];
static uint8_t ns[32] = {0};
static uint8_t val[32];

int64_t
hook(uint32_t r)
{
    otxn_param(SBUF(facc), "F", 1);

    BENCH_BEGIN(256)
    UINT32_TO_BUF(key, i);
    acc +=
        state_foreign_set(SBUF(val), SBUF(key), SBUF(ns), (uint32_t)facc, 20);

    BENCH_END
}

#elif defined(B_etxn_reserve_once)

int64_t
hook(uint32_t r)
{
    _g(1, 1);
    int64_t rv = etxn_reserve(1);
    accept(0, 0, rv);
    return 0;
}

#elif defined(B_hook_again_once)

int64_t
hook(uint32_t r)
{
    _g(1, 1);
    int64_t rv = hook_again();
    accept(0, 0, rv);
    return 0;
}

#elif defined(B_xpop_slot_k100)

/* Only fires meaningfully on a ttIMPORT transaction; explicit slots (1,2)
 * avoid the slot-exhaustion edge cases SetHook_test's test_xpop_slot
 * exercises (slot_into=0). */
int64_t
hook(uint32_t r)
{
    _g(1, 1);
    int64_t acc = 0;
    for (uint32_t i = 0; GUARD(150), i < 100; ++i)
    {
        acc += xpop_slot(1, 2);
    }
    if (acc < 0)
        rollback(0, 0, acc);
    accept(0, 0, acc);
    return 0;
}

#elif defined(B_meta_slot_k200)

/* The hook decides its own pass: strong pass calls hook_again() to
 * schedule the weak/AAW pass, which is where meta_slot() actually works
 * (meta_slot requires result.provisionalMeta, only present in the weak
 * pass -- HookAPI.cpp). Both passes run inside the same timed close; the
 * wrapper counter records whichever pass actually calls meta_slot. */
int64_t
hook(uint32_t r)
{
    _g(1, 1);
    if (meta_slot(1) == PREREQUISITE_NOT_MET)
    {
        hook_again();
        accept(0, 0, 1);
        return 0;
    }

    int64_t acc = 0;
    for (uint32_t i = 0; GUARD(256), i < 200; ++i)
    {
        acc += meta_slot(1);
    }
    if (acc < 0)
        rollback(0, 0, acc);
    accept(0, 0, acc);
    return 0;
}

#elif defined(B_etxn_nonce_k200)

static uint8_t nb[32];

int64_t
hook(uint32_t r)
{
    etxn_reserve(1);
    BENCH_BEGIN(256)
    acc += etxn_nonce(SBUF(nb));
    BENCH_END
}

#elif defined(B_util_verify_ed25519)

/* fixtures copied verbatim from SetHook_test.cpp test_util_verify */
static uint8_t pubkey_ed[] = {0xEDU, 0xD9U, 0xB3U, 0x59U, 0x98U, 0x02U, 0xB2U,
                              0x14U, 0xA9U, 0x9DU, 0x75U, 0x77U, 0x12U, 0xD6U,
                              0xABU, 0xDFU, 0x72U, 0xF8U, 0x3CU, 0x63U, 0xBBU,
                              0xD5U, 0x38U, 0x61U, 0x41U, 0x17U, 0x90U, 0xB1U,
                              0x3DU, 0x04U, 0xB2U, 0xC5U, 0xC9U};
static uint8_t sig_ed[] = {
    0x56U, 0x68U, 0x80U, 0x76U, 0x70U, 0xFEU, 0xCEU, 0x60U, 0x34U, 0xAFU, 0xD6U,
    0xCDU, 0x1BU, 0xB4U, 0xC6U, 0x60U, 0xAEU, 0x08U, 0x39U, 0x6DU, 0x6DU, 0x8BU,
    0x7DU, 0x22U, 0x71U, 0x3BU, 0xDAU, 0x26U, 0x43U, 0xC1U, 0xE1U, 0x91U, 0xC4U,
    0xE4U, 0x4DU, 0x8EU, 0x02U, 0xE8U, 0x57U, 0x8BU, 0x20U, 0x45U, 0xDAU, 0xD4U,
    0x8FU, 0x97U, 0xFCU, 0x16U, 0xF8U, 0x92U, 0x5BU, 0x6BU, 0x51U, 0xFBU, 0x3BU,
    0xE5U, 0x0FU, 0xB0U, 0x4BU, 0x3AU, 0x20U, 0x4CU, 0x53U, 0x04U};
static uint8_t vmsg[] = {0xDEU, 0xADU, 0xBEU, 0xEFU};

int64_t
hook(uint32_t r)
{
    _g(1, 1);
    int64_t first = util_verify(SBUF(vmsg), SBUF(sig_ed), SBUF(pubkey_ed));
    if (first != 1)
        rollback(0, 0, first);
    uint8_t nbuf[4];
    uint32_t n = (otxn_param(SBUF(nbuf), "N", 1) == 4)
        ? (uint32_t)UINT32_FROM_BUF(nbuf)
        : 0;
    int64_t acc = first;
    for (uint32_t i = 0; GUARD(300), i < n; ++i)
    {
        acc += util_verify(SBUF(vmsg), SBUF(sig_ed), SBUF(pubkey_ed));
    }
    if (acc < 0 && acc > -100000)
        rollback(0, 0, acc);
    accept(0, 0, acc);
    return 0;
}

#elif defined(B_util_verify_secp256k1)

static uint8_t pubkey_sec[] = {0x02U, 0xC7U, 0x38U, 0x7FU, 0xFCU, 0x25U, 0xC1U,
                               0x56U, 0xCAU, 0x7FU, 0x8AU, 0x6DU, 0x76U, 0x0CU,
                               0x8DU, 0x01U, 0xEFU, 0x64U, 0x2CU, 0xEEU, 0x9CU,
                               0xE4U, 0x68U, 0x0CU, 0x33U, 0xFFU, 0xB3U, 0xFFU,
                               0x39U, 0xAFU, 0xECU, 0xFEU, 0x70U};
static uint8_t sig_sec[] = {
    0x30U, 0x45U, 0x02U, 0x21U, 0x00U, 0x95U, 0x6EU, 0x7DU, 0x1FU, 0x01U, 0x16U,
    0xF1U, 0x65U, 0x00U, 0xD2U, 0xCCU, 0xD8U, 0x8DU, 0x2AU, 0x2FU, 0xEFU, 0xF6U,
    0x52U, 0x16U, 0x85U, 0x42U, 0xF4U, 0x4EU, 0x43U, 0xDBU, 0xE6U, 0xF4U, 0x53U,
    0xE8U, 0x03U, 0xB8U, 0x4FU, 0x02U, 0x20U, 0x0AU, 0xB6U, 0xC3U, 0x4BU, 0x5FU,
    0x0CU, 0xC6U, 0x6BU, 0x4FU, 0x1FU, 0x83U, 0xE9U, 0x89U, 0x74U, 0xB8U, 0x80U,
    0xA2U, 0x2FU, 0xAEU, 0x52U, 0x91U, 0x6BU, 0xA2U, 0xCEU, 0x96U, 0xA3U, 0x61U,
    0x05U, 0x3FU, 0xFFU, 0x81U, 0xE9U};
static uint8_t vmsg[] = {0xDEU, 0xADU, 0xBEU, 0xEFU};

int64_t
hook(uint32_t r)
{
    _g(1, 1);
    int64_t first = util_verify(SBUF(vmsg), SBUF(sig_sec), SBUF(pubkey_sec));
    if (first != 1)
        rollback(0, 0, first);
    uint8_t nbuf[4];
    uint32_t n = (otxn_param(SBUF(nbuf), "N", 1) == 4)
        ? (uint32_t)UINT32_FROM_BUF(nbuf)
        : 0;
    int64_t acc = first;
    for (uint32_t i = 0; GUARD(300), i < n; ++i)
    {
        acc += util_verify(SBUF(vmsg), SBUF(sig_sec), SBUF(pubkey_sec));
    }
    if (acc < 0 && acc > -100000)
        rollback(0, 0, acc);
    accept(0, 0, acc);
    return 0;
}

#elif defined(B_hook_skip_alt)

static uint8_t otherhash[32];

int64_t
hook(uint32_t r)
{
    hook_hash(SBUF(otherhash), 1);
    BENCH_BEGIN(300)
    acc += hook_skip(SBUF(otherhash), (i & 1) ? 1 : 0);
    BENCH_END
}

#elif defined(B_ledger_nonce_k200)

static uint8_t nb[32];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(256)
    acc += ledger_nonce(SBUF(nb));

    BENCH_END
}

#elif defined(B_hook_param_set_k16)

static uint8_t key[4];
static uint8_t val[2] = "V";
static uint8_t hash32[32];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(16)
    UINT32_TO_BUF(key, i);
    acc += hook_param_set(SBUF(val), SBUF(key), SBUF(hash32));

    BENCH_END
}

#elif defined(B_ledger_keylet)

/* lo/hi must be well-formed keylet buffers (2-byte type + 32-byte key) that
 * unserialize_keylet() accepts, or it's an immediate INVALID_ARGUMENT
 * (all-zero/all-0xFF don't decode to a valid ltXXX type). Bracket the
 * hook's own AccountRoot keylet: lo = that keylet with the last hash byte
 * cleared, hi = same with the last hash byte set to 0xFF, so a real entry
 * (the account itself) sits inside the range. */
static uint8_t acc20[20];
static uint8_t lo[34];
static uint8_t hi[34];
static uint8_t outbuf[34];

int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    util_keylet(
        SBUF(lo), 3 /*KEYLET_ACCOUNT*/, (uint32_t)acc20, 20, 0, 0, 0, 0);
    for (int k = 0; k < 34; ++k)
        hi[k] = lo[k];
    lo[33] = 0x00;
    hi[33] = 0xFF;

    BENCH_BEGIN(300)
    acc += ledger_keylet(SBUF(outbuf), SBUF(lo), SBUF(hi));

    BENCH_END
}

#elif defined(B_prepare_min)

/* prepare() takes a small partial serialized tx (TT+Flags+TagSrc+TagDst+
 * Amount+DestAccount, 49B) and returns a complete one -- same fields
 * PREPARE_PAYMENT_SIMPLE builds by hand, minus the etxn_details/
 * etxn_fee_base+refill steps (that's precisely what prepare() replaces). */
static uint8_t dest[20];
static uint8_t outbuf[1000];

int64_t
hook(uint32_t r)
{
    otxn_param(SBUF(dest), "D", 1);
    etxn_reserve(1);

    BENCH_BEGIN(300)
    uint8_t buf[49];
    uint8_t* buf_tx = buf;
    _01_02_ENCODE_TT(buf_tx, 0 /*ttPAYMENT*/);
    _02_02_ENCODE_FLAGS(buf_tx, 0x80000000UL);
    _02_03_ENCODE_TAG_SRC(buf_tx, 0);
    _02_14_ENCODE_TAG_DST(buf_tx, 0);
    _06_01_ENCODE_DROPS_AMOUNT(buf_tx, 1);
    _08_03_ENCODE_ACCOUNT_DST(buf_tx, dest);
    acc += prepare(SBUF(outbuf), SBUF(buf));

    BENCH_END
}

#elif defined(B_emit_min_k200)

static uint8_t dest[20];
static uint8_t tx[PREPARE_PAYMENT_SIMPLE_SIZE];
static uint8_t hashout[32];

int64_t
hook(uint32_t r)
{
    otxn_param(SBUF(dest), "D", 1);
    etxn_reserve(200);

    BENCH_BEGIN(256)
    PREPARE_PAYMENT_SIMPLE(tx, 1, dest, 0, 0)
    acc += emit(SBUF(hashout), SBUF(tx));

    BENCH_END
}

#elif defined(B_state_w_setup_4k)

static uint8_t key[32];
static uint8_t val[4096];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(256)
    UINT32_TO_BUF(key, i);
    val[0] = (uint8_t)i;
    acc += state_set(SBUF(val), SBUF(key));

    BENCH_END
}

#elif defined(B_state_r_4k)

static uint8_t key[32];
static uint8_t out[4096];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(256)
    UINT32_TO_BUF(key, i);
    acc += state(SBUF(out), SBUF(key));

    BENCH_END
}

#elif defined(B_state_w_4k)

static uint8_t key[32];
static uint8_t val[4096];

int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(256)
    UINT32_TO_BUF(key, i);
    val[0] = (uint8_t)(acc);
    acc += state_set(SBUF(val), SBUF(key));

    BENCH_END
}

#elif defined(B_util_keylet_hook)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 1, (uint32_t)acc20, 20, 0, 0, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_hook_state)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    hook_hash(SBUF(hash32b), -1);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(
        SBUF(klbuf),
        2,
        (uint32_t)acc20,
        20,
        (uint32_t)hash32,
        32,
        (uint32_t)hash32b,
        32))
    BENCH_END
}

#elif defined(B_util_keylet_skip)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 6, 0, 0, 0, 0, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_offer)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 10, (uint32_t)acc20, 20, 1, 0, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_signers)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 14, (uint32_t)acc20, 20, 0, 0, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_check)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 15, (uint32_t)acc20, 20, 1, 0, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_deposit_preauth)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    for (int k = 0; k < 20; ++k)
        acc20b[k] = (uint8_t)(k + 1);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(
        SBUF(klbuf), 16, (uint32_t)acc20, 20, (uint32_t)acc20b, 20, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_unchecked)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 17, (uint32_t)hash32, 32, 0, 0, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_owner_dir)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 18, (uint32_t)acc20, 20, 0, 0, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_page)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 19, (uint32_t)hash32, 32, 1, 0, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_paychan)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    for (int k = 0; k < 20; ++k)
        acc20b[k] = (uint8_t)(k + 1);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(
        SBUF(klbuf), 21, (uint32_t)acc20, 20, (uint32_t)acc20b, 20, 1, 0))
    BENCH_END
}

#elif defined(B_util_keylet_emitted_txn)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 22, (uint32_t)hash32, 32, 0, 0, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_nft_offer)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 23, (uint32_t)acc20, 20, 1, 0, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_hook_definition)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 24, (uint32_t)hash32, 32, 0, 0, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_hook_state_dir)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(
        SBUF(klbuf), 25, (uint32_t)acc20, 20, (uint32_t)hash32, 32, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_cron)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 26, (uint32_t)acc20, 20, 1, 0, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_did)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 31, (uint32_t)acc20, 20, 0, 0, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_oracle)
static uint8_t acc20[20];
static uint8_t acc20b[20];
static uint8_t hash32[32];
static uint8_t hash32b[32];
static uint8_t klbuf[34];
int64_t
hook(uint32_t r)
{
    hook_account(SBUF(acc20));
    hook_hash(SBUF(hash32), 0);
    BENCH_BEGIN(300)
    BENCH4(util_keylet(SBUF(klbuf), 32, (uint32_t)acc20, 20, 1, 0, 0, 0))
    BENCH_END
}

#elif defined(B_util_keylet_amm)

/* keylet_code::AMM (27) takes two 40-byte assets (20B currency + 20B
 * issuer). issue1 = XRP (all-zero currency + issuer), issue2 = a "USD" IOU
 * issued by the hook's own account -- neither asset nor any AMM object
 * needs to actually exist in the ledger, util_keylet only computes a hash. */
static uint8_t issue1[40] = {0};
static uint8_t issue2[40] = {0};
static uint8_t klbuf[34];

int64_t
hook(uint32_t r)
{
    uint8_t acc20[20];
    hook_account(SBUF(acc20));
    issue2[12] = 'U';
    issue2[13] = 'S';
    issue2[14] = 'D';
    for (int k = 0; k < 20; ++k)
        issue2[20 + k] = acc20[k];

    int64_t first = util_keylet(
        SBUF(klbuf), 27, (uint32_t)issue1, 40, (uint32_t)issue2, 40, 0, 0);
    if (first != 34)
        rollback(0, 0, first);

    BENCH_BEGIN(300)
    BENCH4(util_keylet(
        SBUF(klbuf), 27, (uint32_t)issue1, 40, (uint32_t)issue2, 40, 0, 0))
    BENCH_END
}

#elif defined(B_prepare_1k)

/* Same idempotency argument as prepare_min: the 1KiB ttINVOKE+sfBlob buffer
 * is built once, then prepare()d repeatedly. */
static uint8_t tx1k[PREPARE_INVOKE_BLOB_SIZE(1024)];
static uint8_t outbuf[PREPARE_INVOKE_BLOB_SIZE(1024) + 64];

int64_t
hook(uint32_t r)
{
    etxn_reserve(1);
    PREPARE_INVOKE_BLOB(tx1k, 1024)

    int64_t first = prepare(SBUF(outbuf), SBUF(tx1k));
    if (first <= 0)
        rollback(0, 0, first);

    uint8_t nbuf[4];
    uint32_t n = (otxn_param(SBUF(nbuf), "N", 1) == 4)
        ? (uint32_t)UINT32_FROM_BUF(nbuf)
        : 0;
    int64_t acc = first;
    for (uint32_t i = 0; GUARD(300), i < n; ++i)
        acc += prepare(SBUF(outbuf), SBUF(tx1k));

    if (acc < 0 && acc > -100000)
        rollback(0, 0, acc);
    accept(0, 0, acc);
    return 0;
}

#elif defined(B_etxn_fee_base_1k)

static uint8_t tx1k[PREPARE_INVOKE_BLOB_SIZE(1024)];

int64_t
hook(uint32_t r)
{
    etxn_reserve(1);
    PREPARE_INVOKE_BLOB(tx1k, 1024)

    int64_t first = etxn_fee_base(SBUF(tx1k));
    if (first <= 0)
        rollback(0, 0, first);

    uint8_t nbuf[4];
    uint32_t n = (otxn_param(SBUF(nbuf), "N", 1) == 4)
        ? (uint32_t)UINT32_FROM_BUF(nbuf)
        : 0;
    int64_t acc = first;
    for (uint32_t i = 0; GUARD(300), i < n; ++i)
        acc += etxn_fee_base(SBUF(tx1k));

    if (acc < 0 && acc > -100000)
        rollback(0, 0, acc);
    accept(0, 0, acc);
    return 0;
}

#elif defined(B_emit_1k_k200)

/* Same structure as emit_min_k200 (a fresh tx -- fresh nonce/EmitDetails --
 * per emit()), but a 1KiB ttINVOKE+sfBlob buffer. An emitted Invoke needs no
 * destination account/hooks, so unlike emit_min_k200 no "D" param is read. */
static uint8_t tx1k[PREPARE_INVOKE_BLOB_SIZE(1024)];
static uint8_t hashout[32];

int64_t
hook(uint32_t r)
{
    etxn_reserve(200);

    BENCH_BEGIN(256)
    PREPARE_INVOKE_BLOB(tx1k, 1024)
    acc += emit(SBUF(hashout), SBUF(tx1k));

    BENCH_END
}

#else
#error "hookcost.c: no B_<name> section selected (pass -DB_<name>)"
#endif
