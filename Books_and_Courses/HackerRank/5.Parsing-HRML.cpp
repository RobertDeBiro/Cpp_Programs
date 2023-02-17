#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // std::remove_if
#include <cctype> // isalnum
#include <sstream> // stringstream
#include <map>
#include <unordered_map>
using namespace std;


int main() {
    cout << "*****************************************************\n";
    
    /*
     * 1. input:
     *  - N - the number of lines in the HRML
     *  - Q - the number of queries
     * 
     * 2. input:
     *  - HRML tags and queries, for example:
     * 
     *      4 3
     *      <tag1 value = "HelloWorld">
     *      <tag2 name = "Name1">
     *      </tag2>
     *      </tag1>
     *      tag1.tag2~name
     *      tag1~name
     *      tag1~value
     */

    /*
     * Get N and Q
     */
    int n, q;
    do{
        cin >> n >> q;
    } while(n < 1 || n > 20 || q < 1 || q > 20);
    // remove newline
    cin.ignore();

    /*
     * Get HRML and Querry
     */
    string temp;
    vector<string> hrmlRaw;
    vector<string> querryRaw;
    for(int i = 0;  i < n; i++)
    {
        getline(cin, temp);
        if (i < n)
            hrmlRaw.push_back(temp);
    }
    for(int i = 0;  i < q; i++)
    {
        getline(cin, temp);
        querryRaw.push_back(temp);
    }

    cout << "-----------------------------\n";

    /*
     * Parse HRML
     */
    // Set stringstream and strings needed for parsing
    stringstream strStream;
    string strTemp, hrmlAttr, hrmlValue;

    // Declare map where parsed hrml will be saved
    string hrmlTag{};
    map<string, string> hrmlAttrsValues{};
    map<string, map<string, string>> hrmlParsed;

    // Iterate through each line of the raw hrml
    for(auto& s : hrmlRaw)
    {
        if(s.find('/') != string::npos)
            continue;
        // Remove characters: <, >, =, ""
        auto remReq = [](char elem) { return (!isalnum(elem) && !isspace(elem)); };
        s.erase(remove_if(s.begin(), s.end(), remReq), s.end());

        // Input tag string into string stream
        //  - each iteration has to have cleared string stream
        strStream.str(string{});
        strStream.clear();
        strStream << s;

        // Clear the content of the map
        //  - every tag needs to have clear map for their own attributes and values
        hrmlAttrsValues.clear();

        bool tagSet = false, attrPresent = false;
        while(strStream >> strTemp)
        {
            if(!tagSet)
            {
                hrmlTag = strTemp;
                tagSet = true;
                continue;
            }
            if(!attrPresent)
                attrPresent = true;
            
            hrmlAttr = strTemp;
            strStream >> strTemp;
            hrmlValue = strTemp;

            hrmlAttrsValues.insert(std::make_pair(hrmlAttr, hrmlValue));
        }
        // Inside parsed hrml we will only put tags that contain at least one
        // attribute with corresponding value
        //  - if tag doesn't contain attributes, then we know that querry will for sure
        //    not find wanted attribute
        if(attrPresent)
            hrmlParsed.insert(std::make_pair(hrmlTag, hrmlAttrsValues));
    }

    /*
     * Parse querry and test the querry on hrml
     */
    for(auto& s : querryRaw)
    {
        string qTag, qAttr;
        
        // Find last occurence of '.' and return back the position
        string::size_type n = s.rfind(".");
        n++;

        // Insert characters as long as we don't encounter '~'
        while(s[n] != '~')
            qTag.push_back(s[n++]);
        // Skip '~' character
        n++;

        // Insert characters till the end of the string
        while(s[n])
            qAttr.push_back(s[n++]);
        
        // Test querry on hmrl
        auto searchTag = hrmlParsed.find(qTag);
        if(searchTag != hrmlParsed.end())
        {
            auto attrValueMap = searchTag->second;
            auto searchAttr = attrValueMap.find(qAttr);
            if(searchAttr != attrValueMap.end())
                cout << searchAttr->second << '\n';
            else
                cout << "Not Found!\n";
        }
        else
            cout << "Not Found!\n";
    }

    cout << "*****************************************************\n";
    return 0;
}
