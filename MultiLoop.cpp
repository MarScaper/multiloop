/*
 * MultiLoop.cpp
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

#include "MultiLoop.hpp"

MultiLoop::MultiLoop()
{
  for(_loopIndex = 0; _loopIndex<_loopCount; _loopIndex++)
  {
    LoopStruct *loop = &_loopArray[_loopIndex];
    
    loop->fireDelay              = 0;
    loop->callback               = NULL;
    loop->startTime              = 0;
    loop->launched               = false;
  }
  
  _loopIndex = 0;
}

void MultiLoop::dispatch(bool reset)
{
  unsigned long time = millis();
  
  if( reset)
  {
    _loopIndex = 0;
  }
  
  for(_loopIndex = 0; _loopIndex<_loopCount; _loopIndex++)
  {
    LoopStruct *loop = &_loopArray[_loopIndex];
    
    if( reset )
    {
      loop->launched = false;;
    }

    if( loop->launched == false )
    {
      if( time >= loop->startTime+loop->fireDelay )
      {
        loop->launched = true;
        {
          loop->startTime = time;
          loop->callback();
        }
        loop->launched = false;
      }
    }
  }
}

void MultiLoop::delay(unsigned long aDelay)
{
  uint8_t loopIndex = _loopIndex;
  {
    LoopStruct *loop = &_loopArray[_loopIndex];
    
    unsigned long internalDelay =  millis()+aDelay;
    
   /* Serial.println(loopIndex);
    Serial.println(" -> ");
    Serial.println(_loopArray[loopIndex].internalDelay);*/
    
    do
    {
      dispatch();
      
    } while(millis() < internalDelay);
  }
  _loopIndex = loopIndex;
}

bool MultiLoop::addLoop(callback_void_t callback,unsigned long fireDelay,unsigned long launchDelay)
{
  bool res = false;
  
  if( _loopCount < MAX_LOOPS)
  {
    LoopStruct *loop = &_loopArray[_loopCount];
    
    if( fireDelay )
    {
      loop->fireDelay = fireDelay;
      loop->startTime = millis()+launchDelay;
    }
    else
    {
      loop->fireDelay = 0;
      loop->startTime = 0;
    }
    
    loop->callback  = callback;

    _loopCount++;
    
    res = true;
  }
  
  return res;
}
