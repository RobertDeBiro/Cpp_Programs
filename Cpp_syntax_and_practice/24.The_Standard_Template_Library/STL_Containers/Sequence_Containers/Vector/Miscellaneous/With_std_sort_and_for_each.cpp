/*
 * LearnCpp
 * Arrays, Strings, and Dynamic Allocation
 * Summary and quiz
 */

#include <iostream>
#include <string>
#include <algorithm> // std::sort
#include <cstddef> // std::size_t
#include <vector> // std::vector

struct Student
{
    std::string name{};
    int grade{};
};

int getNumberOfStudents()
{
    int numberOfStudents{};
    do
    {
        std::cout << "How many students do you want to enter: ";
        std::cin >> numberOfStudents;
    } while (numberOfStudents <= 0);

    return numberOfStudents;
}

std::vector<Student> getStudents()
{
    using vector_type = std::vector<Student>;

    int numberOfStudents{ getNumberOfStudents() };

    // Create a vector with 'numberOfStudents' elements
    // - when constructing vector of multiple same elements, number of elements put into
    //   vector constructor is of type 'size_type'
    vector_type students(static_cast<vector_type::size_type>(numberOfStudents));

    int studentNumber{ 1 };

    for (auto& student : students)
    {
        std::cout << "Enter name #" << studentNumber << ": ";
        std::cin >> student.name;
        std::cout << "Enter grade #" << studentNumber << ": ";
        std::cin >> student.grade;

        ++studentNumber;
    }
    std::cout << "-------------------------------------\n";

    return students;
}

// When 'compareStudents' returns 'true', means that elements are already sorted
bool compareStudents(const Student& a, const Student& b)
{
    return (a.grade > b.grade);
}

int main()
{
    std::cout << "*****************************************************\n";

    auto students{ getStudents() };

    // Sorting students in descending order
    std::sort(students.begin(), students.end(), compareStudents);

    // Print out all the names
    for (const auto& student : students)
    {
        std::cout << student.name << " got a grade of " << student.grade << '\n';
    }

    std::cout << "*****************************************************\n";
    return 0;
}
