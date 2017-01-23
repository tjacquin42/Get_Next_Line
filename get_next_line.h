/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquin <tjacquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 15:33:36 by tjacquin          #+#    #+#             */
/*   Updated: 2017/01/23 18:49:23 by tjacquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>

# define ERROR			-1
# define END_OF_LINE	1
# define END_OF_FILE	0
# define BUFF_SIZE		32

typedef struct		s_f
{
	int				fd;
	int				eof;
	char			*data;
	struct s_f		*next;
}					t_f;

int					get_next_line(const int fd, char **line);

#endif
