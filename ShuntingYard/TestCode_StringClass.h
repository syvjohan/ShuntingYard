#include "String.h"

#include <iostream>
#include <cassert>

void TestStringClass()
{
	//Constructors
	String string1;
	assert(string1.cStr() == NULL);

	String string2('c');
	assert(string2 == "c");

	String string3("hello ");
	assert(string3 == "hello ");

	String string4(string3);
	assert(string4 == string3);
	assert(string4.Length() == 6);
	assert(string4.Capacity() == 12);


	//Destructor
	delete new String("goodbye :(");


	//Push Back
	String string5;
	string5.PushBack("hello");
	assert(string5 == "hello");

	string5.PushBack(' ');
	assert(string5 == "hello ");

	String string6("world");
	string5.PushBack(string6);
	assert(string5 == "hello world");


	//Push Front
	string5.PushFront("said - ");
	assert(string5 == "said - hello world");

	string5.PushFront(' ');
	assert(string5 == " said - hello world");

	String string7("Kalle");
	string5.PushFront(string7);
	assert(string5 == "Kalle said - hello world");


	//PushAt
	String string51("lo");
	string51.PushAt(0, "hel");
	assert(string51 == "hello");

	string51.PushAt(string51.Length(), " World!");
	assert(string51 == "hello World!");

	string51.PushAt(string51.Length() / 2, "This is a break... ");
	assert(string51 == "hello This is a break... World!");

	String string50("Kalle said - hello world");
	string50.PushAt(4, "j");
	assert(string50 == "Kallje said - hello world");

	string50.PushAt(0, "j");
	assert(string50 == "jKallje said - hello world");

	string50.PushAt(string50.Length(), "j");
	assert(string50 == "jKallje said - hello worldj");


	//Pop Back and Pop Front
	const int capacity = string5.Capacity();
	string5.PopBack();
	assert(string5 == "Kalle said - hello worl");
	assert(string5.Capacity() == capacity);

	string5.PopFront();
	assert(string5 == "alle said - hello worl");

	string5.PopFront(5);
	assert(string5 == "said - hello worl");

	string5.PopBack(4);
	assert(string5 == "said - hello ");

	string5.PopBack(string5.Length());
	assert(string5 == "");

	string5.PopBack();
	assert(string5.Length() == 0);

	string5.PopFront();
	assert(string5.Length() == 0);
	assert(string5.Capacity() == capacity);


	//Operator =
	string5 = "testing!";
	assert(string5 == "testing!");

	String string8("wassup?");
	string8 = string5;
	assert(string5 == "testing!");

	string5 = "test!";
	assert(string5 == "test!");

	string8 = 'c';
	assert(string8 == "c");

	//Operator +
	String string9("hello ");
	String string10("world");
	String string11 = string9 + string10;
	assert(string11 == "hello world");

	string11 = string9 + "world!";
	assert(string11 == "hello world!");

	string11 = ""; //Reset
	assert(string11 == "");

	string11 = string9 + 'w';
	assert(string11 == "hello w");

	//Operator +=
	string9 = "my name is ";
	string10 = "Nemo";
	string9 += string10;
	assert(string9 == "my name is Nemo");

	string9 = "my name is ";
	string9 += "Nemo";
	assert(string9 == "my name is Nemo");

	string9 = "my name is ";
	string9 += 'N';
	assert(string9 == "my name is N");

	string9 = "my name is ";
	string9 += 'N';
	string9 += 'e';
	string9 += "mo";
	assert(string9 == "my name is Nemo");


	//Operator ==
	string9 = "hello world";
	string10 = "hello world";
	assert(string9 == string10);

	string9 = "hello world";
	assert(string9 == "hello world");

	string9 = "w";
	assert(string9 != string10);


	//Operator !=
	string9 = "hello world";
	string10 = "hello worl";
	assert(string9 != string10);

	string9 = "hello world";
	assert(string9 != "hello worl");


	//Operator []
	String string13("mello");
	string13[0] = 'h';
	assert(string13 == "hello");

	string13[3] = 'p';
	string13[4] = '\0';
	assert(string13 == "help");

	//Get char
	string9 = "hello";
	assert(string9.GetFirstChar() == 'h');
	assert(string9.GetLastChar() == 'o');
	assert(string9.GetCharAt(2, true) == 'l');
	assert(string9.GetCharAt(string9.Length() - 1, true) == 'o');
	assert(string9.GetCharAt(2, false) == 'l');

	assert(string9[0] == 'h');
	assert(string9[string9.Length() + 1] != '\0'); //Outside text in string.

	string10 = "";
	for (int i = 0; i != string9.Length(); ++i)
	{
		string10.PushBack(string9[i]);
	}
	assert(string10 == string9);


	//Find and FindReverse
	String string12("hello world");
	assert(string12.Find('l') == 2);
	assert(string12.FindReverse('l') == 9);


	//Empty
	assert(string12.Empty() == false);
	string12 = "";
	assert(string12.Empty() == true);

	printf("\n\n------------------------ Success! --------------------\n\n");
}