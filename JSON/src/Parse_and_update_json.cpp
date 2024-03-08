/*
 * Saving data from .json file into object inside C++ program
 * - object must be of type Json::Value
 * - data is saved inside json object using another object of type Json::Reader
 * 
 * References:
 *  - https://www.youtube.com/watch?v=GYauneigGTs&t=4s
 *  - https://www.youtube.com/watch?v=2P4wdz1li5c&t=161s
 *  - https://github.com/open-source-parsers/jsoncpp
 */

#include <iostream>
#include <string>
#include "../inc/json.hpp"
#include <fstream> // std::ifstream

namespace Files
{
    const char* students{ "C:\\Users\\Robert\\Desktop\\IT\\Programs\\Random_files\\json\\students.json" };
}

int main()
{
    std::cout << "*****************************************************\n";

    // Using fstream to get the file pointer in "file"
    std::ifstream file{ Files::students };
    if(!file)
    {
        std::cerr << "File could not be opened for reading!\n";
        return 1;
    }

    Json::Value jsonData; 
    Json::Reader jsonReader;
    
    // Parsing json by using jsonReader
    // - parse() function transfers data from the file object (details.json file)
    //   into Json::Value jsonData object
    jsonReader.parse(file, jsonData);
    std::cout << "Total json data:\n" << jsonData << "\n";

    // Print jsonData parameters individually
    std::cout << "Name: " << jsonData["Name"] << '\n';
    std::cout << "Birth: " << jsonData["Birth"] << '\n';
    std::cout << "College: " << jsonData["College"] << '\n';

    std::cout << "----------------------------------------------\n";

    Json::Value jsonDataPractice;
    std::cout << "Empty Json::Value object: " << jsonDataPractice << '\n';

    jsonDataPractice["City"] = "Zagreb";
    std::cout << "Json::Value object: " << jsonDataPractice["City"] << '\n';
    
    // Following doesn't work!
    //  - it doesn't work because index of Json::Value must be typed as string
    //jsonDataPractice[1] = 1;
    //std::cout << "1. Json::Value object: " << jsonDataPractice[1] << '\n';

    std::cout << "----------------------------------------------\n";

    Json::Value request;
    request["msgId"] = "1";
    std::cout << "Json::Value request object: " << request["msgId"] << '\n';
    request["payload"]["query"].append("SELECT id, LicensedNumberOfBases FROM DeploymentLimits WHERE ActiveDeployment=1");
    std::cout << "Json::Value request object: " << request["payload"]["query"] << '\n';
    request["payload"]["query"].append("Random query");
    std::cout << "Json::Value request: " << request << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
