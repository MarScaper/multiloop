/*
 * MultiLoop.hpp
 *
 * Copyright (c) 2020 by Sebastien MARCHAND (Web:www.marscaper.com, Email:sebastien@marscaper.com)
 */
/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MultiLoop_hpp
#define MultiLoop_hpp

#include <Arduino.h>

/*
 * Max number of loops allowed by MultiLoop.
 */
#define MAX_LOOPS 16

/*
 * callback definition.
 */
typedef void (*callback_void_t)(void);

/*
 * Internal structure used by MultiLoop to store data.
 */
struct LoopStruct
{
  callback_void_t callback;
  unsigned long   fireDelay;
  unsigned long   startTime;
  bool            launched;
};

/*
 * MultiLoop allows to automatically manage several loops for protothreads.
 * Note that you can’t achieve true multi-threading with Arduino, all the
 * code is executed in one thread, line by line. With protothreads you’ll
 * just have the “feeling” of multi-threading.
 */
class MultiLoop
{
  
public:
  
  // Constructor
  MultiLoop();
  
  // Dispatch must be called in loop() function.
  void dispatch();
  
  // Do not use C delay() function anymore. Use this one for non-blocking purpose.
  void delay(unsigned long aDelay);
  
  // Add loop to the MultiLoop class. It'll be automatically called by dispach().
  bool addLoop(callback_void_t callback,unsigned long fireDelay=0,unsigned long launchDelay=0);
  
  // Change dynamically the delay of a loop
  bool changeLoopDelay(callback_void_t callback, unsigned long fireDelay);
               
private:
  
  uint8_t _loopCount = 0;
  uint8_t _loopIndex = 0;
  LoopStruct _loopArray[MAX_LOOPS];
  
  void dispatch(bool single);
};

#endif
