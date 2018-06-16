# MultiFunctionButton
Arduino Multi-function button library: press, double press, and hold 

```c++
#include <MultiFunctionButton.h>

MultiFunctionButton btn1;
MultiFunctionButton btn2;
MultiFunctionButton btn3;
MultiFunctionButton btn4;



void setup()
{
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
