/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:06:15 by dmontesd          #+#    #+#             */
/*   Updated: 2025/02/05 23:41:15 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "parser.h"
#include "libft.h"
#include "output_buffer.h"

#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_SPACE 16

void	parser_write_char(t_parser *p)
{
	unsigned char c;

	c = (unsigned char)va_arg(*p->ap, int);
	output_buffer_putchar(p->output_buffer, c);
}

bool	parser_write_token(t_parser *p)
{
	int	result;

	result = -1;
	if (p->token_meta.specifier == 'c')
		parser_write_char(p);
	else if (p->token_meta.specifier == 's')
		(void) p;
	else if (p->token_meta.specifier == 'p')
		(void) p;
	else if (p->token_meta.specifier == 'd')
		(void) p;
	else if (p->token_meta.specifier == 'i')
		(void) p;
	else if (p->token_meta.specifier == 'u')
		(void) p;
	else if (p->token_meta.specifier == 'x')
		(void) p;
	else if (p->token_meta.specifier == 'X')
		(void) p;
	else if (p->token_meta.specifier == '%')
		(void) p;
	else
		return (false);
	return (true);
}

/*
 * Returns the amount of chars consumed.
 */
int parse_positive_int(const char *str, int *n)
{
	int	i;

	n = 0;
	i = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		*n *= 10;
		*n += (*str - '0');
		++i;
	}
	return (i);
}

static bool	parser_parse_conversion_specifier(t_parser *p)
{
	static const char	specifier_list[] = "cspdiuxX%";
	const char			*found;
	char				specifier;

	specifier = -1;
	found = ft_strchr(specifier_list, p->format[p->index]);
	if (found != NULL)
		specifier = *found;
	p->token_meta.specifier = specifier;
	return (found != NULL);
}

/*
 * Returns:
 * 	 n if width set on format
 * 	-1 if * flag
 * 	-2 if not set
 */
static void	parser_parse_precision(t_parser *p)
{
	int	precision;

	precision = -2;
	if (p->format[p->index] == '.')
	{
		if (p->format[p->index] == '*') 
		{
			precision = -1;
			++p->index;
		}
		else
			p->index += parse_positive_int(p->format + p->index, &precision);
	}
	p->token_meta.precision = precision;
}

/*
 * Sets width to:
 * 	+n if width set on format
 * 	 0 if not set or set to 0 on format
 * 	-1 if * flag
 */
static void	parser_parse_width(t_parser *p)
{
	int	width;

	width = 0;
	if (p->format[p->index] == '*')
	{
		width = -1;
		++p->index;
	}
	else
		p->index += parse_positive_int(p->format + p->index, &width);
	p->token_meta.width = width;
}

static void	parser_parse_flags(t_parser *p)
{
	static const char	flag_list[] = "-+0# ";
	int					flags;
	char				*found;

	flags = 0;
	found = ft_strchr(flag_list, p->format[p->index]);
	while (found != NULL)
	{
		flags |= 1 << (found - flag_list + 1);
		++p->index;
		found = ft_strchr(flag_list, p->format[p->index]);
	}
	p->token_meta.flags = flags;
}

static void	parser_prune_flags(t_parser *p)
{
	if (p->token_meta.flags & (FLAG_ZERO | FLAG_MINUS))
		p->token_meta.flags &= ~FLAG_ZERO;
	if (p->token_meta.flags & (FLAG_PLUS | FLAG_SPACE))
		p->token_meta.flags &= ~FLAG_SPACE;
	if (p->token_meta.precision == -2 && (p->token_meta.flags & FLAG_ZERO))
		p->token_meta.flags &= ~FLAG_ZERO;
}

int	parser_expand_token(t_parser *p)
{
	parser_parse_flags(p);
	parser_parse_width(p);
	parser_parse_precision(p);
	parser_prune_flags(p);
	if (!parser_parse_conversion_specifier(p))
		return (-1);
	parser_write_token(p);
}

int	parser_parse_and_write(
		t_parser *parser,
		const char *format_str,
		va_list *params,
		t_output_buffer *buf_out
) {
	parser->output_buffer = buf_out;
	parser->ap = params;
	parser->index = 0;
	parser->format = format_str;
	parser->ap = params;
	output_buffer_reset(parser->output_buffer);
	while (parser->format[parser->index] != '\0')
	{
		if (parser->format[parser->index] != '%')
		{
			output_buffer_putchar(
				parser->output_buffer,
				parser->format[parser->index]
				);
		}
		else
			parser_expand_token(parser); // FIXME: If it fails, write % and continue
	}
	output_buffer_flush(parser->output_buffer);
	return (parser->output_buffer->n_written);
}
