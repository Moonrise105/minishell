/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:46:07 by olydden           #+#    #+#             */
/*   Updated: 2021/03/06 15:05:43 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct	s_command
{
	t_list		*args;
	int			jmp_type;
}				t_command;

typedef struct	s_parser
{
	t_list		*first_arg;
	t_list		*letters;
	t_list		*commands;
	t_list		*args;
	int			q1;
	int			q2;
	int			append_redir;
	int			backslash;
}				t_parser;

typedef struct	s_arg_parser
{
	int		q1;
	int		q2;
	t_list	*new_str;
	int		ec;
	int		i;
}				t_arg_parser;

int				parser(t_parser *p, char input);
int				is_redirect(char c);
int				is_quoter(char c);
void			set_quoter_flag(t_parser *p, char input);
int				parser_check(t_list *commands);
void			commands_free(t_list **commands);
int				jmp_get(char c);
void			parser_null(t_parser *p);
void			check_redir_and_add(t_parser *p);
void			args_add_after_redir(t_parser *p);
char			*word_get(t_list **letters);
void			letter_add(t_list **letters, char *c);
void			commands_add(t_list **commands, t_command *command);
t_command		*command_create(t_list *args, int jump);
void			set_quoter_flags(int *q);
void			sign_question(char **number, char *val, t_list **lst);
void			sym_add(t_list **lst, char *sym);
void			str_add(t_list **lst, char *s);
void			add_str_or_sym(t_list **lst, t_pair **pair);

#endif
