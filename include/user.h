#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdexcept>
#include <string.h>


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
};
