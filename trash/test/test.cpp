#include<iostream>
#include<fstream>
#include<time.h>
#include<errno.h>

using namespace std;

int main()
{
        char filename[300];
        time_t timer;
	time(&timer);
        strftime(filename, 300, "%F", localtime(&timer));
	//
	//cout<<timer->tm_year<<"-"<<timer->tm_mon<<endl;
	cout<<filename<<endl;
        fstream fout(filename, ios_base::app);
        if(!fout) cout<<"error establishing the file!"<<endl;
        fout<<"testing!"<<endl;
        cout<<errno<<endl;
	return 0;
}
