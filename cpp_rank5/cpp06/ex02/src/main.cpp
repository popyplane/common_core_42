#include "../inc/Base.hpp"

int main()
{
	Base *p = generate();

	std::cout << "-- pointer --" << std::endl;
	identify(p);
	std::cout << "-- reference --" << std::endl;
	identify(*p);
	delete p;
	return (0);
}
