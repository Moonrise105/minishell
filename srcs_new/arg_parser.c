/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 18:16:28 by olydden           #+#    #+#             */
/*   Updated: 2021/03/05 18:46:41 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_new.h"

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

void	sym_add(t_list **lst, char *sym)
{
	char *tmp;

	tmp = ft_strdup(sym);
	if (*lst)
		ft_lstadd_back(lst, ft_lstnew(tmp));
	else
		*lst = ft_lstnew(tmp);
}

void	str_add(t_list **lst, char *s)
{
	while (*s)
	{
		sym_add(lst, s);
		s++;
	}
}

void	sign_question(char **number, char *val, t_list **lst)
{
	if (!ft_strcmp(val, "?"))
	{
		*number = ft_itoa(status);
		str_add(lst, *number);
		free(*number);
	}
}

void	add_str_or_sym(t_list **lst, t_pair **pair)
{
	if (*pair)
		str_add(lst, (*pair)->value);
	else
		sym_add(lst, "");
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

void	set_quoter_flags(int *q)
{
	if (*q)
		*q = 0;
	else
		*q = 1;
}

char	*parse_arg(char *s)
{
	int		i;
	t_list	*new_str;
	int		q1;
	int		q2;
	int		ec;
	char	*str;

	new_str = NULL;
	i = 0;
	q1 = 0;
	q2 = 0;
	ec = 0;
	if (!(*s))
		return (NULL);
	if (!ft_strcmp(s, "~"))
		str_sub(&new_str, "$HOME", &i);
	while (s[i])
	{
		if (s[i] == '\'' && !q2 && !ec)
			set_quoter_flags(&q1);
		else if (s[i] == '\"' && !q1 && !ec)
			set_quoter_flags(&q2);
		else if (s[i] == '\\' && !ec)
			ec = 1;
		else if (s[i] == '$' && !q1 && !ec)
			str_sub(&new_str, s, &i);
		else
		{
			sym_add(&new_str, &s[i]);
			if (ec)
				ec = 0;
		}
		++i;
	}
	str = lst_to_str(new_str);
	lst_free(&new_str);
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
