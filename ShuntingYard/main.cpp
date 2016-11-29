#include <iostream>
#include <cassert>
#include <cstring>

#include "Interpreter.h"
#include "String.h"
#include "TestCode_StringClass.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	TestStringClass(); //Testcode string class.



	Interpreter Interpreter;	
	
	system("pause");
}