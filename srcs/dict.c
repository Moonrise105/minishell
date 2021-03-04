#include "minishell.h"

void	pair_free(t_pair *pair)
{
	if (pair)
	{
		free(pair->key);
		free(pair->value);
		free(pair);
	}
}

void	dict_free(t_list **dict)
{
	ft_lstclear(dict, pair_free);
}
void	free_array_char(char **array)
{
	int i;
	
	
	i = 0;
	while (array[i])
	{
		free(array[i]);
		++i;
	}

	
}

t_pair	*dict_get(t_list *dict, char *key)
{
	t_pair *pair;

	pair = dict->content;
	while (ft_strcmp(pair->key, key) != 0)
	{
		dict = dict->next;
		if (dict)
			pair = dict->content;
		else
			return (NULL);
	}
	return (pair);
}

char	**split_f(char *s, char c)
{
	int i;
	char **p;

	i = 0;
	p = (char**)malloc(sizeof(char*) * (2 + 1));
	p[2] = NULL;
	while (s[i] && s[i] != c)
	{
		++i;
	}
	p[0] = (char*)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] && s[i] != c)
	{
		p[0][i] = s[i];
		++i;
	}
	p[0][i] = '\0';
	if (i == ft_strlen(s))
		p[1] = NULL;
	else
		p[1] = ft_strdup(&s[++i]);
	return (p);
}

t_pair	*pair_get(char *s, char key)
{
	t_pair	*pair;
	char	**pair_split;

	pair = (t_pair*)malloc(sizeof(t_pair));
	if (s)
	{
		pair_split = split_f(s, key);
		pair->key = pair_split[0];
		pair->value = pair_split[1];
		free(pair_split);
	}
	
	return (pair);
}

char	**dict_to_arr(t_list *dict)
{
	int i;
	t_pair *pair;
	char **res;
	char *tmp;

	res = (char**)malloc(sizeof(char*) * (ft_lstsize(dict) + 1));
	i = 0;
	while (dict)
	{
		pair = dict->content;
		tmp = ft_strjoin(pair->key, "=");
		res[i] = ft_strjoin(tmp, pair->value);
		free(tmp);
		dict = dict->next;
		++i;
	}
	res[i] = NULL;
	return (res);
}

t_list	*dict_create(char **array, char key)
{
	t_list *dict;
	int i;
	t_pair *pair;

	i = 0;
	if (array[i])
	{
		pair = pair_get(array[i], key);
		dict = ft_lstnew(pair);
	}
	++i;
	while (array[i])
	{
		ft_lstadd_back(&dict, ft_lstnew(pair_get(array[i], key)));
		++i;
	}
	//free_array_char(array);
	return (dict);
}



void	dict_insert(t_list *first, t_list *second, t_list *new)
{
	t_list *next_tmp;

	if (first && second && new)
	{
		next_tmp = first->next;
		first->next = new;
		new->next = next_tmp;
	}
}

void	dict_add_sort(t_list *dict, t_pair *pair) //not tested
{
	t_pair *pair_tmp;
	t_list *prev;

	if (dict)
	{
		pair_tmp = dict->content;
		prev = dict;
		while (dict)
		{
			dict = dict->next;
			pair_tmp = dict->content;
			if (ft_strcmp(pair->key, pair_tmp->key) > 0)
			{
				dict_insert(prev, dict, ft_lstnew(pair));
				return ;
			}
			prev = dict;
			pair_tmp = dict->content;
		}
		
	}
	
}



t_list	*dict_del(t_list *dict, char *key)
{
	t_pair *pair;
	t_list *prev;
	t_list *first;
	
	first = dict;
	if (dict && key)
	{
		pair = dict->content;
		if (ft_strcmp(pair->key, key) == 0)
		{
			pair_free(pair);
			free(first);
			return (dict->next);
		}
			
		prev = dict;
		while (dict)
		{
			dict = dict->next;
			if (!dict)
				return (first);
			pair = dict->content;
			if (ft_strcmp(pair->key, key) == 0)
			{
				prev->next = dict->next;
				pair_free(pair);
				free(dict);
				return (first);
			}
			prev = dict;
		}
	}
	return (first);
}



void	dict_set(t_list *dict, char *key, char *value)
{
	t_pair *pair;

	if ((pair = dict_get(dict, key)))
	{
		free(pair->key);
		free(pair->value);
		pair->key = key;
		pair->value = value;
	}
		
	else
	{
		pair = (t_pair*)malloc(sizeof(t_pair));
		pair->key = key;
		pair->value = value;
		ft_lstadd_back(&dict, ft_lstnew(pair));
	}
}



