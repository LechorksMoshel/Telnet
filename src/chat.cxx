#include "chat.h"

using namespace std;

string chat(user* dummy, uchain* dummies)
{
	dummy->SetStatus("chat");
	dummy->Snd("Welcome to the relay channel, type /help to see available commands.\n");
	dummy->Snd(string_format("%s>",dummy->GetName()));
	char* buffer = new char[BUFFER_LEN];
	while(!dummy->IsZombie())
	{
		dummy->Rcv(buffer);
		string command(buffer);
		command = removeNewlineChars(command);
		if(command=="/help"){
			dummy->Snd("/help\t\tDisplay this help message.\n/back\t\tReturn to the previous menu.\n/exit\t\tCompletely logout.\n/who\t\tSee who is on.\n<else>\t\tTalk to everyone else online.\n");
		}
		else if(command=="/back"){
			return "back";
		}
		else if(command=="/exit"||command=="/logout"){
			return "exit";
		}
		else if(command=="/who"){
			dummies->List(dummy,"all");
		}
		else{
			dummies->Snd(string_format("\r%s>%s",dummy->GetName(),buffer),dummy);
		}
		dummy->Snd(string_format("%s>",dummy->GetName())); 
	}
	return "exit";
}
