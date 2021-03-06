#include "log.h"

using namespace std;

string log(user* dummy)
{
	dummy->SetStatus("log");
	char* buffer = new char[BUFFER_LEN];
        char* filename_c = new char[300];
        time_t timer;
	time(&timer);
	tm* timeinfo = localtime(&timer);
        strftime(filename_c, 300, "%F", timeinfo);
	string filename="log/";
	filename.append(filename_c);
	//filename = Form("%i-%i-%i",timeinfo->tm_mday,timeinfo->tm_mon,timeinfo->tm_year);
	//cout<<filename<<endl;
        fstream fout(filename.c_str(), ios_base::app);
	dummy->Snd("Now you can type:\n");
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0,20);
	if(distribution(generator)==20) dummy->Snd("Do you know: Some times I use this to write my diary.\n");
	while(!dummy->IsZombie())
	{
		dummy->SetStatus("log");
		cout<<"a"<<endl;
		dummy->Rcv(buffer);
		cout<<"b"<<endl;
		string command(buffer);
		command = removeNewlineChars(command);
		cout<<"c"<<endl;
		if(command=="help"){
			dummy->Snd("help\t\tDisplay this help message.\nback\t\tReturn to the previous menu.\nexit\t\tCompletely logout.\n<else>\t\tLog the message you type.\n");
		}
		else if(command=="back"){
			return "back";
		}
		else if(command=="exit"||command=="logout"){
			return "exit";
		}
		else{
		cout<<"d"<<endl;
			fout<<dummy->GetName()<<"@"<<dummy->GetIP()<<":\t"<<command<<endl;
			if(!fout) cout<<"Establishing a new file!"<<endl;
			dummy->Snd("Now you can type:\n");
			cout<<"e"<<endl;
			//cout<<errno<<endl;
		}
	}
	return "exit";
}
