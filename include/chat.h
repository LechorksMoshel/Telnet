#include<fstream>
#include<iostream>
#include<random>
#include<sys/socket.h>
#include<stdio.h>
#include<time.h>
#include<errno.h>

#include "user.h"
#include "const.h"
#include "format.h"



#ifndef CHAT

std::string chat(user* dummy, uchain* dummies);

#define CHAT
#endif
