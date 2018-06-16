#ifndef MultiFunctionButton_h
#define MultiFunctionButton_h

#include <Arduino.h>


#define PULL_UP 1
#define PULL_DOWN 0


class MultiFunctionButton
{
	private:
		int _pin;
		bool _pullMode;

		// Properties
		int debounce; // Debounce period to prevent flickering when pressing or releasing the button (in ms)
		int dblPressDelay; // Max period between Presses for a double Press event (in ms)/ Hold period for a long press event (in ms)
		int longHoldDelay; // Hold period for a very long press event (in ms)

		// Variables
		bool _state; // Value read from button
		bool _lastState;// Last value of button state
		bool _dblPressWaiting; // whether we're waiting for a double Press (down)
		bool _dblPressOnNextUp; // whether to register a double Press on next release, or whether to wait and Press
		bool _singlePressOK; // whether it's OK to do a single Press
		long _downTime; // time the button was pressed down
		long _upTime; // time the button was released
		bool _ignoreUP; // whether to ignore the button release because the Press+hold was triggered
		bool _waitForUP; // when held, whether to wait for the up event
		bool _holdHappened; // whether or not the long hold event happened already

	public:
		void (*onPress)(int pin);
		void (*onDblPress)(int pin);
		void (*onHold)(int pin);
		void configure(int pin, int pullMode, void (*press)(int), void (*doub)(int), void (*hold)(int));
		void check();

		MultiFunctionButton();


};
#endif
