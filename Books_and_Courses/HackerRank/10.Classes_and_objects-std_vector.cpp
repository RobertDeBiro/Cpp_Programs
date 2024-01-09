#include <vector>
#include <iostream>
using namespace std;

class Student
{
    std::vector<int> scores;

public:
    void input()
    {
        int temp;
        // Input 5 scores
        for(int i = 0; i < 5; i++)
        {
             cin >> temp;
             scores.push_back(temp);
        }
    }

    int calculateTotalScore()
    {
        int total{};
        for(decltype(scores.size()) i = 0; i < scores.size(); i++)
        {
            total += scores[i];
        }
        return total;
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
