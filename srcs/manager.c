#include "minishell.h"
int status = 0;

void	sig_int(int signal)
{
	ft_putstr("\n");
	// /kill(0, SIGINT);

}
int		try_builtin(char *cmd, char **av, t_parser *p)
{
	if (!ft_strcmp(cmd, "echo"))
		return (echo(++av));
	else if (!ft_strcmp(cmd, "env"))
		return (env_f(++av, 0));
	else if (!ft_strcmp(cmd, "export"))
		return (export(++av));
	else if (!ft_strcmp(cmd, "unset"))
		return (unset(++av));
	else if (!ft_strcmp(cmd, "cd"))
		return (cd(++av));
	else if (!ft_strcmp(cmd, "pwd"))
		return (pwd(++av));
	else if (!ft_strcmp(cmd, "exit"))
		return (my_exit(++av, p));
	// else if (!ft_strncmp(cmd, ".", 1) || !ft_strncmp(cmd, "/", 1));
	// 	return (exec_command_path(cmd, av));
	return (-1);
}

int		is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") ||
		!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd"))
	{
		return (1);
	}
	return (0);
}

char	**args_create(t_list *args)
{
	int size;
	char **argv;
	int i;

	size = ft_lstsize(args);
	
	argv = (char**)malloc(sizeof(char*) * (size + 1));
	i = 0;
	while (args)
	{
		argv[i] = args->content;
		args = args->next;
		++i;
	}
	argv[i] = NULL;
	return (argv);
}

void	print_error(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	perror(s);
}

int		execute_command(t_list *args, t_parser *p)
{
	t_pair	*pair;
	char	**path;
	char	*cmd_path;
	t_list	*dict;
	char	*file_path;
	char	*tmp;
	char **env;
	char **av;
	char *command;
	char *c;
	int code;

	path = NULL;
	env = env_get(NULL);
	parse_args(args);
	command = args->content;
	av = args_create(args);
	
	//printf("%s\n", command);
	//printf("%s\n", av[0]);
	if ((code = try_builtin(command, av, p)) >= 0)
	{
		commands_free(&(p->commands));
		parser_free(p);
		env_get(&c);
		free(av);
		exit(code);
	}
	dict = dict_create(env, '=');
	pair = dict_get(dict, "PATH");
	if (pair)
		path = ft_split(pair->value, ':');
	dict_free(&dict);
	//path = NULL;
	//ft_putstr("IN2\n");
	//printf("command = %s\n", command);
	if (!ft_strcmp(command, ""))
		exit(0);
	else if (!ft_strcmp(command, ".") || !ft_strcmp(command, ".."))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
		commands_free(&(p->commands));
		parser_free(p);
		free(av);
		exit(127);
	}
	
	else if ((cmd_path = parse_dirs(path, command)) && *cmd_path)
	{
		//printf("1\n");
		//printf("%s\n", cmd_path);
		tmp = ft_strjoin(cmd_path, "/");
		file_path = ft_strjoin(tmp, command);
		free(tmp);
		//printf("%s\n", file_path);
		//ft_printf("%s\n", "ls: ");
		if (!execve(file_path, av, env))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": ", 2);
			perror("");
			free(av);
			commands_free(&(p->commands));
			parser_free(p);
		}
			
	}
	else if (!ft_strncmp(command, "./", 2) || !ft_strncmp(command, "/", 1) || !ft_strncmp(command, "../", 3))
	{
		//printf("2\n");
		if (execve(command, av, env) < 0)
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": ", 2);
			perror("");
			commands_free(&(p->commands));
			parser_free(p);
			free(av);
			exit(127);
	}
	else
	{
		//printf("3\n");
		//ft_printf("%")
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
		commands_free(&(p->commands));
		free(av);
		parser_free(p);
		exit(127);
	}	
	return (0);
	 
}

void	fork_exec(char *command, t_list *args, int fd_out, int fd_in, t_parser *p)
{
	int pid;

	pid = fork();
	if (pid > 0)
	{
		signal(SIGINT, sig_int);
		waitpid(-1, &status, 0);
		if (WIFSIGNALED(status))
			status = WTERMSIG(status) + 128;
		else
			status = WEXITSTATUS(status);
		//printf("status = %d\n", status);
		//wait (0);
		if (fd_in)
			close(fd_in);
		return ;
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (fd_out)
			dup2(fd_out, 1);
		if (fd_in)
			dup2(fd_in, 0);
		execute_command(args, p);
	}
	else
	{
		ft_putstr("error\n");
	}
}
int		*pipe_create(void)
{
	int *pipe_fd;

	pipe_fd = (int*)malloc(sizeof(int) * 2);
	pipe(pipe_fd);
	return (pipe_fd);
}



void	exec_write(t_command *command, int fd_out, int fd_in, t_parser *p)
{
	char **av;
	char *cmd;

	cmd = (command && command->args) ? command->args->content : "";
	//av = args_create(command->args);
	//dup2(fd, 1);
	fork_exec(cmd, command->args, fd_out, fd_in, p);
}

t_list	*redir_start(t_list *commands, int prev_jmp, int pipe_fd, t_parser *p)
{	
	t_command *command;
	t_command *prev_cmd;
	int fd;
	int first;
	t_command *first_cmd;
	t_list *prev;
	char *path;

	first = 1;
	while (commands)
	{
		command = commands->content;
		//printf("%s\n", first_cmd->args->content);
		//printf("redir %s\n", command->args->content);	
		if (first)
		{
			first_cmd = command;
			
			first = 0;
		}
		if (ft_strchr("23", prev_jmp + '0') && ft_strchr("23", command->jmp_type + '0'))
		{
			//command = commands->next->content
			path = command->args->content;
			fd = open(path, O_RDWR|O_CREAT|O_TRUNC, 0644);
			//free(path);
			close(fd);	
		}
		else if (!ft_strchr("23", command->jmp_type + '0'))
		{
			//printf("%s\n", command->args->content);
			if (command->jmp_type == 2)
			{
				path = command->args->content;
				fd = open(path, O_RDWR|O_CREAT|O_TRUNC, 0644);
				//free(path);
			}
				
			else
			{
				path = command->args->content;
				fd = open(path, O_RDWR|O_APPEND|O_CREAT, 0644);
				//free(path);
			}
				
			exec_write(first_cmd, fd, pipe_fd, p);
			close(fd);
			if (pipe_fd)
				close(pipe_fd);
			return (prev);
		}
		else
		{
			//printf("else\n");
		}
		
		prev_jmp = command->jmp_type;
		prev = commands;
		prev_cmd = command;
		commands = commands->next;

	}
	return (commands);
}

t_list 	*left_redir_start(t_list	*commands, t_parser *p)
{
	t_command	*command;
	t_command	*first;
	int			fd;
	t_list *prev;
	struct stat buf;
	int err;

	err = 0;
	command = commands->content;
	first = command;
	while (commands && command->jmp_type == 4)
	{
		prev = commands;
		commands = commands->next;
		if (commands)
		{
			command = commands->content;
			//printf("%s\n", command->args->content);
			if (lstat(command->args->content, &buf) < 0 && !err)
			{
				
				err = 1;
				print_error(command->args->content);
			}
		}
			
			//check file
	}
	//printf("%s\n", command->args->content);
	if (err)
		return (commands);
	fd = open(command->args->content, O_RDONLY);
		
	exec_write(first, 0, fd, p);
	return (commands);
}

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
void	pipe_last(t_list *commands, int *pipe_fd, t_parser *p)
{
	char **av;
	t_command *command;

	command = commands->content;
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	execute_command(command->args, p);
}

void	pipe_first(t_list *commands, int *pipe_fd, t_parser *p)
{
	char **av;
	t_command *command;
	command = commands->content;
	close(pipe_fd[1]);
	
	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status))
			status = WTERMSIG(status) + 128;
	else
		status = WEXITSTATUS(status);
	
	
	if (ft_strchr("23", command->jmp_type + '0'))
	{
		redir_start(commands, 1, pipe_fd[0], p);
		free(pipe_fd);
		exit(0);
	}

	else if (command->jmp_type == 4)
	{
		left_redir_start(commands, p);
		free(pipe_fd);
		exit(0);
	}

	else
	{
		dup2(pipe_fd[0], 0);
		free(pipe_fd);
		execute_command(command->args, p);
	}
	
}

void	pipe_in(t_command *command, int *pipe_fd, int *pipe_fd_new, t_parser *p)
{
	char **av;
	close(pipe_fd[0]);
	close(pipe_fd_new[1]);
	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	else
		status = WEXITSTATUS(status);
	dup2(pipe_fd_new[0], 0);
	dup2(pipe_fd[1], 1);
	execute_command(command->args, p);
}

int		my_pipe(t_list *commands, int pipe_count, int i, int *pipe_fd, t_parser *p)
{
	int pid;
	t_command *command;
	t_command *cmd_tmp;
	char **av;
	int *pipe_fd_new;

	
	if (i == 0)
	{
		pipe_fd_new = pipe_create();
		pid = fork();
		if (pid > 0)
		{
			
			pipe_first(ft_lstindex(commands, pipe_count), pipe_fd_new, p);
		}
		else
		{
			my_pipe(commands, pipe_count, ++i, pipe_fd_new, p);
		}
	}
	else if (i == pipe_count)
	{
		pipe_last(commands, pipe_fd, p);
	}
	else
	{
		pipe_fd_new = pipe_create();
		pid = fork();
		if (pid > 0)
		{
			pipe_in(ft_lstindex(commands, pipe_count - i)->content, pipe_fd, pipe_fd_new, p);
		}
		else
		{
			my_pipe(commands, pipe_count, ++i, pipe_fd_new, p);
		}
	}
	return (0);
}

t_list		*pipe_start(t_list *commands, t_parser *p)
{
	int pid;
	int *pipe_fd;
	t_command *command;
	int pipe_count;
	t_list *tmp;
	t_list *prev;

	pipe_count = 0;
	tmp = commands;
	command = tmp->content;
	while (tmp && command->jmp_type == 1)
	{
		++pipe_count;
		prev = tmp;
		tmp = tmp->next;
		command = tmp->content;
		
	}
	command = prev->content;
	pid = fork();
	if (pid > 0)
	{
		signal(SIGINT, sig_int);
		// printf("IN\n");
		//printf("prev %s\n", command->args->content);
		waitpid(-1, &status, 0);
		if (WIFSIGNALED(status))
			status = WTERMSIG(status) + 128;
		else
		{
			status = WEXITSTATUS(status);
			//printf("status = %d\n", status);
		}
			
		//printf("%s\n", command->args->content);
		prev = prev->next;
		command = prev->content;
		
		while (prev && ft_strchr("23", command->jmp_type + '0'))
		{
			prev = prev->next;
			command = prev->content;
			
		}
		//printf("ret %s\n", command->args->content);
		return (prev);
	}
	else
	{
		my_pipe(commands, pipe_count, 0, pipe_fd, p);
	}
	
}
int		manager(t_parser *p)
{
	char **av;
	t_command *command;
	int pipe_count;
	t_list *tmp;
	int r;
	int prev_jump;
	t_command *pr;
	t_list *commands;
	int b;

	b = 0;

	prev_jump = 0;
	commands = p->commands;
	while (commands)
	{
		signal(SIGINT, SIG_DFL);
		tmp = commands;
		
		command = commands->content;
		//printf("%s %d %d\n", command->args->content, prev_jump, command->jmp_type);
	
		if ((command->jmp_type == 0 || command->jmp_type == -1) && prev_jump == 0)
		{
			//printf("IN1\n");
			parse_args(command->args);
			av = args_create(command->args);
			b = try_builtin(command->args->content, av, p); //TODO 0 or -1
			//printf("%d\n", b);
			if (b < 0)
				fork_exec((char*)command->args->content, command->args, 0, 0, p);  //TODO DONT KNOW
			else
				status = b;
			free(av);
			
		}
		else if (command->jmp_type == 1)
		{
			//printf("IN2\n");
			tmp = find_left_redir(commands);
			if (tmp)
				commands = left_redir_start(tmp, p);
			else
				commands = pipe_start(commands, p);
			//tmp = commands->content;
			//printf("%s\n", tmp->args->content);
		}
		else if (command->jmp_type == 2 || command->jmp_type == 3)
		{
			//printf("IN3\n");
			commands = redir_start(commands, 0, 0, p);
			
		}
		else if (command->jmp_type == 4)
		{
			//printf("IN14\n");
			commands = left_redir_start(commands, p);
		}
		command = commands->content;
		prev_jump = command->jmp_type;
		commands = commands->next;
		//parser_free(p);
		//env_get(&c);
		//free(av);
		//exit(code);
		
	}
	//printf("status = %d\n", status);
	//close(0);
	

}


