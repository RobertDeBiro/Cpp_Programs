/*
 * Passing std::unique_ptr to a function
 *  - in this example we are passing only pointer saved inside std::unique_ptr object
 *    and not whole object
 *  - we could also pass whole object by using std::move, but in that case we wouldn't have
 *    the object anymore inside main function, since it would be moved
 */ 

#include <iostream>
#include <memory> // std::unique_ptr

class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
    void sayHi() { std::cout << "Hi!\n"; }

	friend std::ostream& operator<<(std::ostream& out, const Resource &res)
	{
		out << "I am a resource";
		return out;
	}
};

// The function only uses the resource, so we'll accept a pointer to the resource,
// not a reference to the whole std::unique_ptr<Resource>
void useResource(Resource* res)
{
	if (res)
		std::cout << *res << '\n';
	else
		std::cout << "No resource\n";
}

int main()
{
    std::cout << "*****************************************************\n";

	auto ptr1{ std::make_unique<Resource>() }; // Constructor called
	auto ptr2{ std::make_unique<Resource> }; // Constructor not called

	useResource(ptr1.get()); // get() used here to get a pointer to the Resource

	std::cout << "Ending program\n";

    std::cout << "*****************************************************\n";
	return 0;
} // The Resource is destroyed here