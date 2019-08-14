// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <atomic>
#include <thread>

#include <System/Dispatcher.h>
#include <System/Event.h>
#include <System/RemoteContext.h>

#include "CryptoNote.h"
#include "CryptoNoteCore/Difficulty.h"

#include "Logging/LoggerRef.h"

namespace CryptoNote {

/* Struct members are public -> blockTemplate and difficulty are public */
/* TODO: Define Block, Define difficulty_type */
struct BlockMiningParameters {
  Block blockTemplate;
  difficulty_type difficulty;
};

/*
* TODO: Describe all atributes and methods in miner
*/
class Miner {
public:

  /* 
  * Miner constructor 
  * @param: dispatcher (TODO), logger (TODO)
  * TODO: describe dispatcher and logger
  */
  Miner(System::Dispatcher& dispatcher, Logging::ILogger& logger);
  /* ~Miner function
  * @param: 
  */
  ~Miner();

  /* 
  * @param: blockMiningParameters (struct containing blockTemplate & difficulty), threadCount (size_t variable)
  * Return: Block (TODO)
  * TODO: describe thread count; locate block
  */
  Block mine(const BlockMiningParameters& blockMiningParameters, size_t threadCount);

  //NOTE! this is blocking method
  void stop();

private:
  /*
  * atr*/
  System::Dispatcher& m_dispatcher;
  System::Event m_miningStopped;

  enum class MiningState : uint8_t { MINING_STOPPED, BLOCK_FOUND, MINING_IN_PROGRESS};
  std::atomic<MiningState> m_state;

  std::vector<std::unique_ptr<System::RemoteContext<void>>>  m_workers;

  Block m_block;

  Logging::LoggerRef m_logger;

  void runWorkers(BlockMiningParameters blockMiningParameters, size_t threadCount);
  void workerFunc(const Block& blockTemplate, difficulty_type difficulty, uint32_t nonceStep);
  bool setStateBlockFound();
};

} //namespace CryptoNote
