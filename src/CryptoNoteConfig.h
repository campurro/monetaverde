// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
//
// This file is part of Bytecoin.
//
// Bytecoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Bytecoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>

namespace CryptoNote {
namespace parameters {

const uint32_t CRYPTONOTE_MAX_BLOCK_NUMBER                   = 500000000;
const size_t   CRYPTONOTE_MAX_BLOCK_BLOB_SIZE                = 500000000;
const size_t   CRYPTONOTE_MAX_TX_SIZE                        = 1000000000;
const uint64_t CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX       = 6699; // addresses start with "Vd"
const uint32_t CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW          = 60;
const uint64_t CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT            = 60 * 60 * 2; // 525; // T*N/20

const size_t   BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW             = 60;
const size_t   BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW_V4          = 11;

// MONEY_SUPPLY - total number coins to be generated
const uint64_t MONEY_SUPPLY                                  = static_cast<uint64_t>(-1);
const size_t CRYPTONOTE_COIN_VERSION                         = 0;
const unsigned EMISSION_SPEED_FACTOR                         = 23;

// mandatory mixin V4
const uint8_t MANDATORY_MIXIN_BLOCK_VERSION                  = 4;
const size_t MIN_MIXIN                                       = 1;
const size_t MAX_MIXIN                                       = 101;


static_assert(EMISSION_SPEED_FACTOR <= 8 * sizeof(uint64_t), "Bad EMISSION_SPEED_FACTOR");

const size_t   CRYPTONOTE_REWARD_BLOCKS_WINDOW               = 100;
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE     = 20000;
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1  = 20000;
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE; // increasing to allow bigger tx
const size_t   CRYPTONOTE_COINBASE_BLOB_RESERVED_SIZE        = 600;
const size_t   CRYPTONOTE_DISPLAY_DECIMAL_POINT              = 12;
const uint64_t MINIMUM_FEE                                   = UINT64_C(1000000);    // pow(10, 6)
const uint64_t DEFAULT_DUST_THRESHOLD                        = UINT64_C(1000000);    // pow(10, 6)

const uint64_t DIFFICULTY_TARGET                             = 60;
const uint64_t EXPECTED_NUMBER_OF_BLOCKS_PER_DAY             = 24 * 60 * 60 / DIFFICULTY_TARGET;
const size_t   DIFFICULTY_WINDOW                             = 720; //EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;
const size_t   DIFFICULTY_WINDOW_V2                          = 720;
const size_t   DIFFICULTY_WINDOW_V4                          = 720;
const size_t   DIFFICULTY_CUT                                = 60;
const size_t   DIFFICULTY_LAG                                = 15;
const size_t   DIFFICULTY_LAG_V2                             = 15;
#define DIFFICULTY_BLOCKS_COUNT                         parameters::DIFFICULTY_WINDOW + parameters::DIFFICULTY_LAG
static_assert(2 * DIFFICULTY_CUT <= DIFFICULTY_WINDOW - 2, "Bad DIFFICULTY_WINDOW or DIFFICULTY_CUT");

const size_t   MAX_BLOCK_SIZE_INITIAL                        =  1000000;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_NUMERATOR         = 100 * 1024;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_DENOMINATOR       = 365 * 24 * 60 * 60 / DIFFICULTY_TARGET;

const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS     = 1;
const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS    = DIFFICULTY_TARGET * CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS;

const uint64_t CRYPTONOTE_MEMPOOL_TX_LIVETIME                = 60 * 60 * 24;
const uint64_t CRYPTONOTE_MEMPOOL_TX_FROM_ALT_BLOCK_LIVETIME = 60 * 60 * 24 * 7;
const uint64_t CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL = 7;

const size_t   FUSION_TX_MAX_SIZE                            = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT * 15 / 100;
const size_t   FUSION_TX_MIN_INPUT_COUNT                     = 12;
const size_t   FUSION_TX_MIN_IN_OUT_COUNT_RATIO              = 4;

const uint32_t UPGRADE_HEIGHT_V2                             = 0;
const uint32_t UPGRADE_HEIGHT_V3                             = static_cast<uint32_t>(-1);
const uint32_t UPGRADE_HEIGHT_V4                             = static_cast<uint32_t>(-1);
const unsigned UPGRADE_VOTING_THRESHOLD                      = 90;               // percent
const uint32_t UPGRADE_VOTING_WINDOW                         = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;  // blocks
const uint32_t UPGRADE_WINDOW                                = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;  // blocks
static_assert(0 < UPGRADE_VOTING_THRESHOLD && UPGRADE_VOTING_THRESHOLD <= 100, "Bad UPGRADE_VOTING_THRESHOLD");
static_assert(UPGRADE_VOTING_WINDOW > 1, "Bad UPGRADE_VOTING_WINDOW");

const char     CRYPTONOTE_BLOCKS_FILENAME[]                  = "blocks.dat";
const char     CRYPTONOTE_BLOCKINDEXES_FILENAME[]            = "blockindexes.dat";
const char     CRYPTONOTE_POOLDATA_FILENAME[]                = "poolstate.dat";
const char     P2P_NET_DATA_FILENAME[]                       = "p2pstate.dat";
const char     MINER_CONFIG_FILE_NAME[]                      = "miner_conf.json";

// testnet setup
const uint32_t TESTNET_UPGRADE_HEIGHT_V2                             = 2;
const uint32_t TESTNET_UPGRADE_HEIGHT_V3                             = 5;
const uint32_t TESTNET_UPGRADE_HEIGHT_V4                             = 10;
const uint64_t TESTNET_DIFFICULTY_TARGET                             = 15; // target in testnet mode

} // parameters

const char     CRYPTONOTE_NAME[]                             = "monetaverde";
const char     GENESIS_COINBASE_TX_HEX[]                     = "013c01ff00002101274a48ea82cb5d54547e6dd7ed87af943761d82c9050f60f56da4a7e71baa2f5";

const uint8_t  TRANSACTION_VERSION_1                         =  1;
const uint8_t  TRANSACTION_VERSION_2                         =  2;
const uint8_t  CURRENT_TRANSACTION_VERSION                   =  TRANSACTION_VERSION_1;
const uint8_t  BLOCK_MAJOR_VERSION_1                         =  1;
const uint8_t  BLOCK_MAJOR_VERSION_2                         =  2;
const uint8_t  BLOCK_MAJOR_VERSION_3                         =  3;
const uint8_t  BLOCK_MAJOR_VERSION_4                         =  4;
const uint8_t  BLOCK_MINOR_VERSION_0                         =  0;
const uint8_t  BLOCK_MINOR_VERSION_1                         =  1;

const size_t   BLOCKS_IDS_SYNCHRONIZING_DEFAULT_COUNT        =  10000;  //by default, blocks ids count in synchronizing
const size_t   BLOCKS_SYNCHRONIZING_DEFAULT_COUNT            =  300;    //by default, blocks count in blocks downloading
const size_t   COMMAND_RPC_GET_BLOCKS_FAST_MAX_COUNT         =  1000;

const int      P2P_DEFAULT_PORT                              =  26080;
const int      RPC_DEFAULT_PORT                              =  26081;

const size_t   P2P_LOCAL_WHITE_PEERLIST_LIMIT                =  1000;
const size_t   P2P_LOCAL_GRAY_PEERLIST_LIMIT                 =  5000;

const size_t   P2P_CONNECTION_MAX_WRITE_BUFFER_SIZE          = 64 * 1024 * 1024; // 64 MB
const uint32_t P2P_DEFAULT_CONNECTIONS_COUNT                 = 8;
const size_t   P2P_DEFAULT_WHITELIST_CONNECTIONS_PERCENT     = 70;
const uint32_t P2P_DEFAULT_HANDSHAKE_INTERVAL                = 60;            // seconds
const uint32_t P2P_DEFAULT_PACKET_MAX_SIZE                   = 100000000;      // 50000000 bytes maximum packet size
const uint32_t P2P_DEFAULT_PEERS_IN_HANDSHAKE                = 250;
const uint32_t P2P_DEFAULT_CONNECTION_TIMEOUT                = 5000;          // 5 seconds
const uint32_t P2P_DEFAULT_PING_CONNECTION_TIMEOUT           = 2000;          // 2 seconds
const uint64_t P2P_DEFAULT_INVOKE_TIMEOUT                    = 60 * 2 * 1000; // 2 minutes
const size_t   P2P_DEFAULT_HANDSHAKE_INVOKE_TIMEOUT          = 5000;          // 5 seconds
const char     P2P_STAT_TRUSTED_PUB_KEY[]                    = "db9eabe971890012a4071a96468155c2c360f80d18e73caa97bffd3b7381eed7";

const char* const SEED_NODES[] = {
  "176.9.47.243:8580",
  "66.85.133.156:26080",
  "35.227.28.16:26080",

  "144.217.84.27:26080",
  "51.38.127.186:26080"
};


struct CheckpointData {
    uint32_t index;
    const char* blockId;
};

const std::initializer_list<CheckpointData> CHECKPOINTS = {
    {200000, "23f18774eee12a43c80d7162fba4d5fb10290128f31890a7cd0ff6c4e2948277"},
    {400000, "a1d34d9e229c6e425f7a9d5dfa1fa35525e3f387ed664a04c6ef5cc609357057"},
    {600000, "2a9461eb7ae8a934a111b2e9f570e81efaf02c5382a9c707cadce88e768a9205"},
    {800000, "a1ed05e9671acce3cfa7dd283f0be5320b8d626fe84be4703fc8d3be95ffcc59"},
    {1000000, "d410152f30e4c21e0bc1d82ee80f757fd2223e8a1636774b8759101f4f21dd91"},
    {1500000, "23e3e5273df28de9036b7336894578873257e1b1a2d2d14ab9945b7333ce8707"},
    {2000000, "2d5892e15d7b2066d0b26aa150c4419676dbf7678d220b2d111c74c54c0fe6ad"},
    {2100000, "8246ae723a4581483d2ebd76d4d0c54d342373e94d762d910cc375f453bd1f18"}
};

} // CryptoNote

#define ALLOW_DEBUG_COMMANDS
