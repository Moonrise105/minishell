/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:55:19 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/07 15:13:40 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list			*find_left_redir(t_list *commands)
{
	t_command *command;

	command = commands->content;
	while (commands)
	{
		if (command->jmp_type != 1)
			break ;
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

void			right_redir_write_exec(int *pipe_fd, int fd,
										t_command *first_cmd, int prev_jmp)
{
	if (pipe_fd && prev_jmp == 1)
	{
		dup2(fd, 1);
		execute_in(first_cmd);
		close(fd);
	}
	else if (pipe_fd && prev_jmp == 4)
	{
		pipe_fd[1] = fd;
		fork_exec(first_cmd, pipe_fd);
	}
	else
	{
		pipe_fd = malloc(sizeof(int) * 2);
		pipe_fd[1] = fd;
		pipe_fd[0] = 0;
		fork_exec(first_cmd, pipe_fd);
		free(pipe_fd);
	}
}

void			right_redir_write(t_list *prev_commands, t_command *first_cmd,
							int *pipe_fd, int prev_jmp)
{
	int			fd;
	t_command	*prev_command;
	t_command	*command;

	command = prev_commands->next->content;
	prev_command = prev_commands->content;
	if (prev_command->jmp_type == 2)
		fd = open(command->args->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(command->args->content, O_RDWR | O_APPEND | O_CREAT, 0644);
	right_redir_write_exec(pipe_fd, fd, first_cmd, prev_jmp);
	close(fd);
}

int				right_redir(int *pipe_fd, int prev_jmp,
						t_command *first_cmd, t_list *prev_commands)
{
	int			fd;
	t_list		*commands;
	t_command	*command;

	commands = prev_commands->next;
	command = commands->content;
	if (ft_strchr("23", command->jmp_type + '0'))
	{
		fd = open(command->args->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
		close(fd);
	}
	else
	{
		right_redir_write(prev_commands, first_cmd, pipe_fd, prev_jmp);
		return (1);
	}
	return (0);
}

t_list			*left_redir(t_list *commands, int *err, t_list **first_commands)
{
	struct stat		buf;
	t_command		*command;

	*err = 0;
	*first_commands = commands;
	command = commands->content;
	while (commands && command->jmp_type == 4)
	{
		commands = commands->next;
		if (commands)
		{
			command = commands->content;
			if (lstat(command->args->content, &buf) < 0 && !(*err))
			{
				*err = 1;
				prefix_command(command->args->content);
				perror(" ");
			}
		}
	}
	return (commands);
}
