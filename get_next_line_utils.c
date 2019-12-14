/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:36:05 by aaugusti          #+#    #+#             */
/*   Updated: 2019/12/14 20:00:17 by aaugusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

bool	gnl_haschar(char *buf, char c)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buf[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	gnl_getlinelen(char *str, size_t n)
{
	size_t	res;

	res = 0;
	while (str[res] != '\n' && res < n)
		res++;
	return (res);
}

void	gnl_shiftbuf(char *buf, size_t n)
{
	size_t	start;
	size_t	i;

	start = 0;
	while (buf[start] != '\n')
		start++;
	start++;
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
}

bool	gnl_pushback(t_string *res, char *buf, size_t n)
{
	char	*new;
	size_t	new_len;
	size_t	i;

	if (!res->str)
		res->str = gnl_allocate(buf, n, &(res->len));
	else
	{
		new_len = (res->len + gnl_getlinelen(buf, n)) * sizeof(char);
		new = (char *)malloc(new_len + 1 * sizeof(char));
		if (!new)
			return (1);
		new[new_len] = 0;
		i = 0;
		while (i < res->len)
		{
			new[i] = res->str[i];
			i++;
		}
		while (i < new_len)
		{
			new[i] = buf[i - res->len];
			i++;
		}
		free(res->str);
		res->str = new;
		res->len = new_len;
	}
	return (0);
}

char	*gnl_allocate(char *buf, size_t n, size_t *res_len)
{
	size_t	len;
	char	*res;

	len = 0;
	while (len < n && buf[len] != '\n')
		len++;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = 0;
	*res_len = len;
	while(len > 0)
	{
		res[len - 1] = buf[len - 1];
		len--;
	}
	return (res);
}
