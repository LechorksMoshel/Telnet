#include "format.h"



using namespace std; //Don't if you're in a header-file


// Remove the newline characters to handle linux and mac line endings
std::string removeNewlineChars(std::string input){
    return input.erase(input.find_last_not_of(" \n\r\t")+1);
}

