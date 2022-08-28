typedef void (*callbackFunction)(void);
typedef int (*callbackFunctionArgument) (const int arg1, const int arg2);
#include <Arduino.h>
#include <Vector.h>

class testcallback {
public:
	testcallback() {
		voids.setStorage(storage);
	}

    //{ 
    void voidCallback(callbackFunction newFunction) {
      Serial.println("VOIDCALLBACK::INIT!");
      _voidCallback = newFunction;
	  voids.push_back(newFunction);
    }
    void RunvoidCallBack() {
      _voidCallback();
    }

	void runsvoids() {
		for (int i = 0; i < voids.size(); i++) {
			voids[i]();
		}
	}
    //}

    //{
    int FunctionArgument1(callbackFunctionArgument newFunction) {
    Serial.println("FUNCTIONARGUMENT1::INIT!");
    _FunctionArgument1 = newFunction;
    }
    void RunCallbackArg1(int value1, int value2) {
    Serial.println("Return value from local function 1:" + String(_FunctionArgument1(value1,value2)));
    }
    //}
    //{
    int FunctionArgument2(callbackFunctionArgument newFunction) {
      Serial.println("FUNCTIONARGUMENT2::INIT!");
      _FunctionArgument2 = newFunction;
    }
    void RunCallbackArg2(int value1, int value2) {
      Serial.println("Return value from local function 2:" + String(_FunctionArgument2(value1,value2)));
    }
    //}


private:
    callbackFunction _voidCallback;

    callbackFunctionArgument _FunctionArgument1;
    callbackFunctionArgument _FunctionArgument2;

	callbackFunction storage[10];
	Vector<callbackFunction> voids;

};