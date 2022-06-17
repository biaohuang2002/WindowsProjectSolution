// TestLibrary.h - Contains declarations of math functions
#pragma once

#ifdef TESTLIBRARY_EXPORTS
#define TESTLIBRARY_API __declspec(dllexport)
#else
#define TESTLIBRARY_API __declspec(dllimport)
#endif

#include <string>
using namespace std;

// TestFirst
extern "C" TESTLIBRARY_API string TestFirst(string str);

// TestSecond
extern "C" TESTLIBRARY_API string TestSecond(string str);

// TestThird
extern "C" TESTLIBRARY_API string TestThird(string str);
