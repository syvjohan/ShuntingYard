#include "String.h"

#include <cstring>

String::String()
{
	capacity = 0;
	length   = 0;
	data     = nullptr;
}

String::String(const int8 c)
{
	capacity = 0;
	length   = 0;
	data     = nullptr;

	char arr[2] = { c, '\0' };
	Concat(arr, 1, 0);
}


String::String(const int8 *cStr)
{
	capacity = 0;
	length   = 0;
	data     = nullptr;

	Concat(cStr, Strlen(cStr), 0);
}

String::String(const String &obj)
{
	capacity = 0;
	length   = 0;
	data     = nullptr;

	Concat(obj.data, obj.length, 0);
}

String::~String()
{
	if (data)
	{
		delete[] data;
		data = NULL;
	}
}

void String::PushBack(const int8 c)
{
	char arr[2] = { c, '\0' };
	Concat(arr, 1, length);
}

void String::PushBack(const int8 *cStr)
{
	Concat(cStr, Strlen(cStr), length);
}

void String::PushBack(const String &obj)
{
	Concat(obj.data, obj.length, length);
}

void String::PushFront(const int8 c)
{
	char arr[2] = { c, '\0' };
	Concat(arr, 1, 0);
}

void String::PushFront(const int8 *cStr)
{
	Concat(cStr, Strlen(cStr), 0);
}

void String::PushFront(const String &obj)
{
	Concat(obj.data, obj.length, 0);
}

void String::PushAt(int32 index, int8 c)
{
	char arr[2] = { c, '\0' };
	Concat(arr, 1, index);
}

void String::PushAt(int32 index, int8 *cStr)
{
	Concat(cStr, Strlen(cStr), index);
}

void String::PopFront()
{
	Remove(1, true);
}

void String::PopFront(const int32 numberOfElements)
{
	Remove(numberOfElements, true);
}

void String::PopBack()
{
	Remove(1, false);
}

void String::PopBack(const int32 numberOfElements)
{
	Remove(numberOfElements, false);
}

//******
//GetChar
//if isStartPositionFront == false, then start position is back.
//Returns NULL if index is bigger then String length.
//******
const int8 String::GetCharAt(int index, bool isStartPositionFront)
{
	if (index > length || length == 0)
	{
		return NULL;
	}
	else if (isStartPositionFront)
	{
		return data[index];
	}
	else
	{
		return data[length - index];
	}
}

const int8 String::GetFirstChar()
{
	if (length > 0)
	{
		return data[0];
	}
	return NULL;
}

const int8 String::GetLastChar()
{
	if (length > 0)
	{
		return data[length -1];
	}
	return NULL;
}

const int32 String::Find(int8 c)
{
	for (int i = 0; i != length; ++i)
	{
		if (c == data[i])
		{
			return i;
		}
	}

	return -1;
}

const int32 String::FindReverse(int8 c)
{
	for (int i = length; i >= 0; --i)
	{
		if (c == data[i])
		{
			return i;
		}
	}
	return -1;
}

const bool String::Empty()
{
	return length < 1;
}

const int32 String::Length()
{
	return length;
}

const int32 String::Capacity()
{
	return capacity;
}

const int8* String::cStr()
{
	return data;
}

void String::operator=(const String &obj)
{
	length = 0;
	Concat(obj.data, obj.length, 0);
}

void String::operator=(const int8 *cStr)
{
	length = 0;
	Concat(cStr, Strlen(cStr), 0);
}

void String::operator=(const int8 c)
{
	length = 0;

	char arr[2] = { c, '\0' };
	Concat(arr, 1, 0);
}

String String::operator+(const String &obj)
{
	String string;
	string.Concat(data, length, 0);
	string.Concat(obj.data, obj.length, length);

	return string;
}

String String::operator+(const int8 *cStr)
{
	String string;
	string.Concat(data, length, 0);
	string.Concat(cStr, Strlen(cStr), length);

	return string;
}

String String::operator+(const int8 c)
{
	String string;
	string.Concat(data, length, 0);

	char arr[2] = { c, '\0' };
	string.Concat(arr, 1, length);

	return string;
}

void String::operator+=(const String &obj)
{
	Concat(obj.data, obj.length, length);
}

void String::operator+=(const int8 *cStr)
{
	Concat(cStr, Strlen(cStr), length);
}

void String::operator+=(const int8 c)
{
	char arr[2] = { c, '\0' };
	Concat(arr, 1, length);
}

//******
//operator[]
//Function has no boundary check!
//******
int8 &String::operator[](int32 index)
{
	return data[index];
}

void String::Concat(const int8 * cStr, int32 inputLength, int32 position)
{
	const int32 multiplier = 2;
	if (inputLength > 0)
	{
		//Initialize empty string.
		if (capacity == 0)
		{
			capacity = (inputLength * multiplier);
			length   = inputLength;

			data = new int8[capacity];
			memcpy(data, cStr, inputLength);
			data[length] = '\0';
		}
		else
		{
			if ((inputLength + length + 1) > capacity)
			{
				char *tmp = data;
				capacity = (length + inputLength) * multiplier;
				data = new int8[capacity];

				memcpy(data, tmp, position); //lhs
				memcpy(data + position, cStr, inputLength); //insert input string
				memcpy(data + position + inputLength, tmp + position, length - position); //rhs

				length += inputLength;
				data[length] = '\0';

				delete[] tmp;
				tmp = nullptr;
			}
			else
			{
				memcpy(data + position + inputLength, data + position, length - position); // rhs
				memcpy(data + position, cStr, inputLength); // insert input string
				

				length += inputLength;
				data[length] = '\0';
			}

		}
	}
	else
	{
		length = 0;
		data[0] = '\0';
	}
}

void String::Remove(int32 numberOfElements, bool removeFront)
{
	if (length > 0)
	{
		//Erase all
		if (numberOfElements > length)
		{
			length = 0;
		}
		//Pop back
		if (!removeFront)
		{
			length -= numberOfElements;
			data[length] = '\0';
		}
		//Pop front
		else
		{
			int8 *tmp = data;
			length   -= numberOfElements;
			data      = new int8[capacity];

			memcpy(data, tmp + numberOfElements, length);
			data[length] = '\0';

			delete[] tmp;
			tmp = nullptr;
		}
	}
}

int32 String::Strlen(const int8 * cStr)
{
	int len = 0;
	if (cStr != NULL)
	{
		while (*cStr++ != '\0')
		{
			++len;
		}
	}

	return len;
}

bool String::StrCmp(const int8 *lhs, const int8 *rhs)
{
	while (*lhs == *rhs) {
		if (*lhs == '\0' && *rhs == '\0')
		{
			return true;
		}

		++lhs;
		++rhs;
	}

	return false;
}

bool operator==(const String &lhs, const String &rhs)
{
	return String::StrCmp(lhs.data, rhs.data);
}

bool operator==(const String &lhs, const int8 *rhs)
{
	return String::StrCmp(lhs.data, rhs);
}

bool operator!=(const String &lhs, const String &rhs)
{
	return !(lhs.data == rhs.data);
}

bool operator!=(const String &lhs, const int8 *rhs)
{
	return !(lhs.data == rhs);
}
