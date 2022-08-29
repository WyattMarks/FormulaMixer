#ifndef STEPPER_h
#define STEPPER_h

#include "Arduino.h"

#define STEPPER_ENABLE 4
#define S0_P1 25
#define S1_P1 26
#define S2_P1 27
#define S0_P2 21
#define S1_P2 22
#define S2_P2 14

/* * * * * * * * * * *         M1             
 *  Step C0 C1 C2 C3 * S2 S1 S0  S2 S1 S0     
 *    1  1  0  1  0  *  0  0  0   0  0  0 
 *    2  0  1  1  0  *  0  0  1   0  0  0
 *    3  0  1  0  1  *  0  0  1   0  0  1
 *    4  1  0  0  1  *  0  0  0   0  0  1
 * * * * * * * * * * */

class Stepper {
	public:
		Stepper(uint8_t positive, uint8_t negative);
		void step(int steps);
	private:
		void _setPhase1(uint8_t value);
		void _setPhase2(uint8_t value);
		uint8_t _p, _n;
		int _step, _stepDelay;
};


#endif