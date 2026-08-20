/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:36:39 by bvieilhe          #+#    #+#             */
/*   Updated: 2024/03/01 13:58:01 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define  CLAPTRAP_HPP

# include <iostream>

using   std::cout;
using   std::endl;
using   std::string;

# define ENDCOLOR "\033[0m"
# define YELLOW "\033[033m"
# define BLUE "\033[034m"
# define GREEN "\033[032m"
# define RED "\033[031m"
# define PURPLE "\033[035m"
# define CYAN "\033[036m"

class   ClapTrap
{
	private:
		string  _name;
		int     _hitPoints;
		int     _energyPoints;
		int     _attackDamage;

	public:
		ClapTrap( string name = "Bob");
		ClapTrap( ClapTrap const & src );
		~ClapTrap();

		ClapTrap &      operator=( ClapTrap const & rhs );

		void		attack( const string& target );
		void		takeDamage( unsigned int amount );
		void		beRepaired( unsigned int amount );
};

#endif