#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <exception>
# include <string>

# include "Bureaucrat.hpp"

using	std::string;
using	std::cout;
using	std::endl;

class Bureaucrat;

class Form {

	private :
		const string	_name;
		bool			_signed;
		const int		_signGradeRequired;
		const int		_execGradeRequired;

	public :
		// canon
		Form();
		Form(const string name, const int signGR, const int execGR);
		Form(const Form &src);
		~Form();
		Form	&operator=(const Form &src);

		// getters
		const string	getName() const;
		int				getSignGR() const;
		int				getExecGR() const;
		bool			isSigned() const;

		// member functions
		
		void			beSigned(const Bureaucrat &b);

		// exceptions
		class GradeTooHighException : public std::exception {
			public :
				virtual const char	*what() const throw();
		};

		class GradeTooLowException : public std::exception {
			public :
				virtual const char	*what() const throw();
		};
};

std::ostream	&operator<<(std::ostream &out, Form const &src);

#endif