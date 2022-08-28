#include "GUI.h"

LiquidCrystal* GUI::lcd;
Vector<String> GUI::menu_items;
Vector<void (*)()> GUI::menu_callbacks;
String GUI::str_storage[10];
callbackFunction GUI::f_storage[11];
int GUI::select, GUI::back, GUI::right, GUI::left, GUI::selected;

void GUI::begin(LiquidCrystal* lcd) {
	GUI::lcd = lcd;

	selected = 1;
	menu_items.setStorage(str_storage);
	menu_callbacks.setStorage(f_storage);
}

void GUI::_select_isr() {
	static unsigned long last_interrupt = 0;
	unsigned long current = millis();
	if (current - last_interrupt > 100) {
		Serial.println("SELECTED");
		menu_callbacks[selected]();
		selected = 1;
	}
	last_interrupt = current;
}

void GUI::_back_isr() {
	static unsigned long last_interrupt = 0;
	unsigned long current = millis();
	if (current - last_interrupt > 100) {
		Serial.println("BACK");
		menu_callbacks[0]();
		selected = 1;
	}
	last_interrupt = current;
}

void GUI::_enc_isr() {
	static int previousValue = 0;
	int value = digitalRead(right) | (1 << digitalRead(left));

	static unsigned long last_interrupt = 0;
	unsigned long current = millis();

	if (value == 3) { //My encoder goes through all 4 stages in one "click", so we only check one of the states
		if (previousValue == 1) {
			if (current - last_interrupt > 50) {
				_changeSelection(1);

				last_interrupt = current;
			}
		} else if (previousValue == 2) {
			if (current - last_interrupt > 50) {
				_changeSelection(-1);
				
				last_interrupt = current;
			}
		}
	}

	previousValue = value;
}

void GUI::attachInterrupts(int select, int back, int right, int left) {
	GUI::select = select;
	GUI::back = back;
	GUI::right = right;
	GUI::left = left;

	attachInterrupt(select, GUI::_select_isr, RISING);
	attachInterrupt(back, GUI::_back_isr, RISING);
	attachInterrupt(right, GUI::_enc_isr, CHANGE);
	attachInterrupt(left, GUI::_enc_isr, CHANGE);
}

void GUI::createMenu(Vector<String> items, Vector<callbackFunction> callbacks) {
	assert(items.size() + 1 == callbacks.size());
	
	menu_callbacks.clear();
	menu_items.clear();

	for (int i = 0; i < callbacks.size(); i++)
		menu_callbacks.push_back(callbacks[i]);
	
	for (int i = 0; i < items.size(); i++)
		menu_items.push_back(items[i]);

	_draw();
}

void GUI::_changeSelection(int direction) {

	lcd->setCursor(0, selected-1);
	lcd->write(menu_items[selected-1].c_str());
	lcd->write(" ");

	selected += direction;

	if (selected < 1)
		selected = 1;
	if (selected > menu_items.size())
		selected = menu_items.size();
	
	
	lcd->setCursor(0, selected-1);
	lcd->write(">");
	lcd->write(menu_items[selected-1].c_str());
}

void GUI::_draw() {
	lcd->clear();

	for (int i = 0; i < 4; i++) {
		lcd->setCursor(0,i);
		if (i == 0)
			lcd->write(">");
		if (i < menu_items.size())
			lcd->write(menu_items[i].c_str());
	}
}
