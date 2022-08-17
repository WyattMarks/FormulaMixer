#include <Arduino.h>
#include <LiquidCrystal.h>
#include "GUI/GUI.h"

#define ENC_A 34
#define ENC_B 35
#define SELECT 32
#define BACK 33

GUI gui;
LiquidCrystal lcd;

void menu_a() {
	Vector<String> options;
	options.push_back("Menu B");

	Vector<void (*)()> callbacks;
	callbacks.push_back(main_menu);
	callbacks.push_back(menu_b);

	gui.create_menu(options, callbacks);
}

void menu_b() {
	Vector<String> options;
	options.push_back("Menu A");

	Vector<void (*)()> callbacks;
	callbacks.push_back(main_menu);
	callbacks.push_back(menu_a);

	gui.create_menu(options, callbacks);
}

void main_menu() {
	Vector<String> options;
	options.push_back("Menu A");
	options.push_back("Menu B");

	Vector<void (*)()> callbacks;
	callbacks.push_back(main_menu);
	callbacks.push_back(menu_a);
	callbacks.push_back(menu_b);

	gui.create_menu(options, callbacks);
}

void setup() {
	pinMode(ENC_A, INPUT);
	pinMode(ENC_B, INPUT);
	pinMode(SELECT, INPUT);
	pinMode(BACK, INPUT);

	lcd = LiquidCrystal(19, 23, 18, 17, 16, 13); //LCD Pins
	gui = GUI(&lcd, ENC_A, ENC_B, SELECT, BACK); //Encoder + Button Pins

	main_menu();
}

void loop() {
	gui.process();
}