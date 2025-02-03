/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:07:27 by dmontesd          #+#    #+#             */
/*   Updated: 2025/02/03 14:00:23 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "libft.h"

#define BUF_SIZE 1024
#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_SPACE 16

static int	parse_flags(const char *format, int *i)
{
	static const char	flag_list[] = "-+0# ";
	int					flags;
	char				*found;

	flags = 0;
	found = ft_strchr(flag_list, format[*i]);
	while (found != NULL)
	{
		flags |= 1 << (found - flag_list + 1);
		++*i;
		found = ft_strchr(flag_list, format[*i]);
	}
	return (flags);
}

static int	prune_flags(int flags, bool has_precision)
{
	if (flags & (FLAG_ZERO | FLAG_MINUS))
		flags &= ~FLAG_ZERO;
	if (flags & (FLAG_PLUS | FLAG_SPACE))
		flags &= ~FLAG_SPACE;
	if (has_precision && flags & FLAG_ZERO)
		flags &= ~FLAG_ZERO;
	return (flags);
}

static int	parse_width(const char *format, int *i)
{
	int	width;

	width = ft_atoi(format + *i);
	while (ft_isdigit(format[*i]))
		++*i;
	return (width);
}

/*
 * Returns:
 * 	-1 if not set 
 * 	-2 if error
 */
static int	parse_precision(const char *format, int *i)
{
	int	precision;

	precision = -1;
	if (format[*i] == '.')
	{
		precision = ft_atoi(format + *i);
		if (precision < 0)
			precision = -2;
	}
	return (precision);
}

/*
 * Returns -1 on error.
 */
static char	parse_conversion_specifier(const char *format, int *i)
{
	static const char	specifier_list[] = "cspdiuxX%";
	const char			*found;
	char				specifier;

	specifier = -1;
	found = ft_strchr(specifier_list, format[*i]);
	if (found != NULL)
		specifier = *found;
	return (specifier);
}

int	parse_conversion_token(const char *format, va_list ap, int *i, char *buffer)
{
	parse_flags(format, i);
	parse_width(format, i);
	parse_precision(format, i);
	parse_conversion_specifier(format, i);
	write_buf();
}

int	execute_format(const char *format, va_list ap)
{
	static char	buffer[BUF_SIZE]__attribute__((aligned(BUF_SIZE)));
	int			i;
	int			counter;
	int			n_written;
	
	i = 0;
	counter = 0;
	while (format[i] != '\0')
	{
		while (format[i] != '%' && format[i] != '\0')
		{
			n_written = write_buf(buffer, format[i++]);
			if (n_written < 0)
				return (n_written);
			counter += n_written;
		}
		if (format[i] == '%')
		{
			n_written = parse_conversion_token(format, ap, &i, buffer);
			if (n_written < 0)
				return (n_written);
			counter += n_written;
		}
	}
	return (counter);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		return_value;

	va_start(ap, format);
	return_value = execute_format(format, ap);
	va_end(ap);
	return (return_value);
}


