# multiloop // BETA RELEASE //
Create multiple loops easily for pseudo-parallelism with Arduino.

## Code Example

```
#include "MultiLoop.hpp"

MultiLoop multiLoop = MultiLoop();

void setup()
{
  Serial.begin(9600);
  
  multiLoop.addLoop(blink,500);
}

void loop()
{
  multiLoop.dispatch();
}

void blink()
{
  Serial.print(millis());
  Serial.println("blink");
}
```

## Features
- Easy to use in C code.
- Up to 16 loops.
- Loops can run as fast as possibe or with a specific period.
- Loops can be started after a specific delay.
- Non blocking delay method when you need to wait in a loop.

Video tutorial (French)...

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
