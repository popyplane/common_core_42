#ifndef AFORM_HPP
# define AFORM_HPP

# include <iostream>
# include <exception>
# include <string>

# include "Bureaucrat.hpp"

using	std::string;
using	std::cout;
using	std::endl;

class Bureaucrat;

class AForm 
{
	private :
		const string	_name;
		bool			_signed;
		const int		_signGradeRequired;
		const int		_execGradeRequired;

	public :
		// canon
		AForm();
		AForm(const string name, const int signGR, const int execGR);
		AForm(const AForm &src);
		virtual ~AForm();
		AForm	&operator=(const AForm &src);

		// getters
		const string	getName() const;
		int				getSignGR() const;
		int				getExecGR() const;
		bool			isSigned() const;

		// member functions
		
		void			beSigned(const Bureaucrat &b);
		void			execute(const Bureaucrat &executor);
		virtual void	performExec() const = 0;

		// exceptions
		class GradeTooHighException : public std::exception {
			public :
				virtual const char	*what() const throw();
		};

		class GradeTooLowException : public std::exception {
			public :
				virtual const char	*what() const throw();
		};

		class FormNotSignedException : public std::exception {
			public :
				virtual const char *what() const throw();
		};
};

std::ostream	&operator<<(std::ostream &out, AForm const &src);

#endif