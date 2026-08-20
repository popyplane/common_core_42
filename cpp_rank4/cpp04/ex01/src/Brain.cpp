/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:37:02 by codespace         #+#    #+#             */
/*   Updated: 2024/03/06 22:24:37 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Brain.hpp"

Brain::Brain()
{
	cout << PURPLE
		<< "Brain constructor"
		<< ENDCOLOR << endl;
    _setIdeas();
}

Brain::Brain( Brain const &rhs )
{
	cout << PURPLE
		<< "Brain copy constructor"
		<< ENDCOLOR << endl;
	for(int i = 0; i < 100; ++i)
		_ideas[i] = rhs._ideas[i];
}

Brain::~Brain()
{
	cout << PURPLE
		<< "Brain destructor"
		<< ENDCOLOR << endl;
}

Brain     &Brain::operator=( Brain const &rhs )
{
    if (this != &rhs)
    {
        for (int i = 0; i < 100; i++)
            _ideas[i] = rhs._ideas[i];
    }
	return (*this);
}

void    Brain::_setIdeas()
{
    for (int i = 0; i < 100; i++)
        _ideas[i] = "No idea ...";
}