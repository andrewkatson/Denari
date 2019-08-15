// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once
//header file to store events for when a block is mined or the block chain was updated.
namespace Miner {

enum class MinerEventType: uint8_t {
  BLOCK_MINED,
  BLOCKCHAIN_UPDATED,
};
//holder struct for the enum of miner events
struct MinerEvent {
  MinerEventType type;
};

} //namespace Miner
