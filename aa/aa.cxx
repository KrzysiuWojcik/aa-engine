#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include "trigger_runner.hpp"

using json = nlohmann::json;


int foo() { return 1; }
int bar() { return 42; }


int main(int argc, char** argv)
{
	using namespace std;

	std::map<std::string, std::function<int()>> triggers{
        {"foo", foo},
        {"bar", bar}
    };


	if(argc < 4)
	{
		cerr << "TOO FEW ARGS SUPPLIED\n";
		return 1;
	}
	string confile = (string)argv[1];
	ifstream f(confile);
	json CONF = json::parse(f);

	if((bool)CONF["is_aa_config"])
		cout << (string)CONF["version"] << endl;
	else
		cerr << "SUPPLIED CONF IS NOT AA CONF !!!\n";

	vector<string> IDEN = ((map<string,vector<string>>)CONF["aa"])["identifier_list"];

	for (string v : IDEN)
		cout << v << endl;

	string name = argv[3];

    // 2. check if trigger exists
    auto it = triggers.find(name);
    if (it == triggers.end()) {
        cerr << "Error: unknown trigger '" << name << "'\n";
        return 1;
    }

    // 3. execute function and return its value
    return it->second();

	return 0;
}
