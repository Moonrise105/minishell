#include "minishell_new.h"

int		is_builtin(char *cmd)
{
	int code;
	
	code = 0;
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") ||
		!ft_strcmp(cmd, "cd"))
		code = 1;
	return (code);
}

int		get_cmd_exec_type(char *cmd)
{
	int type;
	t_list *env;
	char **path;

	env = env_get(NULL);
	path = ft_split(dict_get(env, "PATH")->value, ':');
	if (is_builtin(cmd))
		type = BULTIN_TYPE;
	else if (!ft_strncmp(cmd, "./", 2) ||
			!ft_strncmp(cmd, "../", 3) ||
			!ft_strncmp(cmd, "/", 1))
		type = PATH_TYPE;
	
	else if (parse_dirs(path, cmd))
		type = BIN_TYPE;
	else
		type = ERROR_TYPE;
	free_array_char(path);
	return (type);
}

char	**args_create(t_list *args)
{
	int size;
	char **argv;
	int i;

    argv = NULL;
    if (args)
    {
        size = ft_lstsize(args);
        argv = (char**)malloc(sizeof(char*) * (size + 1));
        i = 0;
        while (args)
        {
            argv[i] = ft_strdup(args->content);
            args = args->next;
            ++i;
        }
        argv[i] = NULL;
    }
	return (argv);
}

int     builtin_exec(t_command *command)
{
    char **args;
    int code;

    args = args_create(command->args);
    if (!ft_strcmp("echo", command->args->content))
        code = echo(args + 1);
	else if (!ft_strcmp("pwd", command->args->content))
		code = pwd(args + 1);
	else if (!ft_strcmp("cd", command->args->content))
		code = cd(args + 1);
    free_array_char(args);
    return (code);
}


int		execute_path(char *path, char **args, char **env, char *cmd_name)
{
	errno = 0;
	if (execve(path, args, env) < 0)
	{
		prefix_command(cmd_name);
		perror(" ");
	}
	return (0);
}

int		path_exec(t_command *command)
{
	char **args;
	int code;
	char **env;

	env = dict_to_arr(env_get(NULL));
	args = args_create(command->args);
	code = execute_path(command->args->content, 
						args, env, command->args->content);
	free_array_char(args);
	free_array_char(env);
	return (code);
}

char	*split_path(char *s1, char *s2)
{
	char *tmp;
	char *res;

	tmp = ft_strjoin(s1, "/");
	res = ft_strjoin(tmp, s2);
	free(tmp);
	return (res); 	
}

int		bin_exec(t_command *command)
{
	char	**args;
	t_list	*env;
	int		code;
	char	**path;
	char	*cmd_path;
	char	*file_path;

	env = env_get(NULL);
	args = args_create(command->args);
	path = ft_split(dict_get(env, "PATH")->value, ':');
	cmd_path = parse_dirs(path, command->args->content);
	file_path = split_path(cmd_path, command->args->content);
	execute_path(file_path, args, dict_to_arr(env), command->args->content);
	return (0);
}

int		execute_in(t_command *command)
{
	int type;
	int code;

	type = get_cmd_exec_type(command->args->content);
	parse_args(command->args);
	//printf("%d\n", type);
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
	status = code;
	return (code);
}

int		fork_exec(t_command *command, int *dup_fd)
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
		if (dup_fd && dup_fd[0])
			close(dup_fd[0]);
		if (dup_fd && dup_fd[1])
			close(dup_fd[1]);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (dup_fd && dup_fd[1])
			dup2(dup_fd[1], 1);
		if (dup_fd && dup_fd[0])
			dup2(dup_fd[0], 0);
		//EXECUTE COMMAND
		exit(execute_in(command));
	}
	else
		return (FORK_ERROR);
	return (0);
}




int     execute_handler(t_command *command)
{
    int code;
	int type;

	type = get_cmd_exec_type(command->args->content);
	if (type == BIN_TYPE || type == PATH_TYPE)
	{
		fork_exec(command, NULL);
	}
		
	else //type == BUILTIN_TYPE
		execute_in(command);
	
    return (0);
}