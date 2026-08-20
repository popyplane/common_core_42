/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:24:03 by mafoulon          #+#    #+#             */
/*   Updated: 2023/12/20 17:18:18 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

// function to iterate throught a given string until
// we meet a space again (iterate throught a word and increment size_t *i)
// allows to get the lenght of a given "word" to know how much memory we need
// to allocate

static void	skip_word(char const *s, size_t *i)
{
	char	q;

	while (s[*i] && s[*i] != ' ')
	{
		if (s[*i] != '\'' && s[*i] != '"')
			(*i)++;
		else
		{
			q = s[(*i)++];
			while (s[(*i)] != q)
				(*i)++;
			(*i)++;
		}
	}
}

// function to copy the string values between two s-quotes into the precedently
// created double array **strs

static void	words_filler(const char *s, char **strs, size_t *i, size_t j)
{
	size_t	k;
	char	q;

	k = 0;
	while (s[(*i)] && s[(*i)] != ' ')
	{
		if (s[(*i)] != '\'' && s[(*i)] != '"')
			strs[j][k++] = s[(*i)++];
		else
		{
			q = s[(*i)++];
			strs[j][k++] = q;
			while (s[(*i)] != q)
				strs[j][k++] = s[(*i)++];
			strs[j][k++] = s[(*i)++];
		}
	}
}

// fills each "words" into the precedently created double array **strs
// and returns it

static char	**filler(char const *s, char **strs)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && strs[j])
	{
		if (s[i] != ' ')
		{
			words_filler(s, strs, &i, j);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (strs);
}

// skips spaces and allocates the according memory (word length + 1) to strs[j]
// until it meets the end of the *s string (args)
// returns **strs

static char	**allocater(char const *s, char **strs)
{
	size_t	start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			start = i;
			skip_word(s, &i);
			strs[j] = ft_calloc(i - start + 1, sizeof(char));
			if (!strs[j])
				return (NULL);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (strs);
}

// counts the number of "words/arguments" and allocates the value to the 
// **strs array it then returns to the **expanded array created in the
// function that calls expander_split the filled **strs array
// with each "word/argument"

char	**expander_split(char const *s)
{
	size_t	count;
	char	**strs;
	char	**tofree;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && ++count)
			skip_word(s, &i);
		while (s[i] && s[i] == ' ')
			i++;
	}
	strs = ft_calloc(count + 1, sizeof(char *));
	tofree = strs;
	strs = allocater(s, strs);
	if (!strs || ! count)
		return (free_char2(tofree), NULL);
	return (filler(s, strs));
}
