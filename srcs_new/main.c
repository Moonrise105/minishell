/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:59:55 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/06 16:52:20 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status = 0;

void		shell_newline(void)
{
	ft_putstr("minishell% ");
}

int			read_command(t_parser *parser_struct)
{
	char	input;
	int		read_bytes;
	int		code;

	input = '\0';
	while (1)
	{
		signal(SIGINT, signal_interrupt);
		signal(SIGQUIT, signal_quit);
		read_bytes = read(0, &input, 1);
		code = parser(parser_struct, input);
		if (read_bytes && !code)
			return (READ_END);
		else if (!read_bytes && !input)
			return (READ_EXIT);
		else if (!read_bytes)
			eof_ign();
	}
}

void		shell(char **env)
{
	t_list		*dict;
	t_parser	parser_struct;

	dict = dict_create(env, '=');
	env_get(&dict);
	while (1)
	{
		parser_null(&parser_struct);
		shell_newline();
		if (read_command(&parser_struct) == READ_EXIT)
		{
			dict_free(&dict);
			commands_free(&parser_struct.commands);
			my_exit(NULL);
		}
		if (parser_check(parser_struct.commands) >= 0)
			manager(parser_struct.commands);
		commands_free(&(parser_struct.commands));
	}
}

int			main(int ac, char **av, char **en)
{
	shell(en);
	return (0);
}
