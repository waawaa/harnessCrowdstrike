#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

extern "C" __declspec(dllexport) __declspec(noinline) int fuzzme(char* path);
typedef int (*fuzz)(char* data);


int main(int argc, char* argv[1])
{
	if (argc != 2)
		return 0;
	int result = fuzzme(argv[1]);
	return 0;
}


extern "C" __declspec(dllexport) __declspec(noinline) int fuzzme(char* path)
{
	char input[0x4000];
	HMODULE libraryHandle = LoadLibraryA("DllFuzz.dll");
	fuzz funcHandle = (fuzz)GetProcAddress(libraryHandle, "fuzz");
	int result = funcHandle(path);

	return 0;
}