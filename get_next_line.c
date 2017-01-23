/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquin <tjacquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 22:01:29 by tjacquin          #+#    #+#             */
/*   Updated: 2017/01/23 18:49:02 by tjacquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_f		*check_fd(int fd, t_f **struc)
{
	char	*buf;
	t_f		*new;

	buf = NULL;
	if (fd < 0 || read(fd, buf, 0) == -1)
		return (NULL);
	if (!*struc)
	{
		if (!(new = (t_f*)malloc(sizeof(t_f))))
			return (NULL);
		new->fd = fd;
		new->data = NULL;
		new->eof = 0;
		new->next = NULL;
		*struc = new;
		return (new);
	}
	new = *struc;
	if (!new)
		return (NULL);
	if (new->fd == fd)
		return (new);
	return (check_fd(fd, &new->next));
}

static int		endline(t_f *struc, char **line, int ret)
{
	char *cp;
	char *tmp;

	if ((cp = ft_strchr(struc->data, 0x0a)))
	{
		*cp = 0;
		if (!(tmp = ft_strdup(cp + 1)) ||
				!(*line = ft_strdup(struc->data)))
			return (ERROR);
		free(struc->data);
		if (!(struc->data = ft_strdup(tmp)))
			return (ERROR);
		free(tmp);
		return (END_OF_LINE);
	}
	else if (ret == 0 && (int)ft_strlen(struc->data) == 0)
		struc->eof = 1;
	else if (ret == 0 && (int)ft_strlen(struc->data) > 0)
	{
		if (!(*line = ft_strdup(struc->data)))
			return (ERROR);
		(struc->eof = 1) ? free(struc->data) : NULL;
		return (END_OF_LINE);
	}
	return (0);
}

static int		freejoin(char **dst, char *src)
{
	char	*tmp;

	if (!dst || !src || !*dst)
		return (0);
	if (!(tmp = ft_strjoin(*dst, src)))
		return (0);
	free(*dst);
	if (!(*dst = ft_strdup(tmp)))
		return (0);
	free(tmp);
	return (1);
}

static int		read_line(t_f *struc, char **line, char *buf)
{
	int		ret;
	int		is_endline;

	if (!struc)
		return (ERROR);
	while ((ret = read(struc->fd, buf, BUFF_SIZE)) || struc->eof == 0)
	{
		buf[ret] = 0;
		if (!struc->data)
		{
			if (!(struc->data = ft_strdup(buf)))
				return (ERROR);
		}
		else if (ret > 0)
		{
			if (!freejoin(&struc->data, buf))
				return (ERROR);
		}
		if ((is_endline = endline(struc, line, ret)) == END_OF_LINE)
			return (END_OF_LINE);
		else if (is_endline == ERROR)
			return (ERROR);
	}
	*line = NULL;
	return (END_OF_FILE);
}

int				get_next_line(const int fd, char **line)
{
	static t_f		*struc;
	t_f				*tmp;
	int				ret;
	char			*buf;

	if (!(buf = (char*)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (ERROR);
	if (!(tmp = check_fd(fd, &struc)))
		return (ERROR);
	ret = read_line(tmp, line, buf);
	free(buf);
	if (ret == END_OF_LINE)
		return (END_OF_LINE);
	else if (ret == ERROR)
		return (ERROR);
	else
		return (END_OF_FILE);
}
