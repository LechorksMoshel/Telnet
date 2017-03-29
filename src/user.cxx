#include "user.h"

using namespace std;

user::user(int* csock_in, const char* name_in)
{
	int size_addr = sizeof(addr);
	csock = *csock_in;
	name = new char[200];
	strcpy(name, name_in);
	if(getpeername(csock, &addr, (socklen_t*)(&size_addr))<0&&strcmp(name,"mastermind")!=0)
		throw runtime_error("Error getting address from socket, user profile not initiated.");
	ip4 = new char[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &addr, ip4, INET_ADDRSTRLEN);
	strcpy(status,"main");
	chain=0;
	next=0;
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
	cout<<bytecount<<endl;
    	    cout << "Error receiving data" <<endl;
	    if(chain) chain->Remove(this);
	    shutdown(csock, 0);
    	}
	cout<<bytecount<<endl;
	cout<<"received string: "<<buffer<<endl;
    	    return bytecount;

}

int user::Snd(const char* sndstr)
{
	int bytecount=0;
	cout<<sndstr<<endl;
	if((bytecount = send(csock, sndstr, strlen(sndstr),MSG_NOSIGNAL))== -1){
        cout << "Error sending data" << endl;
	if(chain) chain->Remove(this);
        shutdown(csock, 0);
	}
        return bytecount;
}

int user::Snd(string sndstr)
{
	return user::Snd(sndstr.c_str());
}

void user::SetStatus(const char* status_in)
{
	strcpy(status,status_in);
}

bool user::IsZombie()
{
	string status_string(status);
	if(status_string=="zombie") return true;
	else return false;
}


uchain::uchain(user* firstuser)
{
	start = firstuser;
	if(!start) nusers=0;
	else nusers=1;
}

int uchain::GetNentries()
{
	return nusers;
}

user* uchain::Get(int entry)
{
	if(entry<0) return 0;
	if(entry>=nusers) return 0;
	user* tmp=start;
	if(nusers==1) return tmp;
	for(int i=1;i<nusers;i++)
	{
		tmp=tmp->next;
	}
	return tmp;
}

int uchain::Add(user* newuser)
{
	if(!newuser) return 0;
	user* tmp=0;
	if(!nusers) start=newuser; 
	else {
		tmp=Get(nusers-1);
		tmp->next=newuser;
	}
	nusers++;
	newuser->chain=this;
	return nusers;
}

int uchain::List(user* watcher, const char* status)
{
	string search_status=status;
	if(search_status=="all") search_status="mainlogstatuszombie";
	user* tmp=start;
	watcher->Snd(string_format("\tName      \tStatus\n"));
	while(tmp)
	{
		if(search_status.find(tmp->status)>=0){
			watcher->Snd(string_format("\t%-10s\t%s\n",tmp->GetName(),tmp->status));
		}
		tmp=tmp->next;
	}
}

int uchain::Remove(user* olduser)
{
	olduser->SetStatus("zombie");
	user* tmp=start;
	int entry=1;
	while(tmp->next)
	{
		if(tmp->next->csock==olduser->csock){
			cout<<"!"<<endl;
			tmp->next=olduser->next;
			nusers--;
			break;
		}
		tmp=tmp->next;
		entry++;
	}
	if(entry>=nusers) return -1;
	else return entry;
}

int uchain::Remove(int csock)
{
	user* tmp=start;
	user* olduser=0;
	int entry=0;
	while(tmp->next)
	{
		if(tmp->next->csock==csock){
			olduser = tmp->next;
			olduser->SetStatus("zombie");
			tmp->next=olduser->next;
			nusers--;
			break;
		}
		tmp=tmp->next;
		entry++;
	}
	if(entry>=nusers) return -1;
	else return entry;
}

int uchain::Snd(const char* sndstr, user* sender)
{
	user* tmp=start->next;
	int entry=0;
	char* buffer_in = new char[BUFFER_LEN];
	while(tmp) 
	{
			cout<<tmp->GetName()<<endl;
		if(tmp->csock!=sender->csock){
			int bytecount=0;
			string newstring = sndstr;
			recv(tmp->csock,buffer_in,BUFFER_LEN,MSG_DONTWAIT);//Trying to matin the input buffer, but no luck
			newstring.append(string_format("%s>%s",tmp->GetName(),buffer_in));
			if((bytecount = send(tmp->csock, newstring.c_str(), strlen(newstring.c_str()),MSG_NOSIGNAL))== -1){
			cout << "Error sending data to "<<tmp->GetName() << endl;
			shutdown(tmp->csock, 0);
			user* trash=tmp;
			tmp=tmp->next;
			this->Remove(trash);
			continue;
			}
		}
		tmp=tmp->next;
		entry++;
	}
        return entry;
}

int uchain::Snd(string sndstr, user* sender)
{
	return uchain::Snd(sndstr.c_str(), sender);
}

int uchain::CheckSameName(const char* target)
{
	cout<<target<<endl;
	if(strlen(target)<3||strlen(target)>10) return 100;
	user* tmp=start;
	int entry=0;
	string target_string(target);
	while(tmp)
	{
		if(target_string==tmp->GetName()) return entry;
		tmp=tmp->next;
		cout<<(void*) tmp<<endl;
		entry++;
	}
	return -1;
}
