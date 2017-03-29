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
#include "format.h"


#ifndef USER
class uchain;

class user
{
	private:
	int csock;
	char* name ;
	char* ip4 ;
	struct sockaddr addr;
	char* status = new char[100];
	user* next;
	uchain* chain;
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
	void SetStatus(const char* status_in);
	friend class uchain;
};

class uchain
{
	private:
		user* start;
		int nusers;
	public:
		uchain(user* firstuser=0);
		user* Get(int entry);
		int GetNentries();
		int Add(user* newuser);
		int List(user* watcher, const char* status="all");
		int Remove(user* olduser);
		int Remove(int csock);
		int Snd(const char* sndstr, user* exclude);
		int Snd(std::__cxx11::string sndstr, user* exclude);
		int CheckSameName(const char* target);
};
#define USER
#endif
