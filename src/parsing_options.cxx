#include "parsing_options.h"

using namespace std;

void show_usage(const char* name)
{
	cerr << "Usage: " << name <<" < options >"<<endl
		<<"Options: "<<endl
		<<"\t-h,--help\t\tShow this help message\n"
		<<"\t-p [port number]\t\tSpecifying a port number, the default number is 6770"
		<<endl;
}

bool is_number(const char* number)
{
	string s(number);
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int parsing_options(int argc, char* argv[])
{
	if(argc>1){
		for(int i =1; i < argc; i++){
			string arg(argv[i]);
			if((arg=="-h")||(arg=="--help")){
				show_usage(argv[0]);
				return 1;
			}
			else if(arg=="-p"){
				if(i+1<argc && is_number(argv[i+1])){
					listen_port=atoi(argv[i+1]);
					i++;
				}
				else{
					cerr << "-p provided but no port number specified or it is not a number."<<endl;
					return -1;
				}
			}
			else{
				cerr << "option "<<arg<<" unkown!"<<endl;
				show_usage(argv[0]);
				return -1;
			}
		}
	}

}
