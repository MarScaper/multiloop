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
  
  // Exectute loop0 as fast as possible
  multiLoop.addLoop(loop0);
  
  // Exectute loop1 every 500ms
  multiLoop.addLoop(loop1,500);
  
  // Exectute loop2 every 500ms but launch It after 250ms
  multiLoop.addLoop(loop2,500,250);
}

void loop()
{
  multiLoop.dispatch();
}

void loop0()
{
  Serial.print(millis());
  Serial.println("\tloop0");
  
  // Non blocking delay
  multiLoop.delay(2000);
}

void loop1()
{
  Serial.print(millis());
  Serial.println("\t\tloop1");
}

void loop2()
{
  Serial.print(millis());
  Serial.println("\t\t\tloop2");
}
```

Console feedback:
```
0       loop0
500             loop1
750                     loop2
1000            loop1
1250                    loop2
1500            loop1
1750                    loop2
2000    loop0
2000            loop1
2250                    loop2
2500            loop1
2750                    loop2
3000            loop1
3250                    loop2
3500            loop1
3750                    loop2
4000            loop1
4000    loop0
4250                    loop2
4500            loop1
...
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
