/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:26:00 by aaugusti          #+#    #+#             */
/*   Updated: 2019/12/17 11:06:41 by aaugusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

int	get_next_line(int fd, char **line)
{
	static char	buf[BUFFER_SIZE + 1];
	ssize_t		readret;
	char		*res;
	bool		did_run;
	bool		force_return;

	readret = 0;
	force_return = false;
	res = gnl_strdup(buf, &force_return);
	did_run = false;
	while (true)
	{
		if (gnl_strlcat(&res, buf))
			return (-1);
		*line = res;
		if (gnl_haschar(buf, '\n') || force_return)
			return (gnl_shiftbuf(buf, gnl_strlenc(buf, 0)));
		readret = read(fd, buf, BUFFER_SIZE);
		if (readret < 0)
			return (-1);
		if(!readret)
			return ((int)did_run);
		buf[readret] = 0;
		did_run = true;
	}
	return (1);
}
