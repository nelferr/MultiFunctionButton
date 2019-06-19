#include "MultiFunctionButton.h"
#include "Arduino.h"


/**
* Constructor function - sets defaults ready for use
*/
MultiFunctionButton::MultiFunctionButton()
{
	this->debounce = 20;
	this->dblPressDelay = 250;
	this->longHoldDelay = 750;

	this->_state = true;
	this->_lastState = true;
	this->_dblPressWaiting = false;
	this->_dblPressOnNextUp = false;
	this->_singlePressOK = false;
	this->_downTime = -1;
	this->_upTime = -1;
	this->_ignoreUP = false;
	this->_waitForUP = false;
	this->_holdHappened = false;
}



/**
* Configuration function to be used within your setup() function
*
* @param int pin
* @param int pullMode PULL_UP|PULL_DOWN Defaults to PULL_DOWN
* @param int Optional callback press function (Function Pointer)
* @param int Optional callback double press function (Function Pointer)
* @param int Optional callback press-hold function (Function Pointer)
* @return void
*/
void MultiFunctionButton::configure(int pin, int pullMode = PULL_DOWN, void (*press)(int) = NULL, void (*doub)(int) = NULL, void (*hold)(int) = NULL)
{
	this->_pin = pin;
	this->_pullMode = pullMode;
	pinMode(this->_pin, INPUT);

	onPress = press;
	onDblPress = doub;
	onHold = hold;
}


/**
* Check button state. To be used within your loop() function
*
* @return void
*/
void MultiFunctionButton::check(void)
{
	int resultEvent = 0;
	long millisRes = millis();
	this->_state = digitalRead(this->_pin) == HIGH;

	// Button down
	if (this->_state != this->_pullMode
			&& this->_lastState == this->_pullMode
			&& (millisRes - this->_upTime) > this->debounce)
	{
		this->_downTime = millisRes;
		this->_ignoreUP = false;
		this->_waitForUP = false;
		this->_singlePressOK = true;
		this->_holdHappened = false;

		if ((millisRes - this->_upTime) < this->dblPressDelay
				&& this->_dblPressOnNextUp == false
				&& this->_dblPressWaiting == true)
		{
			this->_dblPressOnNextUp = true;
		}
		else
		{
			this->_dblPressOnNextUp = false;
			this->_dblPressWaiting = false;
		}
	}

	// Button released
	else if (this->_state == this->_pullMode
			&& this->_lastState != this->_pullMode
			&& (millisRes - this->_downTime) > this->debounce)
	{
		if (this->_ignoreUP == false)
		{
			this->_upTime = millisRes;

			if (this->_dblPressOnNextUp == false)
			{
				this->_dblPressWaiting = true;
			}
			else
			{
				resultEvent = 2;
				this->_dblPressOnNextUp = false;
				this->_dblPressWaiting = false;
				this->_singlePressOK = false;
			}
		}
	}

	// Test for normal Press event: dblPressDelay expired
	if (this->_state == this->_pullMode
			&& (millisRes - this->_upTime) >= this->dblPressDelay
			&& this->_dblPressWaiting == true
			&& this->_dblPressOnNextUp == false
			&& this->_singlePressOK == true
			&& resultEvent != 2)
	{
		resultEvent = 1;
		this->_dblPressWaiting = false;
	}

	// Test for hold
	if (this->_state != this->_pullMode
			&& (millisRes - this->_downTime) >= this->longHoldDelay)
	{
		// Trigger hold
		if (this->_holdHappened == false)
		{
			// resultEvent = 3;
			this->_waitForUP = true;
			this->_ignoreUP = true;
			this->_dblPressOnNextUp = false;
			this->_dblPressWaiting = false;
			this->_holdHappened = true;
		}

		this->_downTime = millisRes;
		resultEvent = 3;
	}

	this->_lastState = this->_state;

	if (resultEvent == 1 && onPress) onPress(this->_pin);
	if (resultEvent == 2 && onDblPress) onDblPress(this->_pin);
	if (resultEvent == 3 && onHold) onHold(this->_pin);
}
