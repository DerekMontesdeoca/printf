#ifndef OUTPUT_BUFFER_H
# define OUTPUT_BUFFER_H

#include <stddef.h>
#include <stdbool.h>

# define BUF_SIZE 2048

typedef struct	s_output_buffer
{
	size_t			index;	
	unsigned char	buf[BUF_SIZE];
	int				error;
	int				n_written;
}	t_output_buffer;

bool	output_buffer_write(t_output_buffer *w, const char *mem, size_t size);

bool 	output_buffer_write_str(t_output_buffer *w, const char *str);

int		output_buffer_flush(t_output_buffer *w);

bool	output_buffer_is_full(t_output_buffer *w);

bool	output_buffer_putchar(t_output_buffer *w, char c);

void	output_buffer_reset(t_output_buffer *w);

#endif
