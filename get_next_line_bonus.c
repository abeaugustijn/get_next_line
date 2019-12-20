/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:26:00 by aaugusti          #+#    #+#             */
/*   Updated: 2019/12/20 12:58:18 by aaugusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int			get_next_line(int fd, char **line)
{
	static char	buf[20000][BUFFER_SIZE + 1];
	ssize_t		readret;
	char		*res;
	bool		force_ret;

	readret = 0;
	force_ret = false;
	res = gnl_strdup(buf[fd], &force_ret);
	while (true)
	{
		if (force_ret ? false : gnl_strlcat(&res, buf[fd]))
			return (-1);
		*line = res;
		if (gnl_haschar(buf[fd], '\n') || force_ret)
			return (gnl_shiftbuf(buf[fd], gnl_strlenc(buf[fd], 0), 1));
		readret = read(fd, buf[fd], BUFFER_SIZE);
		if (readret < 0)
			return (-1);
		if (!readret)
			return (gnl_shiftbuf(buf[fd], gnl_strlenc(buf[fd], 0), 0));
		buf[fd][readret] = 0;
	}
	return (1);
}
