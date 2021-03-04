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

extern int status;
typedef struct			s_pair
{
	char				*key;
	char				*value;
}						t_pair;
void	dict_free(t_list **dict);
t_pair	*dict_get(t_list *dict, char *key);
t_pair	*pair_get(char *s, char key);
t_list	*dict_create(char **array, char key);
void	dict_set(t_list *dict, char *key, char *value);
t_list	*dict_del(t_list *dict, char *key);
char	*parse_dirs(char **dirs, char *file);
int		find_file(DIR *dir, char *file);
char	**dict_to_arr(t_list *dict);
int		manager(t_parser *p);
int		echo(char **av);
char	**args_create(t_list *args);
int		env_f(char **av, int dec);
char	**split_f(char *s, char c);
int		export(char **av);
char	**env_get(char **nw);
int		unset(char **av);
int		cd(char **args);
char	*parse_arg(char *s);
int		pwd(char **args);
void	parse_args(t_list *args);
void	signal_ign(int signal);
int		exec_command_path(char *cmd, char **av);
int		my_exit(char **args, t_parser *p);
void	parser_free(t_parser *p);
void	free_array_char(char **array);

void	lst_free(t_list **lst);
#endif