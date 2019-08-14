// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

// 08/13/19
// @Commentor: Nick Thomas

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
  * @param: blockMiningParameters (struct containing blockTemplate & difficulty), threadCount (size_t discription for number of threads)
  * Return: Block (TODO)
  * TODO: describe thread count; locate block
  */
  Block mine(const BlockMiningParameters& blockMiningParameters, size_t threadCount);

  //NOTE! this is blocking method
  void stop();

private:
  /*
  * @attributes: m_dispatcher (is a Dispatcher), m_miningStopped (is an event)
  * TODO: got to system to identify Dispatcher and Event
  */
  System::Dispatcher& m_dispatcher;
  System::Event m_miningStopped;

  /* 
  * MiningState is an enum array that inherits from the 8 bit integer 
  * it hold values to determine if mining has stopped, block is found, and if mining is in progress
  */
  enum class MiningState : uint8_t { MINING_STOPPED, BLOCK_FOUND, MINING_IN_PROGRESS};
  /* 
  * m_state is a list of atomic MiningState variables. 
  * Atomic variables prevent overlaps from occuring during multithreading 
  */
  std::atomic<MiningState> m_state;

  /*
  * m_workers is a vector of smart pointers determined by RemoteContext()
  * smart pointers are pointers that delete themselves and clear memory when they go out of scope
  * TODO: Identify RemoteContext<void> for more detailed description
  */
  std::vector<std::unique_ptr<System::RemoteContext<void>>>  m_workers;

  /* m_block is a Block */
  Block m_block;

 /* m_logger is a logger */
  Logging::LoggerRef m_logger;

  /*
  * @param: blockMiningParameters (struct with blockTemplate and Difficulty), threadCount (size_t number of threads)
  * return:
  */
  void runWorkers(BlockMiningParameters blockMiningParameters, size_t threadCount);
  /* 
  * @params: blockTemplate (it is a variable to rep a block), difficulty (it is the difficulty), nonceStep (32 bit float. Use as one time number for hash)
  * reutrn:
  * Note: Nonce literally means number used once
  * TODO: describe block template and confirm difficutly type
  */
  void workerFunc(const Block& blockTemplate, difficulty_type difficulty, uint32_t nonceStep);
  /* 
  * @params:
  * return: True or False 
  * identifies if the state block has been found
  */
  bool setStateBlockFound();
};

} //namespace CryptoNote
