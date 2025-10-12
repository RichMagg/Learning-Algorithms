#include <iostream>
#include <map>
#include <algorithm>

static std::map<std::string, bool> voted = 
{
	{ "bob", true },
	{ "john", true },
	{ "willian", true },
	{ "larry", true }
};

bool check_vote(std::string name) 
{
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	
	if (voted.find(name) != voted.end() && voted.at(name) == true) 
	{
		std::cout << "Get out of here!" << std::endl;
		return false;
	}
	
	voted[name] = true;
	std::cout << "You can vote!" << std::endl;
	return true;
}

int main(int argc, char* argv[]) 
{
	while (true) 
	{
		std::string name;
		
		std::cout << "Please, enter your name: ";
		getline(std::cin, name);
		
		check_vote(name);
		
		std::cin.get();
		std::cin.clear();
		
		system("clear");
	}
	return 0;
}