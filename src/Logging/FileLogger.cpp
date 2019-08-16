// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "FileLogger.h"
//A version of the logger that writes to a specific file
namespace Logging {

FileLogger::FileLogger(Level level) : StreamLogger(level) {
}

void FileLogger::init(const std::string& fileName) {
  fileStream.open(fileName, std::ios::app);
  StreamLogger::attachToStream(fileStream);
}

}
