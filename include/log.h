#include<fstream>
#include<iostream>
#include<random>
#include<sys/socket.h>
#include<stdio.h>
#include<time.h>
#include<errno.h>

#include "user.h"



#ifndef LOG

std::string log(user* dummy);

#define LOG
#endif
