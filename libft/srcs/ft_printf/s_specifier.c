/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 15:55:34 by olydden           #+#    #+#             */
/*   Updated: 2020/08/10 20:26:52 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	s4_specifier(const char *format, int *i, char **pointer, va_list ap)
{
	if (format[*i - 1] == '.')
	{
		if (!(*pointer = ft_strdup("")))
		{
			ft_free(*pointer);
			return (-1);
		}
	}
	else
		*pointer = va_arg(ap, char *);
	return (1);
}

int	s3_specifier(t_flags *p_t_flags, char **pointer)
{
	int counter;
	int printed;
	int spaces;

	counter = 0;
	printed = 0;
	spaces = p_t_flags->width - ft_strlen(*pointer);
	if (p_t_flags->width)
	{
		while (counter++ < spaces)
		{
			if (p_t_flags->null)
				printed += ft_putchar('0');
			else
				printed += ft_putchar(' ');
		}
	}
	printed += ft_putstr(*pointer);
	return (printed);
}

int	s2_specifier(char **pointer, t_flags *p_t_flags, int *flag_error)
{
	int spaces;

	spaces = 0;
	if (p_t_flags->precision >= 0 && *pointer != NULL)
	{
		if (!(*pointer = ft_strndup(*pointer, p_t_flags->precision)))
		{
			ft_free(*pointer);
			*flag_error = 1;
			return (-1);
		}
	}
	if (p_t_flags->width)
		spaces = p_t_flags->width - ft_strlen(*pointer);
	return (spaces);
}

int	s1_specifier(char **pointer, t_flags *p_t_flags)
{
	int printed;
	int spaces;
	int counter;
	int	flag_error;

	printed = 0;
	counter = 0;
	flag_error = 0;
	spaces = s2_specifier(pointer, p_t_flags, &flag_error);
	if (flag_error)
		return (-1);
	if (p_t_flags->minus)
	{
		printed += ft_putstr(*pointer);
		if (p_t_flags->width)
		{
			while (counter++ < (spaces = p_t_flags->width -
					ft_strlen(*pointer)))
				printed += ft_putchar(' ');
		}
	}
	else
		printed += s3_specifier(p_t_flags, pointer);
	return (printed);
}

int	s_specifier(const char *format, int *i, t_flags *p_t_flags, va_list ap)
{
	int		printed;
	char	*pointer;
	int		j;

	printed = 0;
	pointer = NULL;
	j = 0;
	if (s4_specifier(format, i, &pointer, ap) < 0)
		return (-1);
	if (!pointer || (pointer == 0 && p_t_flags->precision < 0))
		pointer = "(null)";
	if ((j = s1_specifier(&pointer, p_t_flags)) < 0)
		return (-1);
	printed += j;
	if ((p_t_flags->precision >= 0) || format[*i - 1] == '.')
		ft_free(pointer);
	return (printed);
}
