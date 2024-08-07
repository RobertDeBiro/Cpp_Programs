/*
 * Saving data from .json file into object inside C++ program
 * - object must be of type 'Json::Value'
 * - data is saved inside json object using another object of type 'Json::Reader'
 */

#include <iostream>
#include <string>
#include "../inc/json.hpp"
#include <fstream>

namespace Files
{
    //* Windows paths
    // const char* filename{ "C:\\Users\\Robert\\Desktop\\IT\\Programs\\Random_files\\json\\students.json" };

    //* Linux paths
    const char* filename{ "/home/robert/IT/Files_for_testing/Students" };
}

int main()
{
    std::cout << "*****************************************************\n";

    // Using 'fstream' to get the file pointer in "file"
    std::ifstream input_json_file{ Files::filename };
    if(!input_json_file)
    {
        std::cerr << Files::filename << " file could not be opened for reading!" << std::endl;
        return 1;
    }

    Json::Value jsonData; 
    Json::Reader jsonReader;
    
    // Parsing json by using 'jsonReader'
    // - 'parse()' parses "JSON string" from the input file into "'Json::Value' object"
    jsonReader.parse(input_json_file, jsonData);
    std::cout << "Total json data:\n" << jsonData << "\n";

    // Print 'jsonData' parameters individually
    std::cout << "Name: " << jsonData["Name"] << '\n';
    std::cout << "Birth: " << jsonData["Birth"] << '\n';
    std::cout << "College: " << jsonData["College"] << '\n';

    std::cout << "----------------------------------------------\n";

    Json::Value jsonDataPractice;
    std::cout << "Empty Json::Value object: " << jsonDataPractice << '\n';

    jsonDataPractice["City"] = "Zagreb";
    std::cout << "Json::Value object: " << jsonDataPractice["City"] << '\n';
    
    // Following doesn't work!
    //  - it doesn't work because index of 'Json::Value' must be typed as string
    //!jsonDataPractice[1] = 1;
    //!std::cout << "1. Json::Value object: " << jsonDataPractice[1] << '\n';

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
