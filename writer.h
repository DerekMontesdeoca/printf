#ifndef WRITER_H
# define WRITER_H

#include <stddef.h>
#include <stdbool.h>

# define BUF_SIZE 4096

typedef struct	s_writer
{
	size_t			index;	
	unsigned char	buf[BUF_SIZE];
	int				error;
}	t_writer;


void	writer_make(t_writer *w);

bool	writer_write(t_writer *w, const char *mem, size_t size);

bool 	writer_write_str(t_writer *w, const char *str);

int		writer_flush(t_writer *w);

bool	writer_is_full(t_writer *w);

bool	writer_putchar(t_writer *w, char c);

#endif
