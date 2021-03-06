/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:03:03 by olydden           #+#    #+#             */
/*   Updated: 2021/03/06 17:16:03 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include "../libft/includes/libft.h"
# include "parser.h"
# include "dict.h"
# include "errno.h"
# include <sys/stat.h>

extern int g_status;

# define READ_EXIT 1
# define READ_END 0

void	shell_newline();
int		manager(t_list *commands);

# define FORK_ERROR -4
# define BULTIN_TYPE 3
# define BIN_TYPE 4
# define PATH_TYPE 5
# define ERROR_TYPE -3

char	**args_create(t_list *args);
int		execute_handler(t_command *command);
int		execute_in(t_command *command);
int		fork_exec(t_command *command, int *dup_fd);
int		is_builtin(char *cmd);
int		get_cmd_exec_type(char *cmd);
int		builtin_exec(t_command *command);
int		execute_path(char *path, char **args, char **env, char *cmd_name);
int		path_exec(t_command *command);
int		bin_exec(t_command *command);
void	fork_exec_parent(int *dup_fd);

void	signal_interrupt(int signal);
void	signal_quit(int signal);
void	signal_interrupt(int signal);
void	eof_ign(void);
void	sig_int(int signal);

int		semicolon_handler(t_command *command);
t_list	*pipe_handler(t_list *commands);
t_list	*right_redir_handler(t_list *commands, int *pipe_fd, int prev_jmp);
t_list	*left_redir_handler(t_list *commands);

int		echo(char **av);
int		pwd(void);
int		cd(char **args);

void	prefix_command(char *command);
void	print_newline(char *s, int fd);
void	chdir_error(char *path);

int		find_file(DIR *dir, char *file);
char	*parse_dirs(char **dirs, char *file);

t_list	*env_get(t_list **nw);
int		env_f(char **av, int dec);
int		export(char **av);
int		unset(char **av);

int		pipe_count(t_list *commands);
int		my_pipe(t_list *commands, int count, int i, int *pipe_fd);

t_list	*find_left_redir(t_list *commands);
void	right_redir_write_exec(int *pipe_fd, int fd,
									t_command *first_cmd, int prev_jmp);
void	right_redir_write(t_list *prev_commands, t_command *first_cmd,
							int *pipe_fd, int prev_jmp);
int		right_redir(int *pipe_fd, int prev_jmp,
						t_command *first_cmd, t_list *prev_commands);
t_list	*left_redir(t_list *commands, int *err, t_list **first_commands);

t_list	*skip_jmps(t_list *commands, char *jmps);
void	lst_free(t_list **lst);
char	**split_f(char *s, char c);
int		my_exit(char **args);
int		is_numeric(char *s);
char	*split_path(char *s1, char *s2);

#endif
