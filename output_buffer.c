/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:59:34 by dmontesd          #+#    #+#             */
/*   Updated: 2025/02/05 19:07:48 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "output_buffer.h"

/*
 * Does not zero initialize the buffer but the variables.
 */
void	output_buffer_reset(t_output_buffer *w)
{
	w->index = 0;
	w->error = 0;
	w->n_written = 0;
}

bool	output_buffer_write(t_output_buffer *w, const char *mem, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && output_buffer_putchar(w, mem[i]))
		++i;
	return (w->error < 0);
}

bool	output_buffer_write_str(t_output_buffer *w, const char *str)
{
	while (*str != '\0' && output_buffer_putchar(w, *str))
		++str;
	return (w->error < 0);
}

int	output_buffer_flush(t_output_buffer *w)
{
	size_t	n_written;
	size_t	total_written;

	total_written = 0;
	while (total_written < w->index)
	{
		n_written = write(STDOUT_FILENO, w->buf + total_written,
				w->index - total_written);
		if (n_written < 0)
			return (w->error = n_written, n_written);
		total_written += n_written;
	}
	w->index = 0;
	w->n_written += total_written;
	return (total_written);
}

bool	output_buffer_is_full(t_output_buffer *w)
{
	return (w->index == BUF_SIZE);
}

bool	output_buffer_putchar(t_output_buffer *w, char c)
{
	if (output_buffer_is_full(w) && output_buffer_flush(w) < 0)
		return (false);
	w->buf[w->index] = c;
	w->index++;
	return (true);
}
