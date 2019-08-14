// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstdint>
#include <vector>

#include "crypto/hash.h"

namespace CryptoNote
{
    typedef std::uint64_t difficulty_type;
    /*
     * @brief checks if a hash fits the given difficulty
     *
     * The hash passes if (hash * difficulty) < 2^256.
     * Phrased differently, if (hash * difficulty) fits without overflow into
     * the least significant 256 bits of the 320 bit multiplication result.
     *
     * @param hash the hash to check
     * @param difficulty the difficulty to check against
     *
     * @return true if valid, else false
     */
    bool check_hash(const Crypto::Hash &hash, difficulty_type difficulty);
}
