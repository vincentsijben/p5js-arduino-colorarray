# p5js arduino colorarray

reading 1201 characters from p5js and store it in array of length 100, each item containing a color (3 bytes).

This takes up 1725 bytes in total, so not much bytes left...

I had to comment out the `strcpy(tempChars, receivedChars);` part, because it would double the amount of necessary bytes.


Based on https://github.com/vincentsijben/p5js-arduino-parse-data