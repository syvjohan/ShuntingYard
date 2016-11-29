#include "Stream.h"

#include <cassert>

Stream::Stream()
{

}

Stream::Stream(const int8 *path) {
	currentByte = 0;
	Win32SetWorkingDirectory();

	HANDLE hFile = Win32OpenFile(path, GENERIC_READ);
	if (hFile)
	{
		printf("Open file for reading\n");
		fileSize = Win32GetFileSize(path, hFile);
		if (fileSize > 0)
		{
			fileBuffer = new char[fileSize];
			Win32ReadFromFile(hFile, fileSize, fileBuffer);
			
			Win32CloseFile(hFile);
			printf("Successfully read from file.\nClosed file.\n");
		}
		else
		{
			printf("Cannot read from empty file!\n");
		}
	}
	else
	{
		printf("Could not open file!\n");
	}

	SetCurrentDirectory(workingDirectory); //Reseting path.
}

Stream::~Stream()
{

}

bool Stream::Win32SetWorkingDirectory() {
	int8  buffer[MAX_PATH];
	int32 length = GetModuleFileName(NULL, buffer, MAX_PATH);
	if (length > MAX_PATH) {
		return false;
	}

	//go back...
	const char *subPath = strstr(buffer, "Debug");
	int subLen = strlen(subPath);
	buffer[length - subLen] = '\0';

	if (!SetCurrentDirectory(buffer)) {
		return false;
	}

	strcpy_s(workingDirectory, buffer);
	return true;
}

// ******
// Win32OpenFile
// ******
HANDLE Stream::Win32OpenFile(const int8 *path, int32 flags) {
	int createFlags = 0;
	if (flags & GENERIC_WRITE)
	{
		createFlags |= CREATE_ALWAYS;
	}
	else
	{
		createFlags |= OPEN_EXISTING;
	}

	HANDLE hFile = CreateFile(path, flags, 0, NULL, createFlags, FILE_ATTRIBUTE_NORMAL, NULL);
	assert(hFile);
	return hFile;
}

// ******
// Win32CloseFile
// ******
void Stream::Win32CloseFile(HANDLE &hFile) {
	CloseHandle(hFile);
}

// ******
// Win32WriteToFile
// ******
void Stream::Win32WriteToFile(HANDLE hFile, const void *data, int32 bytesToWrite, int32 startPos) {
	DWORD bytesWritten = startPos;
	const unsigned char *ptr = (unsigned char*)data;

	do {
		WriteFile(hFile, ptr, bytesToWrite, &bytesWritten, NULL);
		bytesToWrite -= bytesWritten;
		ptr += bytesWritten;
	} while (bytesToWrite > 0);
}

// ******
// GetFileSize
// ******
int32 Stream::Win32GetFileSize(const int8 *path, HANDLE hFile)
{
	LARGE_INTEGER size;
	bool success = GetFileSizeEx(hFile, &size);
	assert(success);
	/* NOTE (Johan 2016-10-12): LARGE_INTEGER returns twice the acctual size probably has something to do with VS 32-bit and function is for 64-bit.  */
	/* NOTE (Johan 2016-10-12): An empty file(size.QuadPart) contains number 2  */
	if (size.QuadPart == 2) {
		return 0;
	}

	return size.QuadPart;
}

// ******
// Win32ReadFromFile
// ******
void Stream::Win32ReadFromFile(HANDLE hFile, UINT bytesToRead, void *buffer)
{
	DWORD bytesRead = 0;
	unsigned char *ptr = (unsigned char*)buffer;

	do {
		ReadFile(hFile, ptr, bytesToRead, &bytesRead, NULL);
		bytesToRead -= bytesRead;
		ptr += bytesRead;
	} while (bytesToRead > 0);
}

bool Stream::GetNextByte(int8 &byte) {
	if (currentByte != fileSize)
	{
		byte = fileBuffer[currentByte++];
		return true;
	}
	return false;
}

bool Stream::SneakPeekOnNextByte(int8 &byte)
{
	if (currentByte != fileSize)
	{
		byte = fileBuffer[currentByte];
		return true;
	}
	return false;
}

int32 Stream::CountCharacter(const char c) {
	int numberOfC = 0;
	for (int i = 0; i != fileSize; ++i) {
		if (fileBuffer[i] == c) {
			++numberOfC;
		}
	}
	return numberOfC;
}
