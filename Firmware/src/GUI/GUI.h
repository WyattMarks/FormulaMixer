#ifndef GUI_h
#define GUI_h
#include <Vector.h>
#include <LiquidCrystal.h>
#include <ESP32Encoder.h>


class GUI {
	public:
		GUI(LiquidCrystal* lcd, int right, int left, int select, int back);

		void create_menu(Vector<String> items, Vector<void (*)()> callbacks);

		void process();
	private:
		void _draw();

		LiquidCrystal* lcd;

		ESP32Encoder encoder;

		Vector<String> menu_items;
		Vector<void (*)()> menu_callbacks;

		int select, back;
};





#endif