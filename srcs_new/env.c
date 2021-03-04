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

// int		env_f(char **av, int dec)
// {
// 	int i;
// 	char **env;

// 	env = env_get(NULL);
// 	i = 0;
// 	if (av)
// 	{
// 		// if (av[0])
// 		// {
// 		// 	//TODO error print
// 		// 	return (-1);
// 		// }
// 		while (env[i])
// 		{
// 			if (dec)
// 				ft_putstr("declare -x ");
// 			ft_putstr(env[i]);
// 			ft_putstr("\n");
// 			++i;
// 		}
// 		return (0);
// 	}
// 	return (-1);
	
// }

// int		export(char **av)
// {
// 	t_list *dict;
// 	int i;
// 	char **pair;
// 	char **env;

// 	t_pair *tmp;
// 	char **nw;
// 	char *tmp_s;
// 	char *tmp_s1;

// 	//printf("|%s|", av[0]);
// 	if (!av[0])
// 	{
// 		env_f(av, 1);
// 		return (0);
// 	}
// 	env = env_get(NULL);
// 	i = 0;
// 	dict = dict_create(env, '=');
// 	while (av[i])
// 	{
// 		//printf("|%s|\n", av[i]);
// 		pair = split_f(av[i], '=');
// 		tmp_s = ft_strtrim(pair[1], " ");
// 		free(pair[1]);
// 		pair[1] = tmp_s;
// 		if (pair[1])
// 		{
// 			dict_set(dict, pair[0], pair[1]);
// 		}
			
// 		else
// 		{
// 			//TODO print error
// 			free(pair[1]);
// 			free(pair[0]);
// 		}
// 		free(pair);
// 		++i;
		
// 	}
// 	nw = dict_to_arr(dict);
// 	// if (!env_init)
// 	// 	free_array_char(env_get(NULL));
// 	//free(env);
// 	env_get(nw);
// 	dict_free(&dict);
// 	return (0);
// }

// int		unset(char **av)
// {
// 	t_list *dict;
// 	int i;
// 	char **env;

// 	i = 0;
// 	env = env_get(NULL);
// 	dict = dict_create(env, '=');
// 	while (av[i])
// 	{
// 		//printf("%s\n", av[i]);
// 		dict = dict_del(dict, av[i]);
// 		++i;
// 	}
// 	env_get(dict_to_arr(dict));
// 	dict_free(&dict);
// 	return (0);
// }