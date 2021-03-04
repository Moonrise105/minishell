#include "minishell_new.h"

//int status = 0;



int     manager(t_list *commands)
{
    t_command	*command;
	t_list		*tmp;
    int code;

    while (commands)
    {
        command = commands->content;
        if (command->jmp_type == 0 || command->jmp_type == -1)
        {
            code = semicolon_handler(command);
        }
        else if (command->jmp_type == 1)
        {
			tmp = find_left_redir(commands);
			if (tmp)
				commands = left_redir_handler(tmp);
			else
				commands = pipe_handler(commands);
        }
        else if (command->jmp_type == 2 || command->jmp_type == 3)
        {
			commands = right_redir_handler(commands, NULL, 0);
        }
        else if (command->jmp_type == 4)
        {
			commands = left_redir_handler(commands);
        }
        commands = commands->next;

    }
    return (code);
}