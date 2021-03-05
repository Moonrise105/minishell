#include "minishell_new.h"



t_list		*env_get(t_list **nw) 
{
	static t_list *env;

	if (nw)
	{
		env = *nw;
	}
		
	return (env);
}

int		env_f(char **av, int dec)
{
	int i;
	char **env;

	if (av)
	{
		env = dict_to_arr(env_get(NULL));
		i = 0;
		while (env[i])
		{
			if (dec)
				ft_putstr("declare -x ");
			ft_putstr(env[i]);
			ft_putstr("\n");
			++i;
		}
		free_array_char(env);
		return (0);
	}
	return (-1);
	
}

int		export(char **av)
{
	t_list *dict;
	int i;
	char **pair;
	char **env;

	t_pair *tmp;
	char **nw;
	char *tmp_s;
	char *tmp_s1;

	if (!av[0])
	{
		env_f(av, 1);
		return (0);
	}
	dict = env_get(NULL);
	i = 0;
	//dict = dict_create(env, '=');
	while (av[i])
	{
		//printf("|%s|\n", av[i]);
		pair = split_f(av[i], '=');
		tmp_s = ft_strtrim(pair[1], " ");
		free(pair[1]);
		pair[1] = tmp_s;
		if (pair[1])
		{
			dict_set(dict, pair[0], pair[1]);
			free(pair[0]);
			free(pair[1]);
		}
			
			
		else
		{
			free(pair[0]);	
		}
		free(pair);
		++i;
		
	}
	return (0);
}

int		unset(char **av)
{
	t_list *dict;
	int i;
	char **env;

	i = 0;
	dict = env_get(NULL);
	while (av[i])
	{
		dict = dict_del(dict, av[i]);
		++i;
	}
	return (0);
}