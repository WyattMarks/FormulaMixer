#include "Stepper.h"
#include "Arduino.h"

Stepper::Stepper(uint8_t positive, uint8_t negative) {
	_step = 0;
	_p = positive;
	_n = negative;
	_stepDelay = 2500;
}

void Stepper::_setPhase1(uint8_t value) {
	digitalWrite(S0_P1, value & 1);
	digitalWrite(S1_P1, value & 2);
	digitalWrite(S2_P1, value & 4);
}

void Stepper::_setPhase2(uint8_t value) {
	digitalWrite(S0_P2, value & 1);
	digitalWrite(S1_P2, value & 2);
	digitalWrite(S2_P2, value & 4);
}

void Stepper::step(int steps) {
	digitalWrite(STEPPER_ENABLE, 1);

	for (int i = 0; i < abs(steps); i++) {
		switch (_step % 4) {
			case 0:
				_setPhase1(_p);
				_setPhase2(_p);
				break;
			case 1:
				_setPhase1(_n);
				_setPhase2(_p);
				break;
			case 2:
				_setPhase1(_n);
				_setPhase2(_n);
				break;
			case 3:
				_setPhase1(_p);
				_setPhase2(_n);
				break;
			default:
				break;
		}

		usleep(_stepDelay);

		if (steps > 0)
			_step++;
		else
			_step--;
	}

	digitalWrite(STEPPER_ENABLE, 0);
}