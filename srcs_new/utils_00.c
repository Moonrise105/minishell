#include "minishell_new.h"

t_list *skip_jmps(t_list *commands, char *jmps)
{
	t_command	*command;

	command = commands->content;
	while (commands && ft_strchr(jmps, command->jmp_type + '0'))
	{
		commands = commands->next;
		command = commands->content;
	}
	return (commands);
}

int		is_numeric(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (0);
		++i;
	}
	return (1);
}

int		my_exit(char **args)
{
	int i;
	int code;
	char *c;

	i = 0;

	if (args)
	{
		while (args[i]) 
		{
			if (i > 0)
			{
				ft_putstr("exit\n");
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				return (127);
			}

			if (!is_numeric(args[i]))
			{
				ft_putstr("exit\n");
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(args[i], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
			}
			++i;
		}
		ft_putstr("exit\n");
		code = (args[0]) ? ft_atoi_orig(args[0]) : 0;
		exit(code);

	}
	ft_putstr("exit\n");
	exit(0);
	return (0);
}
