#include "../inc/ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{}

ScalarConverter::ScalarConverter(const ScalarConverter &src)
{
	*this = src;
}

ScalarConverter::~ScalarConverter()
{}

ScalarConverter	&ScalarConverter::operator=(const ScalarConverter &src)
{
	(void)src;
	return (*this);
}

void	ScalarConverter::toChar(const char *input_char, double input_double)
{
	cout << "char : ";
	if (!isdigit(input_char[0]) && !input_char[1])
		cout << "'" << input_char[0] << "'";
	else if (input_double < 0 || input_double >= CHAR_MAX)
		cout << "impossible";
	else if (input_double >= 0 && input_double <= 32)
		cout << "Non displayable";
	else
		cout << "'" << static_cast<char>(input_double) << "'";
	cout << endl;
}

void	ScalarConverter::toInt(const char *input_char, double input_double)
{
	cout << "int : ";
	if (!isdigit(input_char[0]) && !input_char[1])
		cout << static_cast<int>(input_char[0]);
	else if (input_double < INT_MIN || input_double > INT_MAX)
		cout << "Impossible";
	else
		cout << static_cast<int>(input_double);
	cout << endl;
}

void	ScalarConverter::toFloat(const char *input_char, double input_double)
{
	int	decimalDigits = calculateFormat(input_char);

	cout << std::fixed << std::setprecision(decimalDigits) << "float : ";
	if (!isdigit(input_char[0]) && !input_char[1])
		cout << static_cast<float>(input_char[0]);
	else if (input_double < -FLT_MAX || input_double > FLT_MAX)
		cout << "Impossible";
	else
		cout << static_cast<float>(input_double) << "f";
	cout << endl;
}

void	ScalarConverter::toDouble(const char *input_char, double input_double)
{
	int	decimalDigits = calculateFormat(input_char);

	cout << std::fixed << std::setprecision(decimalDigits) << "double : ";
	if (!isdigit(input_char[0]) && !input_char[1])
		cout << static_cast<double>(input_char[0]);
	else if (input_double < -DBL_MAX || input_double > DBL_MAX)
		cout << "Impossible";
	else
		cout << static_cast<double>(input_double);
	cout << endl;
}

bool	ScalarConverter::isLimit(const string input)
{
	return (input == "+inf" || input == "-inf" || input == "nan" || input == "+inff" || input == "-inff" || input == "nanf");
}

int	ScalarConverter::calculateFormat(const char *input_char)
{
	string	str(input_char);
	int		isFloat = 0;
	size_t	lastNonZero;
	size_t	dotPos = str.find('.');

	if (dotPos == std::string::npos)
		return (1);
	
	if (str.at(str.length() - 1) == 'f')
		isFloat++;

	lastNonZero = str.find_last_not_of('0');
	if (lastNonZero - dotPos > 0)
		return (lastNonZero - dotPos - isFloat);
	return (1);
}

void	ScalarConverter::castLimit(const string input)
{
	cout << "char : Impossible" << endl << "int : Impossible" << endl;
	if (input == "nan" || input == "nanf")
		cout << "float : nanf" << endl << "double : nan" << endl;
	else if (input == "+inf" || input == "+inff")
		cout << "float : +inff" << endl << "double : +inf" << endl;
	else if (input == "-inff" || input == "-inf")
		cout << "float : -inff" << endl << "double : -inf" << endl;
}

void	ScalarConverter::convert(const string literal)
{
	const char	*input_char = literal.c_str();
	char *endPtr = 0;
	double	input_double = std::strtod(input_char, &endPtr);

	if (isLimit(literal))
		castLimit(literal);
	else if (*endPtr == '\0' || (*endPtr == 'f' && *(endPtr + 1) == '\0'))
	{
		toChar(input_char, input_double);
		toInt(input_char, input_double);
		toFloat(input_char, input_double);
		toDouble(input_char, input_double);
	}
	else
	{
		cout << literal << " isn't a literal number." << endl;
	}
}
