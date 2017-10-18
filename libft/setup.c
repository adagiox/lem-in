/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:34:06 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 00:34:07 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	set_spec(const char **f, t_printf *flags, va_list args)
{
	if (**f == 's' || **f == 'S' || **f == 'p' || **f == 'd' || **f == 'D' ||
		**f == 'i' || **f == 'o' || **f == 'O' || **f == 'u' || **f == 'U' ||
		**f == 'x' || **f == 'X' || **f == 'c' || **f == 'C' || **f == '%')
		flags->spec = **f;
	else
		return (-1);
	(*f)++;
	if (flags->spec == '%')
	{
		handle_percent(flags);
		return (1);
	}
	if (flags->spec == 'U' || flags->spec == 'O' || flags->spec == 'D')
	{
		flags->is_long = 1;
		flags->is_short = 0;
		flags->is_int = 0;
	}
	return (do_conversion(flags, args));
}

int	set_length(const char **f, t_printf *flags, va_list args)
{
	if (**f == 'h' && *(*f + 1) == 'h')
		flags->is_char = 1;
	else if (**f == 'l' && *(*f + 1) == 'l')
		flags->is_longlong = 1;
	else if (**f == 'j')
		flags->intmax = 1;
	else if (**f == 'z')
		flags->is_sizet = 1;
	else if (**f == 'h')
		flags->is_short = 1;
	else if (**f == 'l')
		flags->is_long = 1;
	if (flags->is_short == 1 || flags->is_long == 1 || flags->intmax == 1 ||
		flags->is_sizet == 1)
	{
		flags->is_int = 0;
		(*f)++;
	}
	else if (flags->is_char == 1 || flags->is_longlong == 1)
	{
		flags->is_int = 0;
		(*f) += 2;
	}
	return (set_spec(f, flags, args));
}

int	set_prec(const char **f, t_printf *flags, va_list args)
{
	if (**f == '.')
	{
		(*f)++;
		if (ft_isdigit(**f))
		{
			flags->prec = ft_atoi(*f);
			while (ft_isdigit(**f))
				(*f)++;
		}
		else
			flags->prec = 0;
		flags->prec_set = 1;
	}
	return (set_length(f, flags, args));
}

int	set_width(const char **f, t_printf *flags, va_list args)
{
	int length;

	length = 0;
	if (flags->space && flags->pad)
		flags->pad = 0;
	if (flags->showsign && flags->space)
		flags->space = 0;
	if (ft_isdigit(**f))
	{
		flags->width = ft_atoi(*f);
		while (ft_isdigit(**f))
			(*f)++;
	}
	if (set_prec(f, flags, args) == -1)
		length = -1;
	else
		length = flags->length;
	return (length);
}

int	set_flags(const char **f, va_list args)
{
	t_printf	*flags;
	int			length;

	flags = init_flags();
	while (**f == '#' || **f == '-' || **f == '+' || **f == ' ' || **f == '0')
	{
		if (**f == '#')
			flags->alt = 1;
		else if (**f == '-')
			flags->left = 1;
		else if (**f == ' ')
			flags->space = 1;
		else if (**f == '+')
			flags->showsign = 1;
		else if (**f == '0')
			flags->pad = 1;
		(*f)++;
	}
	if ((length = set_width(f, flags, args)) == -1)
	{
		free(flags);
		return (-1);
	}
	free(flags);
	return (length);
}
