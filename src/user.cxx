#include "user.h"

using namespace std;

user::user(int* csock_in, const char* name_in = "anonymous")
{
	csock = *csock_in;
	name = new char[200](name_in);
	if(getpeername(csock, &addr, sizeof(addr))<0)
		throw runtime_error("Error getting address from socket, user profile not initiated.");
	ip4 = new char[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &addr, ip4, INET_ADDRSTRLEN);
}

void user::SetName(const char* name_in)
{
	name=name_in;
}

void Refresh();//Reload the socketaddr from socket, just in case.
{
	if(getpeername(csock, &addr, sizeof(addr))<0)
		throw runtime_error("Error getting address from socket, user profile not initiated.");
	inet_ntop(AF_INET, &addr, ip4, INET_ADDRSTRLEN);
}

const char* GetName()
{
	return name;
}

const char* GetIP()
{
	return ip4;
}

int GetSocket()
{
	return csock;
}
