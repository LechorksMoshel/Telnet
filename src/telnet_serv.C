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

#include "parsing_options.h"
#include "user.h"
#include "performAction.h"
#include "format.h"

using namespace std;


void help_master(const char* action, user* dummy)
{
	string helpinfo;
	if(!action){
		helpinfo="Here is the list of currently available actions:\nlog\t\t||\tAny thing you type in this mode will be logged anonymously and be viewed later by the author. This is the place where you want to put your comment or unsatisfaction toward me. >.<\nchat\t\t||\tYou will enter a chatting room where you can chat with others who are also using this chatting room. However, I doubt there will be any. =.=\nMore functions on the way!\n";
	}
	else 	helpinfo=string_format("No help page about action %s! Check your spelling. \n",action);
	dummy->Snd(helpinfo);
}



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////




void* SocketHandler(void* lp){
    int *csock = (int*)lp;

    char buffer[1024];
    int buffer_len = 1024;
    int bytecount;

    // Upon first connection, set the working directory and send the MOD
    char path[2048];
    //string wd = getcwd(path, 2048);
    string program_dir = getcwd(path, 2048);
    string MOD = "Welcome to the Stupid Telnet Server. \nAuthor: The stupid and boring man.\n> ";
    const char* mod_string = MOD.c_str();
    if((bytecount = send(*csock, mod_string, strlen(mod_string), 0))== -1){
        cout << "Error sending data" << endl;
        shutdown(*csock, 0);
        return 0;
    }

    //Giving a name to the user
    string name("");
    const char* tellmeyourname="Tell me your name, or you can use a nickname.\n> ";
    if((bytecount = send(*csock, tellmeyourname, strlen(tellmeyourname), 0))== -1){
        cout << "Error sending data" << endl;
        shutdown(*csock, 0);
        return 0;
    }
    while(name.size()<1)
    {
    	memset(buffer, 0, buffer_len);
    	if((bytecount = recv(*csock, buffer, buffer_len, 0))== -1){
    	    cout << "Error receiving data" <<endl;

    	    return 0;
    	}
    	cout << "Received username: " <<  buffer;
    	name = buffer;
	name = removeNewlineChars(name);
    }

    //Setting up the user profile
    user dummy(csock, name.c_str());
    dummy.Snd(string_format("%s, Welcome! Type <help> to get list of avalable actions.\n",dummy.GetName()));
    dummy.Snd(dummy.GetName());
    dummy.Snd(">");

    // Loop the connection until logout is received
    while(true){

        memset(buffer, 0, buffer_len);
	dummy.Rcv(buffer);
        //cout << "Received string: " <<  buffer;
        string s(buffer);
	s=removeNewlineChars(s);
        // Get the response from the command and return it to the client
	string response="";
	if(s==""){response="";}
	else if(s=="help") {
		help_master(0,&dummy);
		response="help";
	}
        else response = performAction(s, &dummy);
        if(response.find("exit") == 0||response.find("logout")==0){
            // We are quitting
            response = "[END OF INPUT]\n";
	    dummy.Snd(response);
            cout << "Client disconnected" << endl;
            shutdown(*csock, 0);
            free(csock);
            return 0;
        }
	dummy.Snd(dummy.GetName());
	dummy.Snd(">");

        cout << "Sent bytes " << bytecount << endl;
    }
    cout << "Client disconnected" << endl;
    return 0;
}



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////



int main(int argc, char* argv[]){

    cout << "Launching telnet server" << endl;

    // Begin listening for a connection on port 6770 or whichever port is passed in
    // Default telnet port
    int listen_port = 6770 ; //Default value is 6770
    bool tests = false;

    //Parsing the options provided from the command line
    int par_result = parsing_options(argc, argv, &listen_port);//will chage listen_port if provided a user-defined port
    if(par_result!=0) return par_result;


    struct sockaddr_in host_addr;
    int sck = socket(AF_INET, SOCK_STREAM, 0);
    if(sck < 0){
        // There was an error opening the socket
        cout << "Error opening socket" << endl;
        return 1;
    }

    bzero((char*) &host_addr, sizeof(host_addr));

    host_addr.sin_family = AF_INET;
    host_addr.sin_addr.s_addr = INADDR_ANY;
    host_addr.sin_port = htons(listen_port);

    // Bind the socket to the host address
    if(bind(sck, (struct sockaddr*) &host_addr, sizeof(host_addr)) < 0){
        // Problem binding
        cout << "Error binding socket to host" << endl;
        return 1;
    }

    // Begin listening on the socket
    listen(sck, 5);

    // Begin server

    socklen_t addr_size = sizeof(sockaddr_in);
    int* csock;
    pthread_t thread_id = 0;

    // Run the server forever
    while(true){
        cout << "Waiting for a connection..." << endl;
        csock = (int*)malloc(sizeof(int));
        if((*csock = accept(sck, (sockaddr*)&host_addr, &addr_size)) >= 0){
            cout << "Received a connection" << endl;
            // A connection has been received, so spawn a thread to handle it
            pthread_create(&thread_id,0,&SocketHandler, (void*)csock );
            pthread_detach(thread_id);
        }
    }
}
