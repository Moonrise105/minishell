/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctobias <ctobias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:55:37 by ctobias           #+#    #+#             */
/*   Updated: 2021/03/06 16:49:19 by ctobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_new.h"

void	sig_int(int signal)
{
	ft_putstr("\n");
}

void	signal_quit(int signal)
{
	ft_putstr("\b\b  \b\b");
}

void	signal_interrupt(int signal)
{
	ft_putstr("\b\b  \b\b");
	ft_putstr("\n");
	g_status = 1;
	shell_newline();
}

void	eof_ign(void)
{
	ft_putstr("  \b\b");
}
