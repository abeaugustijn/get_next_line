/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:36:05 by aaugusti          #+#    #+#             */
/*   Updated: 2019/12/20 16:43:38 by aaugusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

bool		gnl_haschar(char *str, char c)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE && str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t		gnl_strlenc(char *str, char c)
{
	size_t	res;

	res = 0;
	while (str[res] && str[res] != c)
		res++;
	return (res);
}

int			gnl_shiftbuf(char *buf, size_t n, int to_return)
{
	size_t	start;
	size_t	i;

	start = 0;
	while (buf[start] != '\n' && start < n)
		start++;
	start++;
	if (!n && buf[0] == '\n')
		n++;
	i = 0;
	while (start < n)
	{
		buf[i] = buf[start];
		i++;
		start++;
	}
	while (i < n)
	{
		buf[i] = 0;
		i++;
	}
	return (to_return);
}

bool		gnl_strlcat(char **res, char *buf)
{
	size_t	og_len;
	size_t	buf_len;
	size_t	i;
	char	*old_res;

	og_len = gnl_strlenc(*res, '\n');
	buf_len = gnl_strlenc(buf, '\n');
	old_res = *res;
	*res = (char *)malloc((og_len + buf_len + 1) * sizeof(char));
	if (!*res)
		return (true);
	(*res)[og_len + buf_len] = 0;
	i = 0;
	while (i < og_len)
	{
		(*res)[i] = old_res[i];
		i++;
	}
	free(old_res);
	while (i < og_len + buf_len)
	{
		(*res)[i] = buf[i - og_len];
		i++;
	}
	return (false);
}

char		*gnl_strdup(char *buf, bool *force_ret)
{
	size_t	len;
	size_t	i;
	char	*res;

	len = 0;
	while (buf[len] && buf[len] != '\n')
		len++;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = 0;
	i = 0;
	while (i < len)
	{
		res[i] = buf[i];
		i++;
	}
	if (gnl_haschar(buf, '\n'))
		*force_ret = true;
	else if (len > 0)
		gnl_shiftbuf(buf, gnl_strlenc(buf, 0), 0);
	return (res);
}
