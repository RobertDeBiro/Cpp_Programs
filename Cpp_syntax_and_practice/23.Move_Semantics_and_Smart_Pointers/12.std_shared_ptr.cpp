#include <iostream>
#include <memory> // std::shared_ptr

class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
    void sayHi() { std::cout << "Hi!\n"; }
};

int main()
{
    std::cout << "*****************************************************\n";

	// allocate a Resource object and have it owned by std::shared_ptr
	Resource *res { new Resource };
	std::shared_ptr<Resource> ptr1{ res };
	{
        // When we want to create a new shared_ptr we need to point it to already existing shared_ptr
        std::shared_ptr<Resource> ptr2 { ptr1 };

        // Following results with Exception ERROR
        //  - initializing new shared_ptr with object that is alread used for shared_ptr initialization
        //std::shared_ptr<Resource> ptr2 { res };

		std::cout << "Killing one shared pointer\n";
	} // ptr2 goes out of scope here, but nothing happens

	std::cout << "Killing another shared pointer\n";

    std::cout << "*****************************************************\n";
	return 0;
} // ptr1 goes out of scope here, and the allocated Resource is destroyed