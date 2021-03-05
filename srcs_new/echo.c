#include "minishell_new.h"

int		echo(char **av)
{
	int		n;
	int		i;
	int		j;
	int		flag;
	i = 0;
	n = 1;
	flag = 1;
	if (av)
	{
		while (av[i] && !ft_strncmp(av[i], "-n", 2))
		{
			j = 2;
			while (av[i][j])
			{
				if (av[i][j] != 'n')
				{
					flag = 0;
					break;
				}
				++j;
			}
			if (!flag)
				break;
			n = 0;
			++i;
		}
		while (av[i])
		{
			ft_putstr(av[i]);
			if (*(av[i]) && av[i + 1])
			{
				ft_putstr(" ");
			}
			++i;
		}
		if (n)
			ft_putstr("\n");
		g_status = 0;
	}
	
	return (0);
}