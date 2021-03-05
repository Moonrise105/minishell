/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 16:26:29 by olydden           #+#    #+#             */
/*   Updated: 2021/03/05 17:37:36 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_new.h"

// void			print(void *s)
// {
// 	printf("%s\n", s);
// }

// void			print_lst(t_list *lst)
// {
// 	ft_lstiter(lst, print);
// }

// void		print_command(t_command *command)
// {
// 	printf("jmp = %d\n", command->jmp_type);
// 	print_lst(command->args);
// }

// void		print_commands(t_list *commands)
// {
// 	ft_lstiter(commands, print_command);
// }

void		add_args_or_command(t_parser *p)
{
	if (p->letters)
		args_add_after_redir(p);
	if (p->args)
		commands_add(&(p->commands), command_create(p->args, -1));
}

void		create_arg(t_parser *p, char *input)
{
	if (p->q1 || p->q2)
		letter_add(&p->letters, input);
	else if (p->letters)
		args_add_after_redir(p);
	else
	{
	}
}

void		add_to_command_if_redir(t_parser *p, char *input)
{
	if (!p->q1 && !p->q2)
	{
		if (p->letters)
			args_add_after_redir(p);
		if (*input == '>')
			check_redir_and_add(p);
		else
		{
			commands_add(&p->commands,
							command_create(p->args, jmp_get(*input)));
			p->args = NULL;
			p->first_arg = NULL;
		}
	}
	else
		letter_add(&p->letters, input);
}

void		create_commands(t_parser *p, char input)
{
	if (p->append_redir && input != '>' && !p->backslash)
	{
		commands_add(&p->commands, command_create(p->args, 2));
		p->args = NULL;
		p->append_redir = 0;
	}
}

int			parser(t_parser *p, char input)
{
	create_commands(p, input);
	if (is_redirect(input) && !p->backslash)
		add_to_command_if_redir(p, &input);
	else if (input == '\n')
	{
		add_args_or_command(p);
		return (0);
	}
	else if (is_quoter(input))
	{
		set_quoter_flag(p, input);
		letter_add(&p->letters, &input);
	}
	else if ((input == ' ' || input == '\t') && !p->backslash)
		create_arg(p, &input);
	else
	{
		p->backslash = 0;
		letter_add(&p->letters, &input);
		if (input == 92)
			p->backslash = 1;
	}
	return (1);
}
