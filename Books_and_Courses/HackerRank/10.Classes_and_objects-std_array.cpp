#include <vector>
#include <iostream>
#include <array>
#include <numeric>
using namespace std;

class Student
{
    std::array<int, 5> scores{};

public:
    void input()
    {
        for(decltype(scores.size()) i = 0; i < scores.size(); i++)
        {
            cin >> scores[i];
        }
    }

    int calculateTotalScore()
    {
        return (std::reduce(scores.begin(), scores.end()));
    }
};

int main() {
    cout << "*****************************************************\n";

    int n; // number of students
    cin >> n;
    Student *s = new Student[n]; // an array of n students
    
    for(int i = 0; i < n; i++){
        s[i].input();
    }

    // calculate kristen's score
    int kristen_score = s[0].calculateTotalScore();

    // determine how many students scored higher than kristen
    int count = 0; 
    for(int i = 1; i < n; i++){
        int total = s[i].calculateTotalScore();
        if(total > kristen_score){
            count++;
        }
    }

    // print result
    cout << count << '\n';

    cout << "*****************************************************\n";
    return 0;
}
