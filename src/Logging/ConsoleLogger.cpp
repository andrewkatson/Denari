// Copyright (c) 2011-2016 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ConsoleLogger.h"
#include <iostream>
#include <unordered_map>
#include <Common/ConsoleTools.h>


namespace Logging {

using Common::Console::Color;

ConsoleLogger::ConsoleLogger(Level level) : CommonLogger(level) {
}

void ConsoleLogger::doLogString(const std::string& message) {
  //need a lock since there could be multiple loggers operating on this message
  std::lock_guard<std::mutex> lock(mutex);
  //bool on whether it is reading text or color information
  bool readingText = true;
  //bool to detect when the color shifts
  bool changedColor = false;
  //the current color as a string
  std::string color = "";
  //map to quickly get any of the Color class versions of the color to be used.
  static std::unordered_map<std::string, Color> colorMapping = {
    { BLUE, Color::Blue },
    { GREEN, Color::Green },
    { RED, Color::Red },
    { YELLOW, Color::Yellow },
    { WHITE, Color::White },
    { CYAN, Color::Cyan },
    { MAGENTA, Color::Magenta },

    { BRIGHT_BLUE, Color::BrightBlue },
    { BRIGHT_GREEN, Color::BrightGreen },
    { BRIGHT_RED, Color::BrightRed },
    { BRIGHT_YELLOW, Color::BrightYellow },
    { BRIGHT_WHITE, Color::BrightWhite },
    { BRIGHT_CYAN, Color::BrightCyan },
    { BRIGHT_MAGENTA, Color::BrightMagenta },

    { DEFAULT, Color::Default }
  };
  //
  for (size_t charPos = 0; charPos < message.size(); ++charPos) {
    //first look to see if you're looking at a color delimeter for the logs
    if (message[charPos] == ILogger::COLOR_DELIMETER) {
      //flip reading text since now you're reading a color
      readingText = !readingText;
      //append the delimeter to color
      color += message[charPos];
      if (readingText) {
          //find the color in the map
          auto it = colorMapping.find(color);
          //if the color is the iterator for the end of the map set it to default otherwise set it to the value found by the key
          //it->second gets the value that the key it maps to.
          Common::Console::setTextColor(it == colorMapping.end() ? Color::Default : it->second);
          changedColor = true;
          color.clear();
      }
    }
    //if you didnt find a color delmeter just cout this character of the message
    else if (readingText) {
      std::cout << message[charPos];
    }
    //if you didn't find a color delimeter and aren't reading texts you found a color so add it to the color object.
    else {
      color += message[charPos];
    }
  }

  if (changedColor) {
    Common::Console::setTextColor(Color::Default);
  }
}

}
