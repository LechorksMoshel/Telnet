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
#include <arpa/inet.h>

#include "const.h"


#ifndef USER

class user
{
	private:
	int csock;
	char* name ;
	char* ip4 ;
	struct sockaddr addr;
	public:
	user(int* csock_in, const char* name_in = "anonymous");
	void SetName(const char* name_in);
	void Refresh();
	const char* GetName();
	const char* GetIP();
	int GetSocket();
	int Rcv(char* buffer);
	int Snd(const char* sndstr);
	int Snd(std::__cxx11::string sndstr);
};
#define USER
#endif
