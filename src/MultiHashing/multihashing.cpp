#include "multihashing.h"

static void cn_slow_hash_multi (const void *data, size_t length, void *hash, int variant, int height)
{
    init_ctx();
    switch (variant) {
       case 0:  cryptonight_single_hash<xmrig::CRYPTONIGHT, SOFT_AES, xmrig::VARIANT_0>  (reinterpret_cast<const uint8_t*>(data), length, reinterpret_cast<uint8_t*>(hash), &ctx, height);
                break;
       case 1:  cryptonight_single_hash<xmrig::CRYPTONIGHT, SOFT_AES, xmrig::VARIANT_1>  (reinterpret_cast<const uint8_t*>(data), length, reinterpret_cast<uint8_t*>(hash), &ctx, height);
                break;
       case 3:  cryptonight_single_hash<xmrig::CRYPTONIGHT, SOFT_AES, xmrig::VARIANT_XTL>(reinterpret_cast<const uint8_t*>(data), length, reinterpret_cast<uint8_t*>(hash), &ctx, height);
                break;
       case 4:  cryptonight_single_hash<xmrig::CRYPTONIGHT, SOFT_AES, xmrig::VARIANT_MSR>(reinterpret_cast<const uint8_t*>(data), length, reinterpret_cast<uint8_t*>(hash), &ctx, height);
                break;
       case 6:  cryptonight_single_hash<xmrig::CRYPTONIGHT, SOFT_AES, xmrig::VARIANT_XAO>(reinterpret_cast<const uint8_t*>(data), length, reinterpret_cast<uint8_t*>(hash), &ctx, height);
                break;
       case 7:  cryptonight_single_hash<xmrig::CRYPTONIGHT, SOFT_AES, xmrig::VARIANT_RTO>(reinterpret_cast<const uint8_t*>(data), length, reinterpret_cast<uint8_t*>(hash), &ctx, height);
                break;
        default:   
            cryptonight_single_hash<xmrig::CRYPTONIGHT, SOFT_AES, xmrig::VARIANT_0>  (reinterpret_cast<const uint8_t*>(data), length, reinterpret_cast<uint8_t*>(hash), &ctx, height);
    }
}

