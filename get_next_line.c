/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:26:00 by aaugusti          #+#    #+#             */
/*   Updated: 2019/12/14 20:07:56 by aaugusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

int	get_next_line(int fd, char **line)
{
	static char	buf[BUFFER_SIZE + 1];
	ssize_t		readret;
	t_string	res;

	res.str = NULL;
	res.len = 0;
	while (!gnl_haschar(buf, '\n'))
	{
		readret = read(fd, buf, BUFFER_SIZE);
		if (readret <= 0)
			return (!readret ? 0 : -1);
		if (gnl_pushback(&res, buf, (size_t)readret))
			return (-1);
	}
	*line = res.str;
	gnl_shiftbuf(buf, readret);
	return (1);
}
