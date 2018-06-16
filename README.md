# MultiFunctionButton
Arduino Multi-function button library: press, double press, and hold

## Configure function ##
Setup each button:

**pin** Physical Arduino pin to use

**pull-mode** 0 = pull-down for press. 1 = pull-up for press

**press function** Called on single press action

**double-press** Called on double press action

**hold function** Called while button held down, every 750ms by default



## Check function ##
Used within your loop function to check the state for each button, which then calls the appropriate call-back function


## Example: ##
```c++
#include <MultiFunctionButton.h>

MultiFunctionButton btn1;
MultiFunctionButton btn2;
MultiFunctionButton btn3;
MultiFunctionButton btn4;



void setup()
{
  // pin, pull-mode, press function, double-press function, hold function
  btn1.configure(0, 1, onPress, onDblPress, onHold);
  btn2.configure(1, 1, onPress, onDblPress, onHold);
  btn3.configure(2, 1, onPress, onDblPress, onHold);
  btn4.configure(3, 1, onPress, onDblPress, onHold);

  Serial.begin(115200);
}



void loop()
{
  btn1.check();
  btn2.check();
  btn3.check();
  btn4.check();
}



void onPress(int pin)
{
  Serial.print(pin);
  Serial.println(" pressed");
}



void onDblPress(int pin)
{
  Serial.print(pin);
  Serial.println(" double pressed");
}



void onHold(int pin)
{
  Serial.print(pin);
  Serial.println(" holding");
}
```
