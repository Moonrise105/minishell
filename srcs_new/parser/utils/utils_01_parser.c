/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:03:51 by olydden           #+#    #+#             */
/*   Updated: 2021/03/06 16:28:04 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			letter_add(t_list **letters, char *c)
{
	if (*letters)
		ft_lstadd_back(letters, ft_lstnew(ft_strndup(c, 1)));
	else
		*letters = ft_lstnew(ft_strndup(c, 1));
}

char			*word_get(t_list **letters)
{
	char	*arg;
	int		i;
	int		size;
	t_list	*tmp_letters;

	i = 0;
	tmp_letters = *letters;
	size = ft_lstsize(*letters);
	arg = (char *)malloc(sizeof(char) * size + 1);
	arg[size] = '\0';
	while (tmp_letters)
	{
		arg[i] = *(char *)(tmp_letters)->content;
		i++;
		tmp_letters = tmp_letters->next;
	}
	return (arg);
}
