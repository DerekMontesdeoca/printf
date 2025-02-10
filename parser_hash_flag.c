/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hash_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:57:27 by dmontesd          #+#    #+#             */
/*   Updated: 2025/02/10 12:00:06 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"

void	alt_hex(t_parser *p, size_t len, bool upper)
{
	if (p->token_meta.flags & FLAG_HASH && len > 0)
	{
		writer_putchar(p->writer, '0');
		if (upper)
			writer_putchar(p->writer, 'X');
		else
			writer_putchar(p->writer, 'x');
	}
}
