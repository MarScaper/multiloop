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
    _loopArray[_loopIndex].fireDelay              = 0;
    _loopArray[_loopIndex].callback               = NULL;
    _loopArray[_loopIndex].startTime              = 0;
    _loopArray[_loopIndex].internalDelay          = 0;
    _loopArray[_loopIndex].internalStartTimeDelay = 0;
    _loopArray[_loopIndex].launched                = false;
  }
  
  _loopIndex = 0;
}

void MultiLoop::dispatch()
{
  unsigned long time = millis();
  
  for(_loopIndex = 0; _loopIndex<_loopCount; _loopIndex++)
  {
    if( _loopArray[_loopIndex].launched == false && _loopArray[_loopIndex].internalDelay == 0)
    {
      if( _loopArray[_loopIndex].fireDelay == 0 )
      {
        _loopArray[_loopIndex].launched = true;
        {
          _loopArray[_loopIndex].callback();
        }
        _loopArray[_loopIndex].launched = false;
      }
      else if (time >= _loopArray[_loopIndex].startTime+_loopArray[_loopIndex].fireDelay )
      {
        _loopArray[_loopIndex].launched = true;
        {
          _loopArray[_loopIndex].startTime = time;
          _loopArray[_loopIndex].callback();
        }
        _loopArray[_loopIndex].launched = false;
      }
    }
    else if( time >= _loopArray[_loopIndex].internalStartTimeDelay+_loopArray[_loopIndex].internalDelay )
    {
      _loopArray[_loopIndex].internalDelay          = 0;
      _loopArray[_loopIndex].internalStartTimeDelay = 0;
      
      return;
    }
  }
}

void MultiLoop::delay(unsigned long aDelay)
{
  uint8_t loopIndex = _loopIndex;
  {
    _loopArray[loopIndex].internalDelay          = aDelay;
    _loopArray[loopIndex].internalStartTimeDelay = millis();
    
    do
    {
      dispatch();
      
    } while( _loopArray[loopIndex].internalDelay != 0);
  }
  _loopIndex = loopIndex;
}

bool MultiLoop::addLoop(callback_void_t callback,unsigned long fireDelay,unsigned long launchDelay)
{
  bool res = false;
  
  if( _loopCount < MAX_LOOPS)
  {
    if( fireDelay )
    {
      _loopArray[_loopCount].fireDelay = fireDelay;
      _loopArray[_loopCount].startTime = millis()+launchDelay;
      
    }
    else
    {
      _loopArray[_loopCount].fireDelay = 0;
      _loopArray[_loopCount].startTime = 0;
    }
    
    _loopArray[_loopCount].callback  = callback;
    
    _loopArray[_loopCount].internalDelay  = false;
    
    _loopCount++;
    
    res = true;
  }
  
  return res;
}
