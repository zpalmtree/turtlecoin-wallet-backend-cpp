// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2014-2018, The Monero Project
// Copyright (c) 2018-2019, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information.

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <limits>
#include <initializer_list>

namespace CryptoNote {
namespace parameters {

const uint64_t DIFFICULTY_TARGET                             = 30; // seconds

const uint32_t CRYPTONOTE_MAX_BLOCK_NUMBER                   = 500000000;
const uint64_t CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX       = 3914525;
const uint64_t CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT            = 60 * 60 * 2;
const uint64_t CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT_V3         = 3 * DIFFICULTY_TARGET;
const uint64_t CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT_V4         = 6 * DIFFICULTY_TARGET;

/* This is the unix timestamp of the first "mined" block (technically block 2, not the genesis block)
   You can get this value by doing "print_block 2" in TurtleCoind. It is used to know what timestamp
   to import from when the block height cannot be found in the node or the node is offline. */
const uint64_t GENESIS_BLOCK_TIMESTAMP                       = 1512800692;

const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE     = 100000; //size of block (bytes) after which reward for block calculated using block size
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE;
const size_t   CRYPTONOTE_COINBASE_BLOB_RESERVED_SIZE        = 600;

const size_t   CRYPTONOTE_DISPLAY_DECIMAL_POINT              = 2;

const uint64_t MINIMUM_FEE                                   = UINT64_C(10);

/* This section defines our minimum and maximum mixin counts required for transactions */
const uint64_t MINIMUM_MIXIN_V1                              = 0;
const uint64_t MAXIMUM_MIXIN_V1                              = 100;

const uint64_t MINIMUM_MIXIN_V2                              = 7;
const uint64_t MAXIMUM_MIXIN_V2                              = 7;

const uint64_t MINIMUM_MIXIN_V3                              = 3;
const uint64_t MAXIMUM_MIXIN_V3                              = 3;

/* The heights to activate the mixin limits at */
const uint32_t MIXIN_LIMITS_V1_HEIGHT                        = 440000;
const uint32_t MIXIN_LIMITS_V2_HEIGHT                        = 620000;
const uint32_t MIXIN_LIMITS_V3_HEIGHT                        = 800000;

/* The mixin to use by default with zedwallet and turtle-service */
/* DEFAULT_MIXIN_V0 is the mixin used before MIXIN_LIMITS_V1_HEIGHT is started */
const uint64_t DEFAULT_MIXIN_V0                              = 3;
const uint64_t DEFAULT_MIXIN_V1                              = MAXIMUM_MIXIN_V1;
const uint64_t DEFAULT_MIXIN_V2                              = MAXIMUM_MIXIN_V2;
const uint64_t DEFAULT_MIXIN_V3                              = MAXIMUM_MIXIN_V3;

const uint64_t EXPECTED_NUMBER_OF_BLOCKS_PER_DAY             = 24 * 60 * 60 / DIFFICULTY_TARGET;

const size_t   MAX_BLOCK_SIZE_INITIAL                        = 100000;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_NUMERATOR         = 100 * 1024;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_DENOMINATOR       = 365 * 24 * 60 * 60 / DIFFICULTY_TARGET;
const uint64_t MAX_EXTRA_SIZE                                = 140000;

/* This describes how many blocks of "wiggle" room transactions have regarding
   when the outputs can be spent based on a reasonable belief that the outputs
   would unlock in the current block period */
const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS     = 1;
const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS    = DIFFICULTY_TARGET * CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS;

const size_t   FUSION_TX_MAX_SIZE                            = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT * 30 / 100;
const size_t   FUSION_TX_MIN_INPUT_COUNT                     = 12;
const size_t   FUSION_TX_MIN_IN_OUT_COUNT_RATIO              = 4;

/* Block heights we are going to have hard forks at */
const uint64_t FORK_HEIGHTS[] =
{
    187000,  // 0
    350000,  // 1
    440000,  // 2
    620000,  // 3
    700000,  // 4
    800000,  // 5
    1000000, // 6
    1200000, // 7
    1300000, // 8
    1400000, // 9
    1600000, // 10
    1800000, // 11
    2000000, // 12
};

/* MAKE SURE TO UPDATE THIS VALUE WITH EVERY MAJOR RELEASE BEFORE A FORK */
const uint64_t SOFTWARE_SUPPORTED_FORK_INDEX                 = 9;

const uint64_t FORK_HEIGHTS_SIZE = sizeof(FORK_HEIGHTS) / sizeof(*FORK_HEIGHTS);

/* The index in the FORK_HEIGHTS array that this version of the software will
   support. For example, if CURRENT_FORK_INDEX is 3, this version of the
   software will support the fork at 600,000 blocks.

   This will default to zero if the FORK_HEIGHTS array is empty, so you don't
   need to change it manually. */
const uint8_t CURRENT_FORK_INDEX = FORK_HEIGHTS_SIZE == 0 ? 0 : SOFTWARE_SUPPORTED_FORK_INDEX;

static_assert(CURRENT_FORK_INDEX >= 0, "CURRENT FORK INDEX must be >= 0");
/* Make sure CURRENT_FORK_INDEX is a valid index, unless FORK_HEIGHTS is empty */
static_assert(FORK_HEIGHTS_SIZE == 0 || CURRENT_FORK_INDEX < FORK_HEIGHTS_SIZE, "CURRENT_FORK_INDEX out of range of FORK_HEIGHTS!");

} // parameters

const char     CRYPTONOTE_NAME[]                             = "TurtleCoin";

const uint8_t  TRANSACTION_VERSION_1                         =  1;
const uint8_t  TRANSACTION_VERSION_2                         =  2;
const uint8_t  CURRENT_TRANSACTION_VERSION                   =  TRANSACTION_VERSION_1;

const uint8_t  BLOCK_MAJOR_VERSION_1                         =  1;
const uint8_t  BLOCK_MAJOR_VERSION_2                         =  2;
const uint8_t  BLOCK_MAJOR_VERSION_3                         =  3;
const uint8_t  BLOCK_MAJOR_VERSION_4                         =  4;
const uint8_t  BLOCK_MAJOR_VERSION_5                         =  5;

const uint8_t  BLOCK_MINOR_VERSION_0                         =  0;
const uint8_t  BLOCK_MINOR_VERSION_1                         =  1;

const uint64_t BLOCKS_SYNCHRONIZING_DEFAULT_COUNT            =  100;    //by default, blocks count in blocks downloading

const int      RPC_DEFAULT_PORT                              =  11898;
const int      SERVICE_DEFAULT_PORT                          =  8070;

const char     LATEST_VERSION_URL[]                          = "http://latest.turtlecoin.lol";
const std::string LICENSE_URL                                = "https://github.com/turtlecoin/turtlecoin/blob/master/LICENSE";

} // CryptoNote
