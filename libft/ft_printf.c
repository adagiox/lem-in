/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:32:50 by erintala          #+#    #+#             */
/*   Updated: 2017/10/03 00:32:57 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

const		t_type g_dispatch_table[] = {
	{'s', convert_s},
	{'S', convert_ws},
	{'p', convert_u},
	{'d', convert_i},
	{'D', convert_i},
	{'i', convert_i},
	{'o', convert_u},
	{'O', convert_u},
	{'u', convert_u},
	{'U', convert_u},
	{'x', convert_u},
	{'X', convert_u},
	{'c', convert_c},
	{'C', convert_c},
};

t_printf	*init_flags(void)
{
	t_printf *flags;

	flags = (t_printf *)malloc(sizeof(t_printf));
	flags->length = 0;
	flags->width = 0;
	flags->spec = '0';
	flags->pad_char = ' ';
	flags->prefix = '*';
	flags->prec = 1;
	flags->prec_set = 0;
	flags->is_short = 0;
	flags->is_char = 0;
	flags->is_long = 0;
	flags->is_longlong = 0;
	flags->is_sizet = 0;
	flags->intmax = 0;
	flags->alt = 0;
	flags->space = 0;
	flags->left = 0;
	flags->showsign = 0;
	flags->wide = 0;
	flags->pad = 0;
	flags->is_int = 1;
	return (flags);
}

int			do_conversion(t_printf *flags, va_list args)
{
	int i;

	i = 0;
	if (flags->spec == 'p')
	{
		flags->is_long = 1;
		flags->is_int = 0;
	}
	while (1)
	{
		if (flags->spec == g_dispatch_table[i].spec)
		{
			g_dispatch_table[i].func(flags, args);
			break ;
		}
		i++;
	}
	return (1);
}

int			vprintf(const char *f, va_list args)
{
	int length;

	length = 0;
	while (*f)
	{
		if (*f == '%')
		{
			f++;
			if ((length += set_flags(&f, args)) == -1)
				return (-1);
		}
		else
		{
			ft_putchar(*f);
			length++;
			f++;
		}
	}
	return (length);
}

int			ft_printf(const char *f, ...)
{
	int		done;
	va_list	args;

	va_start(args, f);
	done = vprintf(f, args);
	va_end(args);
	return (done);
}
