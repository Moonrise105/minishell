/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 18:16:28 by olydden           #+#    #+#             */
/*   Updated: 2021/03/06 16:27:50 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lst_to_str(t_list *lst)
{
	int		len;
	char	*str;
	char	*start;

	if (lst)
	{
		len = ft_lstsize(lst);
		str = (char*)malloc(sizeof(char) * (len + 1));
		start = str;
		while (lst)
		{
			*str = *((char*)(lst->content));
			str++;
			lst = lst->next;
		}
		*str = '\0';
	}
	else
		start = ft_strdup("\0");
	return (start);
}

void	str_sub(t_list **lst, char *s, int *i)
{
	int		start;
	char	*val;
	t_list	*dict;
	t_pair	*pair;
	char	*number;

	++(*i);
	start = *i;
	while (s[*i] && s[*i] != '$' && s[*i] != '\\' && s[*i] != '\''
			&& s[*i] != '\"')
		++(*i);
	--(*i);
	if (*i == start - 1)
		sym_add(lst, &s[*i]);
	else
	{
		val = ft_substr(s, start, *i - start + 1);
		sign_question(&number, val, lst);
		dict = env_get(NULL);
		pair = dict_get(dict, val);
		free(val);
		add_str_or_sym(lst, &pair);
	}
}

void	parse(t_arg_parser *ap, char *s)
{
	if (s[ap->i] == '\'' && !ap->q2 && !ap->ec)
		set_quoter_flags(&ap->q1);
	else if (s[ap->i] == '\"' && !ap->q1 && !ap->ec)
		set_quoter_flags(&ap->q2);
	else if (s[ap->i] == '\\' && !ap->ec)
		ap->ec = 1;
	else if (s[ap->i] == '$' && !ap->q1 && !ap->ec)
		str_sub(&ap->new_str, s, &ap->i);
	else
	{
		sym_add(&ap->new_str, &s[ap->i]);
		if (ap->ec)
			ap->ec = 0;
	}
}

char	*parse_arg(char *s)
{
	t_arg_parser	ap;
	char			*str;

	ap.new_str = NULL;
	ap.i = 0;
	ap.q1 = 0;
	ap.q2 = 0;
	ap.ec = 0;
	if (!(*s))
		return (NULL);
	if (!ft_strcmp(s, "~"))
	{
		str_sub(&ap.new_str, "$HOME", &ap.i);
		ap.i = 1;
	}
	while (s[ap.i])
	{
		parse(&ap, s);
		++(ap.i);
	}
	str = lst_to_str(ap.new_str);
	lst_free(&ap.new_str);
	return (str);
}

void	parse_args(t_list *args)
{
	char *tmp;

	while (args)
	{
		tmp = parse_arg(args->content);
		free(args->content);
		if (tmp)
			args->content = tmp;
		else
			args->content = ft_strdup("");
		args = args->next;
	}
}
