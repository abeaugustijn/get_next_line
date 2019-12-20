/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:26:00 by aaugusti          #+#    #+#             */
/*   Updated: 2019/12/20 12:44:12 by aaugusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

int			get_next_line(int fd, char **line)
{
	static char	buf[BUFFER_SIZE + 1];
	ssize_t		readret;
	char		*res;
	bool		force_ret;

	readret = 0;
	force_ret = false;
	res = gnl_strdup(buf, &force_ret);
	while (true)
	{
		if (force_ret ? false : gnl_strlcat(&res, buf))
			return (-1);
		*line = res;
		if (gnl_haschar(buf, '\n') || force_ret)
			return (gnl_shiftbuf(buf, gnl_strlenc(buf, 0), 1));
		readret = read(fd, buf, BUFFER_SIZE);
		if (readret < 0)
			return (-1);
		if (!readret)
			return (gnl_shiftbuf(buf, gnl_strlenc(buf, 0), 0));
		buf[readret] = 0;
	}
	return (1);
}
