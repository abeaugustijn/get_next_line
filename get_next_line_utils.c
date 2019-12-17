/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:36:05 by aaugusti          #+#    #+#             */
/*   Updated: 2019/12/17 11:11:49 by aaugusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

/*
**	This function returns a boolean based on whether the string 'str' contains
**	the char 'c'.
**
**	@param	char *str	"the string to check"
**	@param	char c		"the char to check for"
**
**	@return	bool res	"true or false based on wheter 'c' is in 'buf'"
*/

bool			gnl_haschar(char *str, char c)
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

/*
**	This is a functions which counts the amount of chars in a string until a
**	'\0' or a '\n' is encountered.
**
**	@param	char* str	"the string to get the length of"
**
**	@return	size_t res	"the amount of chars before the first '\0' or '\n'.
*/

size_t			gnl_strlenc(char *str, char c)
{
	size_t	res;

	res = 0;
	while (str[res] && str[res] != c)
		res++;
	return (res);
}

int				gnl_shiftbuf(char *buf, size_t n)
{
	size_t	start;
	size_t	i;

	start = 0;
	while (buf[start] != '\n')
		start++;
	/*if (*buf != '\n')*/
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
	return (1);
}

bool			gnl_strlcat(char **res, char *buf)
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

char	*gnl_strdup(char *buf, bool *force_return)
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
		*force_return = true;
	if (len > 0)
		gnl_shiftbuf(buf, gnl_strlenc(buf, 0));
	return (res);
}
