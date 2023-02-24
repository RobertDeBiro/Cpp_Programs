/*
 * Input data:
 *  - n - number of Box tests
 *  - type - type of Box test
 *      - type == 1:
 *          - test default constructor and operator<<
 *      - type == 2:
 *          - test parameterized constructor (instantiate new Box)
 *          - test copy assignment
 *          - test operator<<
 *      - ...
 */

#include<bits/stdc++.h>

using namespace std;

class Box
{
    int m_l;
    int m_b;
    int m_h;

public:
    // Default constructor
    Box() : m_l{0}, m_b{0}, m_h{0}
    {
    }

    // Parameterized constructor
    Box(int l, int b, int h) : m_l{ l }, m_b{ b }, m_h{ h }
    {
    }

    // Copy constructor
    Box(const Box& box) : m_l{ box.m_l }, m_b{ box.m_b }, m_h{ box.m_h }
    {
    }

    // Copy assignment
    Box& operator==(const Box& box)
    {
        m_l = box.m_l;
        m_b = box.m_b;
        m_h = box.m_h;
        return *this;
    }

    // Functions must be 'const' in order to call them via const object Box from operator overloading
    // functions
    int getLength() const { return m_l; }
    int getBreadth() const { return m_b; }
    int getHeight() const { return m_h; }
    long long CalculateVolume() const { return static_cast<long long>(m_l) * m_b * m_h; }
};

bool operator< (const Box& box1, const Box& box2)
{
    int box1_l = box1.getLength();
    int box2_l = box2.getLength();
    int box1_b = box1.getBreadth();
    int box2_b = box2.getBreadth();
    int box1_h = box1.getHeight();
    int box2_h = box2.getHeight();
    return (box1_l < box2_l)
            || ((box1_b < box2_b) && (box1_l == box2_l))
            || ((box1_h < box2_h) && (box1_b == box2_b) && (box1_l == box2_l));
}

ostream& operator<< (ostream& out, const Box& box)
{
    out << box.getLength() << ' ' << box.getBreadth() << ' ' << box.getHeight();
    return out;
}

void check2()
{
	int n;
	cin>>n;
	Box temp;
	for(int i=0;i<n;i++)
	{
		int type;
		cin>>type;
		if(type ==1)
		{
			cout<<temp<<endl;
		}
		if(type == 2)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			temp=NewBox;
			cout<<temp<<endl;
		}
		if(type==3)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			if(NewBox<temp)
			{
				cout<<"Lesser\n";
			}
			else
			{
				cout<<"Greater\n";
			}
		}
		if(type==4)
		{
			cout<<temp.CalculateVolume()<<endl;
		}
		if(type==5)
		{
			Box NewBox(temp);
			cout<<NewBox<<endl;
		}

	}
}

int main()
{
    cout << "*****************************************************\n";

	check2();

    cout << "*****************************************************\n";
    return 0;
}