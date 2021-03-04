#include "minishell_new.h"

void	prefix_command(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
}
