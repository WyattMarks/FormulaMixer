#include "GUI.h"


GUI::GUI(LiquidCrystal* lcd, int right, int left, int select, int back) {
	this->lcd = lcd;
	this->encoder.attachHalfQuad(right, left);
	this->menu_items = Vector<String>();
	this->menu_callbacks = Vector<void (*)()>();
	this->select = select;
	this->back = back;
}

void GUI::create_menu(Vector<String> items, Vector<void (*)()> callbacks) {
	assert(items.size() + 1 == callbacks.size());
	
	this->menu_callbacks.clear();
	this->menu_items.clear();
	this->encoder.setCount(1);

	this->menu_callbacks.push_back(callbacks[0]);
	
	for (int i = 0; i < items.size(); i++) {
		this->menu_items.push_back(items[i]);
		this->menu_callbacks.push_back(callbacks[i + 1]);
	}

	this->_draw();
}

void GUI::_draw() {
	this->lcd->clear();

	for (int i = 0; i < 4; i++) {
		this->lcd->setCursor(i,0);
		this->lcd->write(this->menu_items[this->encoder.getCount() + i].c_str());
	}
}

void GUI::process() {
	if (this->encoder.getCount() > this->menu_items.size())
		this->encoder.setCount(this->menu_items.size());

	if (this->encoder.getCount() < 1)
		this->encoder.setCount(1);


	if (digitalRead(this->select)) {
		usleep(10000);
		if (digitalRead(this->select)) {
			this->menu_callbacks[this->encoder.getCount()]();
			return;
		}
	}

	if (digitalRead(this->back)) {
		usleep(10000);
		if (digitalRead(this->back)) {
			this->menu_callbacks[0]();
			return;
		}
	}


}
