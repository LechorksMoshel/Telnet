#incldue "log.h"

string log(user* dummy)
{
        char* filename = new char[100];
        time_t timer;
	time(&timer);
	tm* timeinfo = localtime(&timer);
        strftime(filename, 100, "%F", timeinfo);
	//filename = Form("%i-%i-%i",timeinfo->tm_mday,timeinfo->tm_mon,timeinfo->tm_year);
	//cout<<filename<<endl;
        fstream fout(filename, ios_base::app);
	user->Snd("Now you can type:\n");
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0,20);
	if(distribution(generator)==20) user->Snd("Do you know: Some times I use this to write my diary.");
	fout<<cname<<">"<<command<<endl;
        if(!fout) cout<<"Establishing a new file!"<<endl;
        cout<<errno<<endl;
}
