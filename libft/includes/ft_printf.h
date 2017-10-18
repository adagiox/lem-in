/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:34:42 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 00:34:44 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>
# include "libft.h"

typedef struct	s_printf
{
	int				length;
	int				width;
	char			spec;
	char			pad_char;
	char			prefix;
	int				prec;
	unsigned int	prec_set:1;
	unsigned int	is_char:1;
	unsigned int	is_short:1;
	unsigned int	is_long:1;
	unsigned int	is_longlong:1;
	unsigned int	is_sizet:1;
	unsigned int	intmax:1;
	unsigned int	alt:1;
	unsigned int	space:1;
	unsigned int	left:1;
	unsigned int	showsign:1;
	unsigned int	wide:1;
	unsigned int	pad:1;
	unsigned int	is_int:1;
}				t_printf;

typedef int		t_dispatcher(t_printf *flags, va_list args);

typedef struct	s_type
{
	char			spec;
	t_dispatcher	*func;
}				t_type;

int				ft_printf(const char *f, ...);
int				ft_getdigits(unsigned long long int value, int base);
int				ft_countdigits(long long int i);
int				ft_ucountdigits(unsigned long long int i);
void			ft_pfputchar(t_printf *flags, int c);
void			ft_uputnbr(t_printf *flags, unsigned long long int i);
void			ft_pfputnbr(t_printf *flags, long long int i);
void			ft_pfputstr(t_printf *flags, char *s);
void			ft_putnstr(t_printf *flags, char *s, int n);
void			ft_wputnstr(t_printf *flags, wchar_t *ws, int n);
int				ft_wstrlen(wchar_t *ws);
int				ft_wclen(wchar_t wc);
int				ft_wputstr(t_printf *flags, wchar_t *ws);
int				ft_wputchar(t_printf *flags, wchar_t wc);
void			ft_itoa_base(t_printf *flags, unsigned long long int i,
								int base, int offset);

int				vprintf(const char *f, va_list args);

int				format_int(t_printf *flags, long long int i);
void			print_int(t_printf *flags, int num_space, int num_zero,
								long long int i);
int				zero_case_int(t_printf *flags, long long int i);
void			print_left_int(t_printf *flags, int num_space, int num_zero,
								long long int i);

int				format_uint(t_printf *flags, unsigned long long int i);
void			print_left_uint(t_printf *flags, int num_space, int num_zero,
								unsigned long long int i);
void			print_uint(t_printf *flags, int num_space, int num_zero,
								unsigned long long int i);

int				format_oct(t_printf *flags, unsigned long long int i);
int				zero_case_oct(t_printf *flags, unsigned long long int i);
void			print_left_oct(t_printf *flags, int num_space, int num_zero,
								unsigned long long int i);
void			print_oct(t_printf *flags, int num_space, int num_zero,
								unsigned long long int i);

int				format_hex(t_printf *flags, unsigned long long int i);
int				get_offset(t_printf *flags);
int				zero_case_hex(t_printf *flags, unsigned long long int i);
void			print_left_hex(t_printf *flags, int num_space, int num_zero,
								unsigned long long int i);
void			print_hex(t_printf *flags, int num_space, int num_zero,
								unsigned long long int i);

int				set_prefix(t_printf *flags, long long int i);
int				set_uprefix(t_printf *flags);
int				print_zero(t_printf *flags, int n);
int				print_space(t_printf *flags, int n);
int				print_prefix(t_printf *flags);
int				print_s(t_printf *flags, char *s);
int				print_ws(t_printf *flags, wchar_t *ws);
int				print_c(t_printf *flags, int c);
int				cast_int(t_printf *flags, long long int i);
int				cast_uint(t_printf *flags, unsigned long long int u);
int				print_wc(t_printf *flags, wchar_t wc);
int				convert_p(t_printf *flags, va_list args);
int				convert_x(t_printf *flags, va_list args);
int				convert_c(t_printf *flags, va_list args);
int				convert_s(t_printf *flags, va_list args);
int				convert_i(t_printf *flags, va_list args);
int				convert_u(t_printf *flags, va_list args);
int				convert_wc(t_printf *flags, va_list args);
int				convert_ws(t_printf *flags, va_list args);
int				do_conversion(t_printf *flags, va_list args);
int				handle_percent(t_printf *flags);
int				set_flags(const char **f, va_list args);
int				set_spec(const char **f, t_printf *flags, va_list args);
int				set_length(const char **f, t_printf *flags, va_list args);
int				set_width(const char **f, t_printf *flags, va_list args);
int				set_prec(const char **f, t_printf *flags, va_list args);
t_printf		*init_flags();

#endif
