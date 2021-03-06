/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 11:49:25 by olydden           #+#    #+#             */
/*   Updated: 2021/03/06 17:19:50 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		specifiers_s_p(const char *format, va_list ap, int *i,
						t_flags *p_t_flags)
{
	int	printed;

	printed = 0;
	if (format[*i] == 's')
	{
		if ((printed = s_specifier(format, i, p_t_flags, ap)) < 0)
			return (-1);
	}
	if (format[*i] == 'p')
	{
		if ((printed = p_specifier(ap, p_t_flags, format, i)) < 0)
			return (-1);
	}
	return (printed);
}

int		specifiers(const char *format, va_list ap, int *i, t_flags *p_t_flags)
{
	int printed;
	int	j;

	printed = 0;
	j = 0;
	if (format[*i] == 'c')
		printed += c_specifier(p_t_flags, ap);
	if ((j = specifiers_s_p(format, ap, i, p_t_flags)) < 0)
		return (-1);
	printed += j;
	if (format[*i] == 'd' || format[*i] == 'i')
		printed += d_specifier(p_t_flags, ap, format, i);
	if (format[*i] == 'u')
		printed += u_specifier(p_t_flags, ap, format, i);
	if (format[*i] == 'x' || format[*i] == 'X')
	{
		if ((j = x_specifier(p_t_flags, ap, format, i)) < 0)
			return (-1);
		printed += j;
	}
	if (format[*i] == '%')
		printed += percent_specifier(p_t_flags);
	ft_free(p_t_flags);
	return (printed);
}

void	flags(const char *format, va_list ap, int *i, t_flags *p_t_flags)
{
	while (format[*i] != '\0' && !(ft_strchr("cspdiuxX%", format[*i])))
	{
		if (format[*i] == '-')
			p_t_flags->minus = 1;
		if (format[*i] == '*' && (format[*i - 1] == '-' ||
			format[*i - 1] == '0' || format[*i - 1] == '%'))
		{
			if ((p_t_flags->width = va_arg(ap, int)) < 0)
			{
				p_t_flags->minus = 1;
				p_t_flags->width = -p_t_flags->width;
			}
		}
		if (format[*i] == '*' && format[*i - 1] == '.')
			p_t_flags->precision = va_arg(ap, int);
		if (format[*i] == '0' && format[*i - 1] != '.')
			p_t_flags->null = 1;
		if (ft_isdigit(format[*i]) && format[*i] != '0' &&
			(format[*i - 1] == '-' || format[*i - 1] == '0'
			|| format[*i - 1] == '%'))
			p_t_flags->width = ft_atoi(format, i);
		if (ft_isdigit(format[*i]) && format[*i - 1] == '.')
			p_t_flags->precision = ft_atoi(format, i);
		(*i)++;
	}
}

int		create_struct(const char *format, va_list ap, int *i, int *printed)
{
	t_flags *p_t_flags;
	int		j;

	p_t_flags = NULL;
	j = 0;
	if (!(p_t_flags = (t_flags *)malloc(sizeof(t_flags))))
	{
		ft_free(p_t_flags);
		return (-1);
	}
	p_t_flags->precision = -1;
	p_t_flags->width = 0;
	p_t_flags->minus = 0;
	p_t_flags->null = 0;
	flags(format, ap, i, p_t_flags);
	if ((j = specifiers(format, ap, i, p_t_flags)) < 0)
		return (-1);
	*printed += j;
	return (1);
}

int		ft_printf(const char *format, ...)
{
	int			printed;
	int			i;
	va_list		ap;

	va_start(ap, format);
	printed = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			if (create_struct(format, ap, &i, &printed) < 0)
				return (-1);
			i++;
			continue;
		}
		ft_putchar(format[i]);
		printed++;
		i++;
	}
	va_end(ap);
	return (printed);
}
