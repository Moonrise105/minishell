/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 21:39:06 by olydden           #+#    #+#             */
/*   Updated: 2021/03/09 20:03:25 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		p4_specifier(t_flags *p_t_flags, char **pointer, int spaces,
				unsigned long long p)
{
	int printed;
	int counter;
	int	null;

	printed = 0;
	counter = 0;
	null = p_t_flags->precision - ft_strlen(*pointer);
	while (counter++ < spaces)
		printed += ft_putchar(' ');
	if (p)
		printed += ft_putstr("0x");
	counter = 0;
	while ((p_t_flags->precision > 0) && counter++ < null)
		printed += ft_putchar('0');
	printed += ft_putstr(*pointer);
	return (printed);
}

void	p3_specifier(const char *format, int *i, char **pointer)
{
	if (format[*i - 1] == '.' || format[*i - 1] == '0')
		*pointer = "0x";
	else
		*pointer = "0x0";
}

int		p2_specifier(t_flags *p_t_flags, char **pointer, unsigned long long p)
{
	int	spaces;

	spaces = 0;
	if (p_t_flags->width && p)
		spaces = (p_t_flags->width - (ft_strlen(*pointer) + 2));
	else
		spaces = (p_t_flags->width - ft_strlen(*pointer));
	return (spaces);
}

int		p1_specifier(t_flags *p_t_flags, char **pointer, unsigned long long p,
					int spaces)
{
	int printed;
	int counter;

	printed = 0;
	counter = 0;
	if (p_t_flags->minus)
	{
		if (p)
			printed += ft_putstr("0x");
		printed += ft_putstr(*pointer);
		while (counter++ < spaces)
			printed += ft_putchar(' ');
	}
	else
		printed += p4_specifier(p_t_flags, pointer, spaces, p);
	return (printed);
}

int		p_specifier(va_list ap, t_flags *p_t_flags, const char *format, int *i)
{
	int					printed;
	char				*pointer;
	unsigned long long	p;
	int					spaces;

	printed = 0;
	pointer = NULL;
	spaces = 0;
	p = va_arg(ap, unsigned long long);
	if (p)
	{
		if (!(pointer = ft_itoa_base(p, 16)))
		{
			ft_free(pointer);
			return (-1);
		}
	}
	else
		p3_specifier(format, i, &pointer);
	spaces = p2_specifier(p_t_flags, &pointer, p);
	printed += p1_specifier(p_t_flags, &pointer, p, spaces);
	if (p)
		ft_free(pointer);
	return (printed);
}
