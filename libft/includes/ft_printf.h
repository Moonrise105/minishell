/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 11:50:23 by olydden           #+#    #+#             */
/*   Updated: 2020/08/10 21:32:37 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

int				ft_printf(const char *format, ...);
typedef	struct	s_flags {
	int			precision;
	int			width;
	int			minus;
	int			null;
}				t_flags;
int				c_specifier(t_flags *p_t_flags, va_list ap);
int				s3_specifier(t_flags *p_t_flags, char **pointer);
int				s2_specifier(char **pointer, t_flags *p_t_flags,
							int *flag_error);
int				s1_specifier(char **pointer, t_flags *p_t_flags);
int				s_specifier(const char *format, int *i, t_flags *p_t_flags,
							va_list ap);
int				d_specifier(t_flags *p_t_flags, va_list ap, const char *format,
							int *i);
int				d1_specifier(t_flags *p_t_flags, const char *format, int *i,
							int d);
int				d2_specifier(int d, int null);
int				d3_specifier(int d);
int				d4_specifier(t_flags *p_t_flags, const char *format, int *i,
							int d);
int				d5_specifier(t_flags *p_t_flags, int d, const char *format,
							int *i);
int				d6_specifier(int d, t_flags *p_t_flags);
int				d7_specifier(t_flags *p_t_flags, int d);
int				d8_specifier(int null, t_flags *p_t_flags, int d);
int				d9_specifier(t_flags *p_t_flags, int d);
int				d10_specifier(int null, t_flags *p_t_flags, int d);
int				d11_specifier(t_flags *p_t_flags, int d, const char *format,
							int *i);
int				d12_specifier(t_flags *p_t_flags, int d);
int				d13_specifier(t_flags *p_t_flags, int null, int d);
int				d14_specifier(t_flags *p_t_flags, int d);
int				d15_specifier(t_flags *p_t_flags, int null, int d);
int				d16_specifier(t_flags *p_t_flags, const char *format, int *i,
							int d);
int				p_specifier(va_list ap, t_flags *p_t_flags, const char *format,
							int *i);
int				p1_specifier(t_flags *p_t_flags, char **pointer,
							unsigned long long p, int spaces);
void			p3_specifier(const char *format, int *i, char **pointer);
int				u_specifier(t_flags *p_t_flags, va_list ap, const char *format,
							int *i);
int				u1_specifier(t_flags *p_t_flags, unsigned int u);
int				u2_specifier(t_flags *p_t_flags, unsigned int u,
							const char *format, int *i);
int				u3_specifier(t_flags *p_t_flags, unsigned int u,
							const char *format, int *i);
int				u4_specifier(t_flags *p_t_flags, unsigned int u);
int				u5_specifier(t_flags *p_t_flags, unsigned int u,
							const char *format, int *i);
int				u6_specifier(t_flags *p_t_flags, unsigned int u);
int				u7_specifier(t_flags *p_t_flags, unsigned int u,
							const char *format, int *i);
int				x_specifier(t_flags *p_t_flags, va_list ap, const char *format,
							int *i);
int				x1_specifier(const char *format, int *i, char **pointer,
							unsigned int u);
int				x2_specifier(t_flags *p_t_flags, char **pointer);
int				x3_specifier(t_flags *p_t_flags, char **pointer);
int				x4_specifier(t_flags *p_t_flags, char **pointer);
int				x5_specifier(t_flags *p_t_flags, char **pointer);
int				x6_specifier(t_flags *p_t_flags, char **pointer);
int				x7_specifier(t_flags *p_t_flags, char **pointer);
int				x8_specifier(t_flags *p_t_flags, char **pointer);
int				percent_specifier(t_flags *p_t_flags);

#endif
