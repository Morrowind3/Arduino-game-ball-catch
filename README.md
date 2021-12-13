# Arduino-game-ball-catch
A little game using a button and two-row, 16-character LCD (LCD1602). Single Digit 7-segment LED display and buzzer used for score counting and feedback, made to verify that I got the hang of the basics of Arduino development. 

Pressing the button moves the arrow between Row A and row B. Pressing the button too shortly may not register as the code may by in the delay when you press it. In that case, press a bit longer. 
Balls spawn at the right side of the LCD and will move left until reaching the left side of the LCD. If it hits the arrow, one point is added on the LED display and the buzzer plays a noise. The LED display wraps around at 9, because a single digit is enough cable hell for a quick prototype. 

