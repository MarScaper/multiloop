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
#include <Servo.h>
Servo servo; 

#include "MultiLoop.hpp"

// Loop declarations
static void loop1();
static void loop2();

// MultiLoop instance
MultiLoop multiLoop = MultiLoop();




// Arduino setup function:
// Now in setup, we need to add the loops we want
// to the MultiLoop instance.
void setup()
{
  // Initialize serial for debug
  Serial.begin(9600);
  
  // Enable led for tests
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Run loop1 every 500ms
  multiLoop.addLoop(loop1,500);

  // Run loop2 as kickly as possible
  multiLoop.addLoop(loop2);

  servo.attach(9); 
}

// Arduino loop function:
// The magic hat. Dispatch method automatically calls
// all loops periodically according to their delays.
void loop()
{
  // Nothing to do except dispatch
  multiLoop.dispatch();
}



void loop1()
{
  int pos = 0;
  
  for (pos = 0; pos <= 90; pos += 1) 
  {
    servo.write(map(pos,0,90,68,168));

    multiLoop.delay(10);   
  }

  multiLoop.delay(200);

  for (pos = 90; pos >= 0; pos -= 1) 
  { 
    servo.write(map(pos,0,90,68,168));

    multiLoop.delay(10);                      
  }
}

void loop2()
{
  Serial.print(millis());
  Serial.println("[LOOP 2]:  We do a non blocking blink with Led in loop 2.");
  
  // Another magic hat: Here we use a non-blocking delay. When this loop is
  // waiting, other loops can run.
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  multiLoop.delay(1000);             // wait for a second (non blocking)

  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  multiLoop.delay(1000);             // wait for a second (non blocking)
}
