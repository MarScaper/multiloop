# MultiLoop - BETA RELEASE -
![Alt text](/MultiLoop.png?raw=true "Optional Title")

Create multiple loops easily for pseudo-parallelism with Arduino.

## Features
- Easy to use in C code.
- Up to 16 loops.
- Loops can run as fast as possibe or with a specific period.
- Loops can be started after a specific delay.
- Non blocking delay method when you need to wait in a loop.

## Code Example

```
#include "MultiLoop.hpp"

MultiLoop multiLoop = MultiLoop();

void setup()
{
  Serial.begin(9600);
  
  // Exectute every 500ms
  multiLoop.addLoop(loop1,500);
  
  // Exectute every 500ms and launch after 250ms
  multiLoop.addLoop(loop2,500,250);
}

void loop()
{
  multiLoop.dispatch();
}

void loop1()
{
  Serial.print(millis());
  Serial.println(" loop1");
}

void loop2()
{
  Serial.print(millis());
  Serial.println(" loop2");
}
```

## Video tutorial (French)...

[![Alt text for your video](https://img.youtube.com/vi/s0Ovzg3ystU/0.jpg)](https://www.youtube.com/watch?v=s0Ovzg3ystU)

## License

Copyright (c) 2017 by Sebastien MARCHAND 
Web:www.marscaper.com - Email:sebastien@marscaper.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
