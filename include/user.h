#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <string>


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
