# MultiFunctionButton
Arduino Multi-function button library: press, double press, and press-hold events

### Public variables ###

**int debounce** Optionally set de-bounce in milliseconds per button instance. Default of 20

**int dblPressDelay** Optionally set max time period for double press in milliseconds per button instance. Default of 250

**int longHoldDelay** Optionally set time period for press-hold event in milliseconds per button instance. Default of 750

## Configure function ##
Configuration function to be used within your setup() function

### Function args ###

**@param int pin** Physical Arduino I/0 pin to use

**@param int pullMode** PULL_UP | PULL_DOWN Defaults to PULL_DOWN

**@param int onPress function-pointer** Optional call-back function called on single press event

**@param int onDblPress function-pointer** Optional call-back function called on double press event

**@param int onHold function-pointer** Optional call-back funcition called during button held down event, every 750ms by default


## Check function ##
Used within your loop() function to check the state for each button, which then calls the appropriate call-back function


## Example: ##
```c++
#include <MultiFunctionButton.h>

// Create instances of buttons
MultiFunctionButton btn1;
MultiFunctionButton btn2;
MultiFunctionButton btn3;
MultiFunctionButton btn4;



void setup()
{
  // Configure each button. Call-backs are optional per button!
  btn1.configure(2, PULL_UP, onPress, onDblPress, onHold);
  btn2.configure(3, PULL_UP, NULL, onDblPress, onHold);
  btn3.configure(4, PULL_UP, onPress, NULL, onHold);
  btn4.configure(5, PULL_UP, onPress, onDblPress, NULL);
  
  // You may have different wire lengths to each button which may require different de-bounce rates per button
  // Change debounce value for btn1 only
  btn1.debounce = 40;
  
  // Change hold period for btn3 only
  btn3.longHoldDelay = 650;

  Serial.begin(9600);
}



void loop()
{
  // Check state of each button
  btn1.check();
  btn2.check();
  btn3.check();
  btn4.check();
}



/**
* Press event call-back function
*
* @param int pin Reports which I/O pin the event occurred on
* @return void
*/
void onPress(int pin)
{
  Serial.print(pin);
  Serial.println(" pressed");
}



/**
* Double press event call-back function
*
* @param int pin Reports which I/O pin the event occurred on
* @return void
*/
void onDblPress(int pin)
{
  Serial.print(pin);
  Serial.println(" double pressed");
}



/**
* Press-hold event call-back function
*
* @param int pin Reports which I/O pin the event occurred on
* @return void
*/
void onHold(int pin)
{
  Serial.print(pin);
  Serial.println(" holding");
}
```
