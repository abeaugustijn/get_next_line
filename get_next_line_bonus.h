/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:26:21 by aaugusti          #+#    #+#             */
/*   Updated: 2019/12/20 12:59:21 by aaugusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdbool.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		get_next_line(int fd, char **line);

/*
**	Utils
*/

bool	gnl_haschar(char *buf, char c);
char	*gnl_strdup(char *buf, bool *force_return);
bool	gnl_strlcat(char **res, char *buf);
size_t	gnl_strlenc(char *str, char c);
int		gnl_shiftbuf(char *buf, size_t n, int to_return);

#endif
