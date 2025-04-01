/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:07:27 by dmontesd          #+#    #+#             */
/*   Updated: 2025/04/01 21:18:17 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "writer.h"

int	ft_printf(const char *format, ...)
{
	static t_writer			buf_out;
	va_list					ap;
	int						return_value;
	t_parser				parser;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	return_value = parser_parse_and_write(&parser, format, &ap, &buf_out);
	va_end(ap);
	return (return_value);
}
