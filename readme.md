+++
Categories = ["network","c++"]
Tags = ["network","c++"]
Description = ""
date = "2017-03-21T03:56:54-07:00"
title = "Stupid Telnet Server"
menu = "projects"

+++

This is a for-fun project, and I have finally enabled the **chat** mode! In this mode you can send a message to everyone else who is also connected to this server (whether they are in the chat mode or not). In the chat mode commands shoud be preceded with a '/'. Such as "/help" for the list of available commands, "/who" to see who is also connected and what they are doing, "/back" to quit the chat mode.

**Known bugs**

+ The display will be quite weired if someone send a message to you when you are still typing, but what you send won't be affected. (In this case what others see will be a little different from what you see on your screen).
+ If you close your connection with [ctrl-c] or any other method other than using the "exit" command, you will still be on the list of connected users until someone send a message to everyone. (So that the system know that you have disconnected.)

Please report other problems or suggestions to me!

------------

**Currently supported functions**

+ *log*: 	Recorde messages at the server side so that the server host will be able to view them later. These messages won't be saw by other users online.
+ *chat*:	Send messages to other connected users like an IRC channel. 


------------

Most of the basic functions are achieved by implementing a *user* class and a *uchain* class:

```cpp
//In file user.h
#ifndef USER
class uchain;

class user
{
	private:
	int csock;//Socket descriptor of the user
	char* name ;//Username
	char* ip4 ;//User's ip address
	struct sockaddr addr;
	char* status = new char[100];//User's current state
	user* next;//Users are stored in a chain
	uchain* chain;//belonged chain
	public:
	user(int* csock_in, const char* name_in = "anonymous");//constructor
	void SetName(const char* name_in);
	void Refresh();
	const char* GetName();
	const char* GetIP();
	int GetSocket();
	int Rcv(char* buffer);//Receive a message from the user
	int Snd(const char* sndstr);//Send a message to the user
	int Snd(std::__cxx11::string sndstr);
	void SetStatus(const char* status_in);//Set the current state of the user
	friend class uchain;
};

class uchain
{
	private:
		user* start;//The first user in the chain
		int nusers;//Number of users connected
	public:
		uchain(user* firstuser=0);
		user* Get(int entry);//Get the nth user
		int GetNentries();//Get the number of users
		int Add(user* newuser);//Add a new user to the chain
		int List(user* watcher, const char* status="all");//List current users and their states
		int Remove(user* olduser);//Remove a user from the chain
		int Remove(int csock);
		int Snd(const char* sndstr, user* exclude);//Send a message to everyone except the user who call this function
		int Snd(std::__cxx11::string sndstr, user* exclude);
		int CheckSameName(const char* target);//Check if the user's name is the same as any other user's name
};
#define USER
#endif
```

PS: The syntax highlighting is working, excellent!

PPS: The defualt port number is 6770, and a daemon is already listning on this site, but I changed the port to 23 so that you can connect to it without specify the port number. Which is to say, you can access it by typing the following command in your terminal:

```html
telnet yuansq.cc 
```

For Windows users, *telnet* can be enabled in the *enable or disable windows functions*. For Mac users *telnet* should be already installed in your computer. And if you are using Linux, there is no way you don't know *telnet*.
