/*
 * LearnCpp
 * Basic Object-oriented Programming
 * Aggregation
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional> // std::reference_wrapper

class Teacher
{
private:
    std::string m_name{};
 
public:
    Teacher(const std::string& name)
        : m_name{ name }
    {
    }

    // Inside classes we can return by reference because attribute won't be destroyed
    // at the end of function
    const std::string& getName() const { return m_name; }
};
 
class Department
{
private:
    // 'std::vector' (and 'std::array' and other STL containers) can't hold a normal reference
    // because container elements must be assignable, and references can't be reassigned
    std::vector<std::reference_wrapper<const Teacher>> m_teachers{};
 
public:
    void add(const Teacher& teacher)
    {
        m_teachers.push_back(teacher);
    }

    friend std::ostream& operator<<(std::ostream& out, const Department& department)
    {
        out << "Department: ";
        
        for (const auto& teacher : department.m_teachers)
        {
            // '.get()' is member function of 'std::reference_wrapper' and it accesses the stored element
            out << teacher.get().getName() << ' ';
        }
 
        out << '\n';
 
        return out;
    }
};
 
int main()
{
    std::cout << "*****************************************************\n";

    //* Create a teacher outside the scope of the Department
    Teacher t1{ "Bob" };
    Teacher t2{ "Frank" };
    Teacher t3{ "Beth" };

    {
        //* Create a department and add some Teachers to it
        //  - parent: 'Department'
        //  - child: 'Teacher'
        Department department{}; // create an empty Department

        department.add(t1);
        department.add(t2);
        department.add(t3);

        std::cout << department;

    } // department goes out of scope here and is destroyed

    //* In aggregation, the child does not have its existence managed by the parent
    std::cout << t1.getName() << " still exists!\n";
    std::cout << t2.getName() << " still exists!\n";
    std::cout << t3.getName() << " still exists!\n";

    std::cout << "*****************************************************\n";
    return 0;
}
