#ifndef GUI_h
#define GUI_h
#include <Vector.h>
#include <LiquidCrystal.h>
#define MENU 0
#define FLOAT_INPUT 1
#define INPUT_COMPLETE 2

typedef void (*callbackFunction)(void);


class GUI {
	public:
		static void createMenu(Vector<String> items, Vector<callbackFunction> callbacks);

		static void begin(LiquidCrystal* lcd);
		static void attachInterrupts(int select, int back, int right, int left);

		static void disableInput();

		static double getInput(String item, double increment); 
	private:
		static void _draw();

		static LiquidCrystal* lcd;

		static Vector<String> menu_items;
		static Vector<void (*)()> menu_callbacks;
		static String str_storage[10];
		static callbackFunction f_storage[11];

		static void _select_isr();
		static void _back_isr();
		static void _enc_isr();

		static void _changeSelection(int direction);

		static int select, back, right, left, selected;

		static bool _acceptInput;
		static int _mode;
		static double _selection, _inc;
};





#endif