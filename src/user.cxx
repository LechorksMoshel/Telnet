#include "user.h"

using namespace std;

user::user(int* csock_in, const char* name_in)
{
	int size_addr = sizeof(addr);
	csock = *csock_in;
	name = new char[200];
	strcpy(name, name_in);
	if(getpeername(csock, &addr, (socklen_t*)(&size_addr))<0)
		throw runtime_error("Error getting address from socket, user profile not initiated.");
	ip4 = new char[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &addr, ip4, INET_ADDRSTRLEN);
}

void user::SetName(const char* name_in)
{
	strcpy(name,name_in);
}

void user::Refresh()//Reload the socketaddr from socket, just in case.
{
	int size_addr = sizeof(addr);
	if(getpeername(csock, &addr, (socklen_t*)&size_addr)<0)
		throw runtime_error("Error getting address from socket, user profile not initiated.");
	inet_ntop(AF_INET, &addr, ip4, INET_ADDRSTRLEN);
}

const char* user::GetName()
{
	return name;
}

const char* user::GetIP()
{
	return ip4;
}

int user::GetSocket()
{
	return csock;
}

//More convenient to receive data from client
int user::Rcv(char* buffer)
{
	int bytecount=0;
	int buffer_len = BUFFER_LEN;
    	memset(buffer, 0, buffer_len);
    	if((bytecount = recv(csock, buffer, buffer_len, 0))== -1){
    	    cout << "Error receiving data" <<endl;
    	}
	cout<<"received string: "<<buffer<<endl;
    	    return bytecount;

}

int user::Snd(const char* sndstr)
{
	int bytecount=0;
	if((bytecount = send(csock, sndstr, strlen(sndstr), 0))== -1){
        cout << "Error sending data" << endl;
        shutdown(csock, 0);
	}
        return bytecount;
}

int user::Snd(string sndstr)
{
	return user::Snd(sndstr.c_str());
}
