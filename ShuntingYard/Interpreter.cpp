#include "Interpreter.h"

#include <cassert>

#include "Types.h"
#include "Stream.h"


//******
//Interpreter
//Uses Shunting-yard algorithm
//******
Interpreter::Interpreter()
{
	Stream stream("code/code.txt");

	if (Lexical(stream)) {
		printf("Lexical was successfully conducted. \n");

	}
	else {
		printf("Lexical failed.\n");
	}
}

//******
//~Interpreter
//Uses Shunting-yard algorithm
//******
Interpreter::~Interpreter()
{
}


//******
//Lexical
//Uses Shunting-yard algorithm
//******
bool Interpreter::Lexical(Stream &stream) {
	String stackOut;
	String stackOp;

	SYMBOLS currentSymbol = SYMBOL_NONE;
	bool isNumber = false;
	bool isName   = false;

	int8 byte;
	while (stream.GetNextByte(byte))
	{
		if (currentSymbol != SYMBOL_NONE)
		{
			isNumber = false;
			isName   = false;
		}

		if (byte == ';')
		{
			currentSymbol = SYMBOL_SEMICOLON;

			stackOut += stackOp;

			//Before save look if there is any pharanthesis.
			for (int i = 0; i != stackOut.Length(); ++i)
			{
				if (stackOut[i] == '(' || stackOut[i] == '[' || stackOut[i] == '{')
				{
					printf("Missing close pharanthesis.\n");
					return false;
				}
			}

			expressions.push_back(stackOut);
			stackOp  = "";
			stackOut = "";
		}
		else if (byte == ' ')
		{

		}
		else if (byte == '\n')
		{
			
		}
		else if (byte == '\t')
		{

		}
		else if (byte == '\v')
		{

		}
		else if (byte == '\r')
		{

		}
		else if (byte == ',')
		{
			currentSymbol = SYMBOL_COMMA;
		}
		else if (byte == '.')
		{
			currentSymbol = SYMBOL_PUNCTUATION;

			stackOut += byte;
		}
		else if (byte == '(')
		{
			currentSymbol = SYMBOL_OPEN_PARANTHESIS;

			stackOp.PushFront(byte);
		}
		else if (byte == ')')
		{
			currentSymbol = SYMBOL_CLOSE_PARANTHESIS;

			bool found = false;
			while (!stackOp.Empty())
			{
				if (stackOp.GetFirstChar() != '(')
				{
					stackOut += stackOp.GetFirstChar();
					stackOp.PopFront();
				}
				else
				{
					stackOp.PopFront();
					found = true;
					break;
				}
			}

			if (!found)
			{
				printf("Missing open paranthesis '(' \n");
				return false;
			}
		}
		else if (byte == ']')
		{
			currentSymbol = SYMBOL_CLOSE_SQUARE_BRACKET;

			bool found = false;
			while (!stackOp.Empty())
			{
				if (stackOp.GetFirstChar() != '[')
				{
					stackOut += stackOp.GetFirstChar();
					stackOp.PopFront();
				}
				else
				{
					stackOp.PopFront();
					found = true;
					break;
				}
			}

			if (!found)
			{
				printf("Missing open square bracket '[' \n");
				return false;
			}
		}
		else if (byte == '[')
		{
			currentSymbol = SYMBOL_OPEN_SQUARE_BRACKET;

			stackOp.PushFront(byte);
		}
		else if (byte == '{')
		{
			currentSymbol = SYMBOL_OPEN_BRACKET;

			stackOp.PushFront(byte);
		}
		else if (byte == '}')
		{
			currentSymbol = SYMBOL_CLOSE_BRACKET;

			bool found = false;
			while (!stackOp.Empty())
			{
				if (stackOp.GetFirstChar() != '{')
				{
					stackOut += stackOp.GetFirstChar();
					stackOp.PopFront();
				}
				else
				{
					stackOp.PopFront();
					found = true;
					break;
				}
			}

			if (!found)
			{
				printf("Missing open bracket '(' \n");
				return false;
			}
		}
		else if (byte == '+')
		{
			currentSymbol = SYMBOL_PLUS;

			stackOp.PushFront(byte);
		}
		else if (byte == '-')
		{
			currentSymbol = SYMBOL_MINUS;

			stackOp.PushFront(byte);
		}
		else if (byte == '/')
		{
			currentSymbol = SYMBOL_FRONT_SLASH;

			if (stackOp.GetFirstChar() == '*')
			{
				stackOut += stackOp.GetFirstChar();
				stackOp.PopFront();
			}
			else if (isalpha(stackOp.GetFirstChar()))
			{
				stackOut += " ";
				while(!stackOp.Empty() && isalpha(stackOp.GetFirstChar()))
				{
					stackOut += stackOp.GetFirstChar();
					stackOp.PopFront();
				}
			}

			stackOp.PushFront(byte);

		}
		else if (byte == '*')
		{
			currentSymbol = SYMBOL_ASTERIX;

			if (stackOp.GetFirstChar() == '/')
			{
				stackOut += stackOp.GetFirstChar();
				stackOp.PopFront();
			}

			stackOp.PushFront(byte);
		}
		else if (byte == '^')
		{
			stackOp.PushFront(byte);
		}
		else
		{
			//Is number
			if (isdigit(byte) && !isName)
			{
				isNumber = true;

				//Add space to separate. If it is a float number dont add a separator.
				if (currentSymbol != SYMBOL_NONE && currentSymbol != SYMBOL_PUNCTUATION)
				{
					currentSymbol = SYMBOL_NONE;
					stackOut += " ";
				}

				stackOut.PushBack(byte);
			}
			//Is name.
			else
			{
				isName = true;

				//Add space to separate.
				if (currentSymbol != SYMBOL_NONE)
				{
					currentSymbol = SYMBOL_NONE;
					stackOp.PushFront(" ");
				}
				
				if (!stackOp.Empty() && isalpha(byte))
				{
					bool isHit = false;
					for (int i = 0; i != stackOp.Length(); ++i)
					{
						if (stackOp[i] == ' ')
						{
							stackOp.PushAt(i, byte);
							isHit = true;
							break;
						}
					}

					if (!isHit)
					{
						stackOp.PushBack(byte);
					}

				}
				else
				{
					stackOp.PushFront(byte);
				}

			}

		}
	}

	return true;
}
