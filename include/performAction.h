#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "user.h"
#include "log.h"
#include "chat.h"

using namespace std;

#ifndef PERFORMACTION

string performAction(string s, user* dummy);

#define PERFORMACTION
#endif
