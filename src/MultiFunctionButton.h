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

		// Variables
		bool _state; // Value read from button
		bool _lastState;// Last value of button state
		bool _dblPressWaiting; // Whether we're waiting for a double Press (down)
		bool _dblPressOnNextUp; // Whether to register a double Press on next release, or whether to wait and Press
		bool _singlePressOK; // whether it's OK to do a single Press
		long _downTime; // Time the button was pressed down
		long _upTime; // Time the button was released
		bool _ignoreUP; // Whether to ignore the button release because the Press+hold was triggered
		bool _waitForUP; // When held, whether to wait for the up event
		bool _holdHappened; // Whether or not the long hold event happened already

	public:
		// Properties
		int debounce; // Debounce period to prevent flickering when pressing or releasing the button (in ms)
		int dblPressDelay; // Max period between Presses for a double Press event (in ms)
		int longHoldDelay; // Hold period for a very long press event (in ms)

		// Function pointers
		void (*onPress)(int pin);
		void (*onDblPress)(int pin);
		void (*onHold)(int pin);

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
		void configure(int pin, int pullMode, void (*press)(int), void (*doub)(int), void (*hold)(int));

		/**
		* Check button state. To be used within your loop() function
		*
		* @return void
		*/
		void check();

		/**
		* Constructor - sets defaults ready for use
		*/
		MultiFunctionButton();
};
#endif
