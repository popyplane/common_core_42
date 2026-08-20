#ifndef PHONEBOOK_CLASS_HPP
# define PHONEBOOK_CLASS_HPP

# include "phoneBook.hpp"

// CLASS PHONEBOOK ////////////////////////////////////////

class PhoneBook
{
	private:

		int				_nbContacts;
		Contact			_contactList[8];

	public:

		bool			add(void);
		bool			search(void) const;
		void			displayPhoneBook(void) const;
		int				getNbContact(void);
		PhoneBook(void);
		~PhoneBook(void);
};

// PHONEBOOK PUBLIC MEMBERS ///////////////////////////////

bool	PhoneBook::add(void)
{
	this->_nbContacts++;
	return (PhoneBook::_contactList[(this->_nbContacts - 1) % 8].setContact());
}

bool	PhoneBook::search(void) const
{
	std::string	buffer;
	int			idx;

	displayPhoneBook();
	std::cout << std::endl << BLUE << "Choose a contact [1] - [8] : " << ENDCOLOR;
	std::getline(std::cin, buffer);
	std::cout << std::endl;

	idx = atoi(buffer.c_str()) - 1;

	if (buffer.length() == 1 && isdigit(buffer[0]) && idx < 8 && idx >= 0)
	{
		_contactList[idx].displayContact();
		return (true);
	}
	std::cout << RED << buffer << " : is an invalid index" << ENDCOLOR << std::endl;
	return (false);
}

int		PhoneBook::getNbContact(void)
{
	return (PhoneBook::_nbContacts);
}

void		PhoneBook::displayPhoneBook(void) const
{
	std::cout << YELLOW << "     index|first name| last name|  nickname|" << ENDCOLOR << std::endl;
	for (int i = 0; i < 8; i++)
		this->_contactList[i].displayShortContact(i);
}

PhoneBook::PhoneBook(void) : _nbContacts(-1)
{
	PhoneBook::_nbContacts++;
}

PhoneBook::~PhoneBook(void)
{
}

#endif