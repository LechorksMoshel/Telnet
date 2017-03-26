#include "performAction.h"
#include "format.h"

string performAction(string s, user* dummy)
{
	if(s.find("log")==0) return log(dummy);
	//else if(s=="chat") return chat(dummy);
	else{
		dummy->Snd(string_format("Action %s not defined.\n",s.c_str()));
		std::cout<<s<<endl;
		return "invalid";
	}
	return "exit";
}
