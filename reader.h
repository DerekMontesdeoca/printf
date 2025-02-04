/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:05:09 by dmontesd          #+#    #+#             */
/*   Updated: 2025/02/04 17:07:38 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

#include <stdarg.h>

typedef struct s_reader
{
	int			index;
	int			format;
	va_list		*ap;
}	t_reader;



#endif
