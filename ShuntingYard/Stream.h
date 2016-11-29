#pragma once

#include <stdio.h>
#include <Windows.h>
#include <string>

#include "Types.h"

class Stream
{
public:
	Stream();
	Stream(const int8 *path);
	~Stream();

	bool  GetNextByte(int8 &);
	int32 CountCharacter(const int8 c);
	bool  SneakPeekOnNextByte(int8 &);

private:
	int32 fileSize;
	int8  *fileBuffer;
	int32 currentByte;

	char workingDirectory[MAX_PATH];

	bool   Win32SetWorkingDirectory();
	HANDLE Win32OpenFile(const int8 *, int32);
	void   Win32CloseFile(HANDLE &);
	void   Win32WriteToFile(HANDLE, const void *, int32, int32);
	int32  Win32GetFileSize(const int8 *, HANDLE);
	void   Win32ReadFromFile(HANDLE, UINT, void *);

};

