/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 20:08:30 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/06 17:11:01 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_builtin(char *cmd)
{
	int code;

	code = 0;
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") ||
		!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") ||
		!ft_strcmp(cmd, "exit"))
		code = 1;
	return (code);
}

int			get_cmd_exec_type(char *cmd)
{
	int		type;
	t_list	*env;
	char	**path;
	t_pair	*path_pair;

	env = env_get(NULL);
	path_pair = dict_get(env, "PATH");
	if (path_pair)
		path = ft_split(path_pair->value, ':');
	else
		path = NULL;
	if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		type = ERROR_TYPE;
	else if (is_builtin(cmd))
		type = BULTIN_TYPE;
	else if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "../", 3) ||
			!ft_strncmp(cmd, "/", 1))
		type = PATH_TYPE;
	else if (parse_dirs(path, cmd))
		type = BIN_TYPE;
	else
		type = ERROR_TYPE;
	if (path)
		free_array_char(path);
	return (type);
}

int			builtin_exec(t_command *command)
{
	char	**args;
	int		code;
	
	code = 0;
	args = args_create(command->args);
	if (!ft_strcmp("echo", command->args->content))
		code = echo(args + 1);
	else if (!ft_strcmp("pwd", command->args->content))
		code = pwd();
	else if (!ft_strcmp("cd", command->args->content))
		code = cd(args + 1);
	else if (!ft_strcmp("env", command->args->content))
		code = env_f(args + 1, 0);
	else if (!ft_strcmp("export", command->args->content))
		code = export(args + 1);
	else if (!ft_strcmp("unset", command->args->content))
		code = unset(args + 1);
	else if (!ft_strcmp("exit", command->args->content))
		code = my_exit(args + 1);
	free_array_char(args);
	return (code);
}

int			execute_path(char *path, char **args, char **env, char *cmd_name)
{
	int		code;

	errno = 0;
	code = 0;
	if (execve(path, args, env) < 0)
	{
		prefix_command(cmd_name);
		perror(" ");
		code = 127;
	}
	return (code);
}

int			path_exec(t_command *command)
{
	char	**args;
	int		code;
	char	**env;

	env = dict_to_arr(env_get(NULL));
	args = args_create(command->args);
	code = execute_path(command->args->content,
						args, env, command->args->content);
	free_array_char(args);
	free_array_char(env);
	return (code);
}
