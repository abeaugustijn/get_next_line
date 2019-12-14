/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:26:21 by aaugusti          #+#    #+#             */
/*   Updated: 2019/12/14 19:57:10 by aaugusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdbool.h>
# include <unistd.h>

typedef struct	s_string
{
	char	*str;
	size_t	len;
}				t_string;

int		get_next_line(int fd, char **line);

/*
**	Utils
*/

bool	gnl_haschar(char *buf, char c);
char	*gnl_allocate(char *buf, size_t n, size_t *res_len);
bool	gnl_pushback(t_string *res, char *buf, size_t n);
void	gnl_shiftbuf(char *buf, size_t n);

#endif
