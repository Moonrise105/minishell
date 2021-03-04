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
