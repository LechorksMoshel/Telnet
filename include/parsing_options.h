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


int listen_port=6770;

void show_usage(const char* name);

bool is_number(const char* number);

int parsing_options(int argc, char* argv[]);
