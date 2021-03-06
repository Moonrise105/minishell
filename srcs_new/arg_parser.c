#include "minishell_new.h"

char	*lst_to_str(t_list *lst)
{
	int len;
	char *str;
	char *start;

	//printf("%s\n", lst->content);
	if (lst)
	{
		//printf("IN\n");
		len = ft_lstsize(lst);
		str = (char*)malloc(sizeof(char) * (len + 1));
		//printf("len = %d", len);
		start = str;
		while (lst)
		{
			*str = *((char*)(lst->content));
			//printf("%s\n", lst->content);
			str++;
			lst = lst->next;
		}
		*str = '\0';
	}
	else
		start = ft_strdup("\0");
	return (start);
	
}

void sym_add(t_list **lst, char *sym)
{
	char *tmp;

	tmp = ft_strdup(sym);
	if (*lst)
	{
		ft_lstadd_back(lst, ft_lstnew(tmp));
	}
	else
	{
		*lst = ft_lstnew(tmp);
	}
}

void	str_add(t_list **lst, char *s)
{
	
	while (*s)
	{
		sym_add(lst, s);
		s++;
	}
	//free(s);
}

void	str_sub(t_list **lst, char *s, int *i)
{
	int start;
	char *val;
	t_list *dict;
	char **env;
	t_pair *pair;
	char *number;

	++(*i);
	start = *i;
	while (s[*i] && s[*i] != '$' && s[*i] != '\\' && s[*i] != '\'' && s[*i] != '\"')
		++(*i);
	--(*i);
	//printf("start=%d, i=%d\n", start, *i);
	if (*i == start - 1)
	{
		//printf("IN\n");
		sym_add(lst, &s[*i]);
	}
	else
	{
		//printf("%d\n", *i);
		val = ft_substr(s, start, *i - start + 1);
		//printf("%s\n", val);
		if (!ft_strcmp(val, "?"))
		{
			number = ft_itoa(g_status);
			str_add(lst, number);
			free(number);
		}
			
		dict = env_get(NULL);
		//printf("%s\n", dict_get(dict, val)->value);
		pair = dict_get(dict, val);
		free(val);
		if (pair)
			str_add(lst, pair->value);
			
		else
			sym_add(lst, "");
		//dict_free(&dict);
	}
	
	//printf("%s\n", val);
}

char	*parse_arg(char *s)
{
	int i;
	t_list *new_str;
	int q1;
	int q2;
	int ec;
	char *str;

	new_str = NULL;
	i = 0;
	q1= 0;
	q2 = 0;
	//new_str = ft_lstnew()
	ec = 0;
	if (!(*s))
		return (NULL);
	if (!ft_strcmp(s, "~"))
	{
		str_sub(&new_str, "$HOME", &i);
		i = 1;
	}
	while (s[i])
	{
		//printf("%c\n", s[i]);
		if (s[i] == '\'' && !q2 && !ec)
		{
			if (q1)
			{
				q1 = 0;
			}
			else
			{
				q1 = 1;
			}
		}
		else if (s[i] == '\"' && !q1 && !ec)
		{
			if (q2)
			{
				q2 = 0;
			}
			else
			{
				q2 = 1;
			}
		}
		else if(s[i] == '\\' && !ec)
		{
			ec = 1;
		}
		else if (s[i] == '$' && !q1 && !ec)
		{
			str_sub(&new_str, s, &i);
		}
		else
		{
			//printf("IN\n");
			
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
	//printf("%s\n", args->content);
}