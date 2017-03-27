#include <memory>
#include <iostream>
#include <string>
#include <string.h>
#include <cstdio>

#ifndef STRFORMAT
#define STRFORMAT

using namespace std;

template<typename ... Args>
char* string_format( const std::string& format, Args ... args )
{
	size_t size = snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
	unique_ptr<char[]> buf( new char[ size ] ); 
	snprintf( buf.get(), size, format.c_str(), args ... );
	std::string tempstr= string( buf.get(), buf.get() + size - 1 ).c_str(); // We don't want the '\0' inside
	char* return_char = new char[tempstr.size()];
	strcpy(return_char,tempstr.c_str());
	return return_char;
}

// Remove the newline characters to handle linux and mac line endings
std::string removeNewlineChars(std::string input);

#endif
