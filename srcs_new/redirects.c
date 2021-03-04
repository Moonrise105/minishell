#include "minishell_new.h"

t_list *find_left_redir(t_list *commands)
{
	t_command *command;
	
	command = commands->content;
	while (commands)
	{
		if (command->jmp_type != 1)
			break;
		commands = commands->next;
		if (commands)
			command = commands->content;
	}
	if (commands)
	{
		if (command->jmp_type != 4)
			return (NULL);
	}
	return (commands);
}