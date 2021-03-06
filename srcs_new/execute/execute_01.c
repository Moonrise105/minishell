/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 20:08:30 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/06 17:12:34 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			bin_exec(t_command *command)
{
	t_list	*env;
	char	**path;
	char	*cmd_path;
	char	*file_path;

	env = env_get(NULL);
	path = ft_split(dict_get(env, "PATH")->value, ':');
	cmd_path = parse_dirs(path, command->args->content);
	file_path = split_path(cmd_path, command->args->content);
	execute_path(file_path, args_create(command->args),
				dict_to_arr(env), command->args->content);
	return (0);
}

int			execute_in(t_command *command)
{
	int type;
	int code;

	type = get_cmd_exec_type(command->args->content);
	parse_args(command->args);
	if (type == BIN_TYPE)
	{
		code = bin_exec(command);
	}
	else if (type == PATH_TYPE)
		code = path_exec(command);
	else if (type == BULTIN_TYPE)
		code = builtin_exec(command);
	else
	{
		prefix_command(command->args->content);
		ft_putstr_fd(": command not found\n", 2);
		code = 127;
	}
	g_status = code;
	return (code);
}

void		fork_exec_parent(int *dup_fd)
{
	signal(SIGINT, sig_int);
	waitpid(-1, &g_status, 0);
	if (WIFSIGNALED(g_status))
		g_status = WTERMSIG(g_status) + 128;
	else
		g_status = WEXITSTATUS(g_status);
	if (dup_fd && dup_fd[0])
		close(dup_fd[0]);
	if (dup_fd && dup_fd[1])
		close(dup_fd[1]);
}

int			fork_exec(t_command *command, int *dup_fd)
{
	int pid;

	pid = fork();
	if (pid > 0)
		fork_exec_parent(dup_fd);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (dup_fd && dup_fd[1])
			dup2(dup_fd[1], 1);
		if (dup_fd && dup_fd[0])
			dup2(dup_fd[0], 0);
		exit(execute_in(command));
	}
	else
		return (FORK_ERROR);
	return (0);
}

int			execute_handler(t_command *command)
{
	int		type;

	type = get_cmd_exec_type(command->args->content);
	if (type == BIN_TYPE || type == PATH_TYPE)
		fork_exec(command, NULL);
	else
		execute_in(command);
	return (0);
}
