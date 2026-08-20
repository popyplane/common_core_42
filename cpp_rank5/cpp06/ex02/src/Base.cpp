#include "../inc/Base.hpp"

Base::~Base()
{}

Base    *generate()
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	int random = std::rand() % 3;

	switch (random)
	{
		case 0 :
			return (new A());
		case 1 :
			return (new B());
		case 2 :
			return (new C());
	}
	return (NULL);
}

void    identify(Base *p)
{
	if (dynamic_cast<A*>(p))
		cout << "*p is A class" << endl;
	else if (dynamic_cast<B*>(p))
		cout << "*p is B class" << endl;
	else if (dynamic_cast<C*>(p))
		cout << "*p is C class" << endl;
	else
		cout << "*p is NULL" << endl;
}

void    identify(Base &p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		cout << "&p is class A" << endl;
		return;
	}
	catch (std::exception const &e) {}
	
	try
	{
		(void)dynamic_cast<B&>(p);
		cout << "&p is class B" << endl;
		return;
	}
	catch (std::exception const &e) {}

	try
	{
		(void)dynamic_cast<C&>(p);
		cout << "&p is class C" << endl;
		return;
	}
	catch (std::exception const &e) {}
}