#include "../inc/Bureaucrat.hpp"

AForm::AForm() : _name("default"), _signed(false), _signGradeRequired(150), _execGradeRequired(150)
{}

AForm::AForm(const string name, const int signGR, const int execGR) : _name(name), _signed(false), _signGradeRequired(signGR), _execGradeRequired(execGR)
{
	if (this->_signGradeRequired < 1 || this->_execGradeRequired < 1)
		throw (GradeTooHighException());
	if (this->_signGradeRequired > 150 || this->_execGradeRequired > 150)
		throw (GradeTooLowException());
}

AForm::AForm(const AForm &src) : _name(src._name), _signed(false), _signGradeRequired(src._signGradeRequired), _execGradeRequired(src._execGradeRequired)
{
	*this = src;
}

AForm::~AForm()
{}

AForm	&AForm::operator=(const AForm &src)
{
	if (this != &src)
		_signed = src.isSigned();	
	return (*this);	
}

const string	AForm::getName() const
{
	return (this->_name);
}

int	AForm::getSignGR() const
{
	return (this->_signGradeRequired);
}

int	AForm::getExecGR() const
{
	return (this->_execGradeRequired);
}

bool	AForm::isSigned() const
{
	return (this->_signed);
}

void	AForm::beSigned(const Bureaucrat &b)
{
	if (b.getGrade() > this->_signGradeRequired)
		throw (GradeTooLowException());
	this->_signed = true;
}

void	AForm::execute(const Bureaucrat &executor)
{
	if (!isSigned())
		throw (FormNotSignedException());
	if (executor.getGrade() > getExecGR())
		throw (GradeTooLowException());
	performExec();
	cout << executor.getName() << " executed " << getName() << endl;
}

const char	*AForm::GradeTooHighException::what() const throw()
{
	return ("(AForm) GradeTooHighException was called");
}

const char	*AForm::GradeTooLowException::what() const throw()
{
	return ("(AForm) GradeTooLowException was called");
}

const char	*AForm::FormNotSignedException::what() const throw()
{
	return ("(AForm) FormNotSigned was called");
}

std::ostream	&operator<<(std::ostream &out, AForm const &src)
{
	if (src.isSigned())
		out << src.getName() << ", signed, grade required to execute : " << src.getExecGR() << endl;
	else
		out << src.getName() << ", grade required to sign : " << src.getSignGR() << ", grade required to execute : " << src.getExecGR() << endl;
	return (out);
}