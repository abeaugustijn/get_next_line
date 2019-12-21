/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:26:00 by aaugusti          #+#    #+#             */
/*   Updated: 2019/12/21 10:41:48 by aaugusti         ###   ########.fr       */
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
		if (!force_ret)
			if (gnl_strlcat(&res, buf))
				return (-1);
		*line = res;
		if (gnl_hasnewline(buf) || force_ret)
			return (gnl_shiftbuf(buf, 1));
		readret = read(fd, buf, BUFFER_SIZE);
		if (readret < 0)
			return (-1);
		if (!readret)
			return (gnl_shiftbuf(buf, 0));
		buf[readret] = 0;
	}
	return (1);
}
