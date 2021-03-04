#ifndef PARSER_H
# define PARSER_H


typedef struct 			s_command
{
	t_list				*args;
	int					jmp_type;		// ';' = 0, '|' = 1, '>' = 2, '>>' = 3, '<' = 4, "end" = -1
}						t_command;

typedef struct			s_parser
{
	t_list				*first_arg;
	t_list				*letters;
	t_list				*commands;
	t_list				*args;
	int					q1;
	int					q2;
	int					append_redir;
	int					backslash;
}						t_parser;

//void		free_t_command(t_command **lst);
void	commands_free(t_list **commands);
void	parser_null(t_parser *p);
int		parser(t_parser *p, char input);
int		parser_check(t_list *commands);
void	commands_free(t_list **commands);
#endif
