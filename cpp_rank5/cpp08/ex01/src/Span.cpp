#include "../inc/Span.hpp"

const unsigned int  Span::kMaxSpan = std::numeric_limits<unsigned int>::max();

Span::Span()
	: _size(0), _minSpan(kMaxSpan), _data()
{}

Span::Span(unsigned int n)
	: _size(n), _minSpan(kMaxSpan), _data()
{}

Span::Span(const Span &src)
	: _size(src._size), _minSpan(src._minSpan), _data(src._data)
{}

Span::~Span()
{}

Span    &Span::operator=(Span &src)
{
	if (this != &src)
	{
		_size = src._size;
		_data = src._data;
		_minSpan = src._minSpan;
	}
	return (*this);
}

void    Span::addNumber(int n)
{
	if (_data.size() >= _size)
		throw (std::out_of_range("The capacity is full, unable to add a new number"));
	
	std::multiset<int>::iterator    it = _data.insert(n);
	evaluateMinSpan(it, n);
}

unsigned int	Span::shortestSpan()
{
	if (_data.size() <= 2)
		throw (std::logic_error("Not enough numbers to calculate the shortest span"));
	return (_minSpan);
}

unsigned int	Span::longestSpan()
{
	if (_data.size() <= 2)
		throw (std::logic_error("Not enough numbers to calculate the longest span"));
	return (calculateSpan(*(_data.begin()), *(std::prev(_data.end()))));
}

void    Span::evaluateMinSpan(std::multiset<int>::iterator it, int n)
{
	if (_minSpan == 0)
		return;
	if (it != _data.begin())
		evaluateSpan(*(std::prev(it)), n);
	if (it != std::prev(_data.end()))
		evaluateSpan(*(std::next(it)), n);
}

void    Span::evaluateSpan(int num1, int num2)
{
	unsigned int span = calculateSpan(num1, num2);
	
	if (span < _minSpan)
		_minSpan = span;
}

unsigned int    Span::calculateSpan(int num1, int num2)
{
	long	diff = static_cast<long>(num1) - static_cast<long>(num2);
	
	diff = (diff >= 0) ? diff : -diff;
	return (static_cast<unsigned int>(diff));
}