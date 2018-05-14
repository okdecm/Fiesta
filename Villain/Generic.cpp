#include <windows.h>
#include <fstream>

char* CreateBuffer(int size)
{
	char* buffer = new char[size];

	ZeroMemory(buffer, size);

	return buffer;
}

bool FileExists(char* path)
{
	return (bool)std::ifstream(path);
}