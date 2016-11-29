#pragma once

#include "Types.h"

class String;

bool operator==(const String &lhs, const String &rhs);
bool operator==(const String &lhs, const String &rhs);

bool operator!=(const String &lhs, const String &rhs);
bool operator!=(const String &lhs, const int8 *rhs);

class String
{
public:
	String();
	String(const int8);
	String(const int8 *);
	String(const String &);
	~String();

	void PushBack(const int8);
	void PushBack(const int8 *);
	void PushBack(const String &);

	void PushFront(const int8);
	void PushFront(const int8 *);
	void PushFront(const String &);

	void PushAt(int32, int8);
	void PushAt(int32, int8 *);

	void PopFront();
	void PopFront(const int32);

	void PopBack();
	void PopBack(const int32);

	const int8 GetCharAt(int index, bool isStartPositionFront);
	const int8 GetFirstChar();
	const int8 GetLastChar();

	const int32 Find(int8);
	const int32 FindReverse(int8);

	const bool Empty();

	const int32 Length();
	const int32 Capacity();

	const int8* cStr();

	void operator=(const String &);
	void operator=(const int8 *);
	void operator=(const int8);

	String operator+(const String &);
	String operator+(const int8 *);
	String operator+(const int8);

	void operator+=(const String &);
	void operator+=(const int8 *);
	void operator+=(const int8);

	int8 &operator[](int32);

	friend bool operator==(const String &, const String &);
	friend bool operator==(const String &, const int8 *);

	friend bool operator!=(const String &, const String &);
	friend bool operator!=(const String &, const int8 *);

private:
	int32 capacity;
	int32 length;
	int8  *data;

	void Concat(const int8 *, int32, int32);
	void Remove(int32, bool);
	int32 Strlen(const int8 *);
	static bool StrCmp(const int8 *, const int8 *);
};

