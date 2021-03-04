/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.21.ru>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 19:33:26 by moonrise          #+#    #+#             */
/*   Updated: 2020/05/30 13:45:39 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_delim(char c, char d)
{
	return (c == d);
}

static int		count_words(const char *str, char d)
{
	int count;

	count = 0;
	while (*str)
	{
		while (*str && is_delim(*str, d))
			str++;
		if (*str && !is_delim(*str, d))
		{
			count++;
			while (*str && !is_delim(*str, d))
				str++;
		}
	}
	return (count);
}

static char		*malloc_word(const char *str, char d)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && !is_delim(str[i], d))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && !is_delim(str[i], d))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char			**ft_split(char const *str, char c)
{
	char	**arr;
	int		i;

	if (!str)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (*str && is_delim(*str, c))
			str++;
		if (*str && !is_delim(*str, c))
		{
			arr[i] = malloc_word(str, c);
			i++;
			while (*str && !is_delim(*str, c))
				str++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
