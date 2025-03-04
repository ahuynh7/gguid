#pragma once
#pragma warning(disable : 4996)		//_CRT_SECURE_NO_WARNINGS

#include <CLI/CLI.hpp>
#include <iostream>
#include <string>

//include platform specific headers/dependencies

#ifdef _WIN32
	#include <objbase.h>
#endif

#ifdef _LIBUUID
	#include <uuid/uuid.h>
#endif
