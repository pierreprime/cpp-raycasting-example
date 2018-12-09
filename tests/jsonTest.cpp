#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <nlohmann/json.hpp>
// C++ equivalent of associative array
#include <unordered_map>

using namespace std;
using json = nlohmann::json;


int main(int /*argc*/, char */*argv*/[])
{
	// load stream from JSON level file
	std::ifstream fileStream("levels/001.json", std::ifstream::binary);
	json myJsonObject;
	myJsonObject << fileStream;

	// warning : boolean is 1 in C++
	// DEMO JSON : field names describe types
	json demoJson = {
		{
			"boolean", true
		},
		{
			"number", {
				{
					"integer", 42
				},
				{
					"floating-point", 17.23
				}
			}
		},
		{
			"string", "Hello world"
		},
		{
			"array", {
				1, 2, 3, 4, 5
			}
		},
		{
			"null", nullptr
		}
	};

	// REACH FIELD OF GIVEN NAME AND AUTO CAST TO MATCHING TYPE
	auto v1 = demoJson["boolean"].get<bool>();
	auto v2 = demoJson["number"]["integer"].get<int>();
	auto v3 = demoJson["number"]["integer"].get<short>();
	auto v4 = demoJson["number"]["floating-point"].get<float>();
	auto v5 = demoJson["number"]["floating-point"].get<int>();
	auto v6 = demoJson["string"].get<std::string>();
	auto v7 = demoJson["array"].get<std::vector<short>>();
	auto v8 = demoJson.get<std::unordered_map<std::string, json>>();

	// display the six first values
	std::cout << v1 << '\n';
	std::cout << v2 << ' ' << v3 << '\n';
	std::cout << v4 << ' ' << v5 << '\n';
	std::cout << v6 << '\n';

	// display elements of array in "array" entry
	for (auto element : v7)
	{
		std::cout << element << ' ';
	}
	// line skip
	std::cout << "\n\n";

	for(auto element : v8)
	{
		std::cout << element.first << ": " << element.second << '\n';
	}

	// close file stream to free memory
	
	//fileStream.close();
}	

