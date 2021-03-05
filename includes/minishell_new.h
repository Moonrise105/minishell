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
# include <termcap.h>
# include <termios.h>
extern int g_status;
typedef struct			s_pair
{
	char				*key;
	char				*value;
}						t_pair;



//dict
void	dict_set(t_list *dict, char *key, char *value);
t_list	*dict_del(t_list *dict, char *key);
t_list	*dict_create(char **array, char key);
char	**dict_to_arr(t_list *dict);
t_pair	*dict_get(t_list *dict, char *key);
void	dict_free(t_list **dict);
void	free_array_char(char **array);
void	dict_print(t_list *dict, char delim);

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

//arg_parser
void	parse_args(t_list *args);

//utils
t_list *skip_jmps(t_list *commands, char *jmps);
void	lst_free(t_list **lst);
char	**split_f(char *s, char c);
int		my_exit(char **args);
#endif