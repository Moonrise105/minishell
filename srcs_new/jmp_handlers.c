#include "minishell_new.h"

int    semicolon_handler(t_command *command)
{
    int code;

    code = execute_handler(command);
    return (code);
}

t_list	*pipe_handler(t_list *commands)
{
	int pid;
	int count;
	int *pipe_fd;

	count = pipe_count(commands);
	pid = fork();
	if (pid > 0)
	{
		signal(SIGINT, sig_int);
		waitpid(-1, &status, 0);
		if (WIFSIGNALED(status))
			status = WTERMSIG(status) + 128;
		else
			status = WEXITSTATUS(status);
		return (skip_jmps(commands, "123"));
	}
	else if (pid == 0)
	{
		my_pipe(commands, count, 0, pipe_fd);
	}
	else;
	
}

t_list    *right_redir_handler(t_list *commands, int *pipe_fd, int prev_jmp)
{
	t_command	*command;
	t_command	*first_cmd;
	int			fd;
	t_command	*prev_command;
	t_list		*prev_commands;

	command = commands->content;
	first_cmd = command;
	//prev_command = first_cmd;
	commands = skip_jmps(commands, "4");
	prev_command = commands->content;
	commands = commands->next;
	command = commands->content;
	
	while (commands)
	{
		
		if (ft_strchr("23", command->jmp_type + '0'))
		{
			fd = open(command->args->content, O_RDWR|O_CREAT|O_TRUNC, 0644);
			close(fd);
		}
		else
		{
			if (prev_command->jmp_type == 2)
				fd = open(command->args->content, O_RDWR|O_CREAT|O_TRUNC, 0644);
			else
				fd = open(command->args->content, O_RDWR|O_APPEND|O_CREAT, 0644);
			if (pipe_fd && prev_jmp == 1) //after pipes
			{
				dup2(fd, 1);
				execute_in(first_cmd);
				close(fd);
				
			}
			else if (pipe_fd && prev_jmp == 4) //after <
			{
				pipe_fd[1] = fd;
				fork_exec(first_cmd, pipe_fd);
				//free(pipe_fd);
			}
			else
			{
				pipe_fd = malloc(sizeof(int) * 2);
				pipe_fd[1] = fd;
				pipe_fd[0] = 0;
				fork_exec(first_cmd, pipe_fd);
				free(pipe_fd);
			}
			// if (pipe_fd && pipe_fd[0])
			// 	close(pipe_fd[0]);
			close(fd);
			return (commands);
		}
		prev_commands = commands;
		prev_command = command;
		commands = commands->next;
		command = commands->content;
	}
	
	//if (pipe_fd)
		//close(pipe_fd)
}

t_list    *left_redir_handler(t_list *commands)
{
	t_command	*command;
	t_command	*first_cmd;
	t_list		*first_commands;
	struct stat	buf;
	int err;
	int fd;
	int dup_fd[2];

	err = 0;
	first_commands = commands;
	command = commands->content;
	first_cmd = command;
	while (commands && command->jmp_type == 4)
	{
		commands = commands->next;
		if (commands)
		{
			command = commands->content;
			if (lstat(command->args->content, &buf) < 0 && !err)
			{
				err = 1;
				prefix_command(command->args->content);
				perror(" ");
			}
		}
	}
	if (err)
		return (commands);
	dup_fd[0] = open(command->args->content, O_RDONLY);
	dup_fd[1] = 0;
	if (ft_strchr("23", command->jmp_type + '0'))
		commands = right_redir_handler(first_commands, dup_fd, 4);
	else
		fork_exec(first_cmd, dup_fd);
	close(dup_fd[0]);
	return (commands);
}