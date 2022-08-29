#include <Arduino.h>
#include <LiquidCrystal.h>
#include "GUI/GUI.h"
#include "Stepper/Stepper.h"
typedef void (*callbackFunction)(void);

#define ENC_A 34
#define ENC_B 35
#define SELECT 32
#define BACK 33


LiquidCrystal lcd(19, 23, 18, 17, 16, 13); //LCD Pins [ RS, EN, D4, D5, D6, D7 ]

Stepper motor1(0, 1);

void (*storage[10])();
String array[10];

callbackFunction main_menu_ptr;
callbackFunction menu_a_ptr;
callbackFunction menu_b_ptr;
callbackFunction stepper_ptr;

uint8_t stepper_flag = 0;

void menu_a() {
	Vector<String> options;
	options.setStorage(array);
	options.push_back("Menu B");

	Vector<callbackFunction> callbacks;
	callbacks.setStorage(storage);
	callbacks.push_back(main_menu_ptr);
	callbacks.push_back(menu_b_ptr);

	GUI::createMenu(options, callbacks);
}

void menu_b() {
	Vector<String> options;
	options.setStorage(array);
	options.push_back("Menu A");

	Vector<callbackFunction> callbacks;
	callbacks.setStorage(storage);
	callbacks.push_back(main_menu_ptr);
	callbacks.push_back(menu_a_ptr);

	GUI::createMenu(options, callbacks);
}

void main_menu() {
	Vector<String> options;
	options.setStorage(array);
	options.push_back("Menu A");
	options.push_back("Menu B");
	options.push_back("Stepper Test");

	
	Vector<callbackFunction> callbacks;
	callbacks.setStorage(storage);

	callbacks.push_back(main_menu_ptr);
	callbacks.push_back(menu_a_ptr);
	callbacks.push_back(menu_b_ptr);
	callbacks.push_back(stepper_ptr);

	GUI::createMenu(options, callbacks);
}

void stepper() {
	lcd.clear();
	lcd.write("Trying to dispense..");
	stepper_flag = 1;
}


void setup() {
	pinMode(ENC_A, INPUT);
	pinMode(ENC_B, INPUT);
	pinMode(SELECT, INPUT);
	pinMode(BACK, INPUT);

	pinMode(S0_P1, OUTPUT);
	pinMode(S1_P1, OUTPUT);
	pinMode(S2_P1, OUTPUT);
	pinMode(S0_P2, OUTPUT);
	pinMode(S1_P2, OUTPUT);
	pinMode(S2_P2, OUTPUT);
	pinMode(STEPPER_ENABLE, OUTPUT);

	digitalWrite(STEPPER_ENABLE, 0);

	Serial.begin(115200);
	lcd.begin(20, 4);
	lcd.clear();

	main_menu_ptr = main_menu;
	menu_a_ptr = menu_a;
	menu_b_ptr = menu_b;
	stepper_ptr = stepper;

	GUI::begin(&lcd);
	GUI::attachInterrupts(SELECT, BACK, ENC_A, ENC_B);

	main_menu();
}



void loop() {
	if (stepper_flag) {
		stepper_flag = 0;

		motor1.step(1000);

		delay(1000);

		motor1.step(-1000);

		main_menu_ptr();
	}
}

//ppnnppnnppnnppnn
//nppnnppnnppnnppnn
//nnppnnppnnppnnppnn
//pnnppnnppnnppnnppnn
//ppnnppnnppnnppnnppnn