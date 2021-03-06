#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h> // delete
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include "../libft/includes/libft.h"
# include "parser.h"
# include "errno.h"
# include <sys/stat.h>
extern int g_status;

//dict
void	dict_set(t_list *dict, char *key, char *value);
t_list	*dict_del(t_list *dict, char *key);
t_list	*dict_create(char **array, char key);
char	**dict_to_arr(t_list *dict);
t_pair	*dict_get(t_list *dict, char *key);
void	dict_free(t_list **dict);
void	free_array_char(char **array);
void	dict_print(t_list *dict, char delim);
void		pair_free(void *pair);

//shell
#define READ_EXIT 1
#define READ_END 0
void	shell_newline();

//manager
int     manager(t_list *commands);

//execute
#define FORK_ERROR -4
#define BULTIN_TYPE 3
#define BIN_TYPE 4
#define PATH_TYPE 5
#define ERROR_TYPE -3

char	**args_create(t_list *args);
int     execute_handler(t_command *command);
int		execute_in(t_command *command);
int		fork_exec(t_command *command, int *dup_fd);
int			is_builtin(char *cmd);
int			get_cmd_exec_type(char *cmd);
int			builtin_exec(t_command *command);
int			execute_path(char *path, char **args, char **env, char *cmd_name);
int			path_exec(t_command *command);
int			bin_exec(t_command *command);
void		fork_exec_parent(int *dup_fd);

//signals
void	signal_interrupt(int signal);
void	signal_quit(int signal);
void	signal_interrupt(int signal);
void	eof_ign(void);
void	sig_int(int signal);

//jmp_handlers
int    semicolon_handler(t_command *command);
t_list	*pipe_handler(t_list *commands);
t_list    *right_redir_handler(t_list *commands, int *pipe_fd, int prev_jmp);
t_list    *left_redir_handler(t_list *commands);
//builtins
int		echo(char **av);
int		pwd(char **args);
int		cd(char **args);
//messages
void	prefix_command(char *command);
void	print_newline(char *s, int fd);
void	chdir_error(char *path);

//finder
int		find_file(DIR *dir, char *file);
char	*parse_dirs(char **dirs, char *file);

//env
t_list		*env_get(t_list **nw);
int			env_f(char **av, int dec);
int		export(char **av);
int		unset(char **av);

//pipe
int		pipe_count(t_list *commands);
int		my_pipe(t_list *commands, int count, int i, int *pipe_fd);

//redirects
t_list	*find_left_redir(t_list *commands);
void			right_redir_write_exec(int *pipe_fd, int fd,
										t_command *first_cmd, int prev_jmp);
void			right_redir_write(t_list *prev_commands, t_command *first_cmd,
							int *pipe_fd, int prev_jmp);
int			right_redir(int *pipe_fd, int prev_jmp,
						t_command *first_cmd, t_list *prev_commands);
t_list		*left_redir(t_list *commands, int *err, t_list **first_commands);

//utils
t_list *skip_jmps(t_list *commands, char *jmps);
void	lst_free(t_list **lst);
char	**split_f(char *s, char c);
int		my_exit(char **args);
int			is_numeric(char *s);
char		*split_path(char *s1, char *s2);
#endif