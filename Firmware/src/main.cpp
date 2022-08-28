#include <Arduino.h>
#include <LiquidCrystal.h>
#include "GUI/GUI.h"
typedef void (*callbackFunction)(void);

#define ENC_A 34
#define ENC_B 35
#define SELECT 32
#define BACK 33

void (*storage[10])();
String array[10];

callbackFunction main_menu_ptr;
callbackFunction menu_a_ptr;
callbackFunction menu_b_ptr;

LiquidCrystal lcd(19, 23, 18, 17, 16, 13); //LCD Pins [ RS, EN, D4, D5, D6, D7 ]

void menu_a() {
	Serial.println("opening menu a");

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
	Serial.println("opening menu b");


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
	Serial.println("opening main menu");
	
	Vector<String> options;
	options.setStorage(array);
	options.push_back("Menu A");
	options.push_back("Menu B");

	
	Vector<callbackFunction> callbacks;
	callbacks.setStorage(storage);

	callbacks.push_back(main_menu_ptr);
	callbacks.push_back(menu_a_ptr);
	callbacks.push_back(menu_b_ptr);

	GUI::createMenu(options, callbacks);
}


void setup() {
	pinMode(ENC_A, INPUT);
	pinMode(ENC_B, INPUT);
	pinMode(SELECT, INPUT);
	pinMode(BACK, INPUT);

	Serial.begin(115200);
	lcd.begin(20, 4);
	lcd.clear();

	main_menu_ptr = main_menu;
	menu_a_ptr = menu_a;
	menu_b_ptr = menu_b;

	GUI::begin(&lcd);
	GUI::attachInterrupts(SELECT, BACK, ENC_A, ENC_B);

	main_menu();
}

void loop() {
	//GUI::process();
}