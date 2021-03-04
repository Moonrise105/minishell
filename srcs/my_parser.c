#include "minishell.h"

int		parser_check(t_list *commands)
{
	t_command	*command;
	char		*errors;
	int prev;
	char *c;

	errors = "1234";
	prev = 8;
	while (commands)
	{
		command = commands->content;
		if ((command->jmp_type == 0 || command->jmp_type == 1 || command->jmp_type == 2) && !command->args)
		{
			c = (command->jmp_type == 0 ? (prev == 0 ? ";;'\n" : ";'\n") : (command->jmp_type == 1 ? (prev == 1 ? "||'\n" : "|'\n") : ">'\n"));
			ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
			ft_putstr_fd(c, 2);
			return (-1);
		}
		if ((ft_strchr(errors, command->jmp_type + '0') && !commands->next) || (ft_strchr(errors, prev + '0') && !command->args))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			return (-1);
		}
		else
		{
			prev = command->jmp_type;
		}
		//printf("%d\n", prev+'0');
		commands = commands->next;
	}
	return (0);
}

int		jmp_get(char c)
{
	char *jmps;
	int i;

	i = 0;
	jmps = ";|>]<";
	while (jmps[i])
	{
		if (c == jmps[i])
			return (i);
		++i;
	}
	return (-1);
}
int		is_redirect(char c)
{
	char *redirs;

	redirs = ";|><";
	if (ft_strchr(redirs, c))
		return (1);
	return (0);
}

int		is_quoter(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	letter_add(t_list **letters, char *c)
{
	if (*letters)
	{
		ft_lstadd_back(letters, ft_lstnew(ft_strndup(c, 1)));
	}
	else
	{
		*letters = ft_lstnew(ft_strndup(c, 1));
	}
}

char	*word_get(t_list **letters)
{
	char *arg;
	int i;
	int size;
	t_list *tmp_letters;

	i = 0;
	tmp_letters = *letters;
	size = ft_lstsize(*letters);
	arg = (char *)malloc(sizeof(char) * size + 1);
	arg[size] = '\0';
	while (tmp_letters)
	{
		arg[i] = *(char *)(tmp_letters)->content;
		//printf("%c\n", arg[i]);
		i++;
		tmp_letters = tmp_letters->next;
	}
	return (arg);
}

void	args_add(t_list **args, char *arg)
{
	if (*args)
	{
		ft_lstadd_back(args, ft_lstnew(arg));
	}
	else
	{
		*args = ft_lstnew(arg);
	}
}

void	commands_add(t_list **commands, t_command *command)
{
	if (*commands)
	{
		ft_lstadd_back(commands, ft_lstnew(command));
	}
	else
	{
		*commands = ft_lstnew(command);
	}
}


void	lst_free(t_list **lst)
{

	if (lst && *lst)
	{
		ft_lstclear(lst, free);
	}
}

void	command_free(t_command **command)
{
	if (command && *command)
	{
		lst_free(&((*command)->args));
		free(*command);
		*command = NULL;
	}
}

void	commands_free(t_list **commands)
{
	t_list *tmp;
	t_list *first;
	if (commands && *commands)
	{
		first = *commands;
		while (first)
		{
			tmp = first->next;
			command_free((t_command **)(&(first->content)));
			free(first);
			first = tmp;
		}
		//free(*commands);
		*commands = NULL;
	}
}

t_command	*command_create(t_list *args, int jump)
{
	t_command *command;
	command = (t_command *)malloc(sizeof(t_command));
	//printf("%p\n", args);
	command->args = args;
	command->jmp_type = jump;
	return (command);
}

void	print(void *s) 
{
	//write(1, s, 1);
	//printf("%s", s);
	printf("%s\n", s);
}

void	print_lst(t_list *lst)
{
	ft_lstiter(lst, print);
}

void	print_command(t_command *command)
{
	printf("jmp = %d\n", command->jmp_type);
	print_lst(command->args);
	//ft_lstiter(command->args, print_lst);
}

void	print_commands(t_list *commands)
{
	ft_lstiter(commands, print_command);

}

void	parser_free(t_parser *p)
{
	// if (p->first_arg)
	// free(p->first_arg);
	//free(p->args);
	free(p->commands);
	free(p->letters);
	free(p);
}
void	parser_null(t_parser *p)
{
	p->first_arg = NULL;
	p->append_redir = 0;
	p->backslash = 0;
	p->args = NULL;
	p->commands = NULL;
	p->letters = NULL;
	p->q1 = 0;
	p->q2 = 0;
}


int		parser(t_parser *p, char input)
{

	if (p->append_redir && input != '>' && !p->backslash)
	{
		commands_add(&p->commands, command_create(p->args, 2));
		p->args = NULL;
		p->append_redir = 0;
	}

	if (is_redirect(input) && !p->backslash)
	{
		if (!p->q1 && !p->q2)
		{
			if (p->letters)
			{
				if (p->first_arg && p->args)
				{
					args_add(&p->first_arg, word_get(&p->letters));
					lst_free(&p->letters);
				}
				else
				{
					args_add(&p->args, word_get(&p->letters));
					lst_free(&p->letters);
				}
			}
			if (input == '>')
			{
				if (!p->first_arg)
					p->first_arg = p->args;
				if (p->append_redir)
				{
					commands_add(&p->commands, command_create(p->args, 3));
					p->args = NULL;
					p->append_redir = 0;
				}
				else
				{
					p->append_redir = 1;
				}
			}
			else
			{
				commands_add(&p->commands, command_create(p->args, jmp_get(input)));
				p->args = NULL;
				p->first_arg = NULL;
			}
		}
		else
		{
			letter_add(&p->letters, &input);
		}
		
		
		//
	}

	else if (input == '\n')
	{
		if (p->letters)
		{
			if (p->first_arg && p->args)
			{
				args_add(&p->first_arg, word_get(&p->letters));
				lst_free(&p->letters);
			}
			else
			{
				args_add(&p->args, word_get(&p->letters));
				lst_free(&p->letters);
			}
		}
		if (p->args)
			commands_add(&(p->commands), command_create(p->args, -1));
		//
		return (0);
	}

	else if (is_quoter(input))
	{
		// ft_printf("kek");
		if (input == '\'')
		{
			if (p->q1)
			{
				p->q1 = 0;
			}
			else
			{
				p->q1 = 1;
			}
		}
		else
		{
			if (p->q2)
			{
				p->q2 = 0;
			}
			else
			{
				p->q2 = 1;
			}
		}
		letter_add(&p->letters, &input);
	}

	else if ((input == ' ' || input == '\t') && !p->backslash)
	{
		//
		if (p->q1 || p->q2)
		{
			letter_add(&p->letters, &input);
		}
		else if (p->letters)
		{
			if (p->first_arg && p->args)
			{
				args_add(&p->first_arg, word_get(&p->letters));
				lst_free(&p->letters);
			}
			else
			{
				args_add(&p->args, word_get(&p->letters));
				lst_free(&p->letters);
			}
			
		}
		else; //not first space
	}
	else
	{
		p->backslash = 0;
		letter_add(&p->letters, &input);
		if (input == 92) // input == '\' 
		{
			// ft_printf("bla");
			p->backslash = 1;
		}
		//
	}
	return (1);
}

void	shell_newline()
{
	ft_putstr("minishell% ");
}

int sig;
int inp = 0;

void	signal_interrupt(int signal)
{
	ft_putstr("\b\b  \b\b");
	ft_putstr("\n");
	status = 1;
	shell_newline();
	//write(0, "\n", 1);
	//write(1, )
	//close(1);
}

void	signal_quit(int signal)
{
	ft_putstr("\b\b  \b\b");
}

void	eof_ign(void)
{
	ft_putstr("  \b\b");
}




int		main(int ac, char **av, char **en)
{
	char input;
	int read_bytes;
	t_parser *p;
	int code;



	// if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	// {
	// 	int i = 0;
	// 	env_get(en);
	// 	parser_null(p);
	// 	input = '\0';
	// 	sig = 1;
	// 	code = 0;
	// 	//printf("%s\n", av[2]);
	// 	//shell_newline();
	// 	while (1) //>>
	// 	{
	// 		// signal(SIGINT, signal_interrupt);
	// 		// signal(SIGQUIT, signal_quit);
	// 		input = av[2][i];
	// 		//read_bytes = read(0, &input, 1);
	// 		if (input == '\0')
	// 			input = '\n';
	// 		code = parser(&p, input);
	// 		if (read_bytes && !code)
	// 			break;
	// 		else if (!read_bytes && !input)
	// 		{
	// 			my_exit(NULL);
	// 		}
	// 		else if (!read_bytes)
	// 			eof_ign();
	// 		++i;
	// 	}
	// 	if (parser_check(p.commands) >= 0)
	// 		manager(p.commands);
	// 	commands_free(&(p.commands));
	// 	return (status);
	// }
	//ft_launch_minishell(av[2]);

	p = (t_parser *)malloc(sizeof(t_parser));

	env_get(en);
	while (1)
	{
		parser_null(p);
		
		
		input = '\0';
		sig = 1;
		code = 0;
		shell_newline();
		
		while (1) //>>
		{
			signal(SIGINT, signal_interrupt);
			signal(SIGQUIT, signal_quit);
			read_bytes = read(0, &input, 1);
			code = parser(p, input);
			if (read_bytes && !code)
				break;
			else if (!read_bytes && !input)
			{
				
				my_exit(NULL, p);
			}
			else if (!read_bytes)
				eof_ign();
		}
		if (parser_check(p->commands) >= 0)
			manager(p);
		commands_free(&(p->commands));
		//parser_free(p);
		//free(p);
	}
	
}






// int main(void)
// {
// 	t_list *commands = NULL;
// 	t_list *args = NULL;
// 	t_command *command = NULL;
// 	t_list *letters = NULL;

// 	char *s = ft_strdup("hello world");`
// 	char *s1 = ft_strdup("sasha kek");

// 	int i = 0;
// 	while (s[i])
// 	{
// 		letter_add(&letters, &s[i]);
// 		++i;
// 	}
// 	args_add(&args, word_get(&letters));
	
// 	lst_free(&letters);
// 	command = malloc(sizeof(t_command));
// 	command->args = args;
// 	command->jmp_type = 2;
// 	commands_add(&commands, command);
// 	args = NULL;
	


// 	i = 0;
// 	while (s1[i])
// 	{
// 		letter_add(&letters, &s1[i]);
// 		++i;
// 	}
	
// 	args_add(&args, word_get(&letters));
// 	lst_free(&letters);
// 	command = malloc(sizeof(t_command));
// 	command->args = args;
// 	command->jmp_type = 3;
// 	commands_add(&commands, command);
// 	lst_free(&letters);


	// print_commands(commands);
// 	commands_free(&commands);
// 	commands = NULL;
// 	commands_add(&commands, command);
	// print_lst(args);
// 	//printf("%s\n", args->content);
// 	//commands_free(&commands);
// 	while (1)
// 	{
// 		//
// 	}
// 	return (0);
// }