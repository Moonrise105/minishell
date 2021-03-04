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
	status = 1;
	shell_newline();
}

void	eof_ign(void)
{
	ft_putstr("  \b\b");
}