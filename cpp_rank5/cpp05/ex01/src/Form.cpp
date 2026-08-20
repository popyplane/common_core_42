#include "../inc/Bureaucrat.hpp"

Form::Form() : _name("default"), _signed(false), _signGradeRequired(150), _execGradeRequired(150)
{
}

Form::Form(const string name, const int signGR, const int execGR) : _name(name), _signed(false), _signGradeRequired(signGR), _execGradeRequired(execGR)
{
	if (this->_signGradeRequired < 1 || this->_execGradeRequired < 1)
		throw (GradeTooHighException());
	if (this->_signGradeRequired > 150 || this->_execGradeRequired > 150)
		throw (GradeTooLowException());
}

Form::Form(const Form &src) : _name(src._name), _signed(false), _signGradeRequired(src._signGradeRequired), _execGradeRequired(src._execGradeRequired)
{
	*this = src;
}

Form::~Form()
{
}

Form	&Form::operator=(const Form &src)
{
	if (this != &src)
		_signed = src.isSigned();	
	return (*this);	
}

const string	Form::getName() const
{
	return (this->_name);
}

int	Form::getSignGR() const
{
	return (this->_signGradeRequired);
}

int	Form::getExecGR() const
{
	return (this->_execGradeRequired);
}

bool	Form::isSigned() const
{
	return (this->_signed);
}

void	Form::beSigned(const Bureaucrat &b)
{
	if (b.getGrade() > this->_signGradeRequired)
		throw (GradeTooLowException());
	else
		this->_signed = true;
}

const char	*Form::GradeTooHighException::what() const throw()
{
	return ("Grade is too high");
}

const char	*Form::GradeTooLowException::what() const throw()
{
	return ("Grade is too low");
}

std::ostream	&operator<<(std::ostream &out, Form const &src)
{
	if (src.isSigned())
		out << src.getName() << ", signed, grade required to execute : " << src.getExecGR() << endl;
	else
		out << src.getName() << ", grade required to sign : " << src.getSignGR() << ", grade required to execute : " << src.getExecGR() << endl;
	return (out);
}