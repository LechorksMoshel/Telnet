#include "performAction.h"

string performAction(string s, user* dummy)
{
	if(s=="log") return log(dummy);
	//else if(s=="chat") return chat(dummy);
	else{
		user->Snd(Form("Action %s not defined.\n",s));
		return "invalid";
	}
	return "exit";
}
