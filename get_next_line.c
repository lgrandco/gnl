/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:48:59 by legrandc          #+#    #+#             */
/*   Updated: 2023/11/09 20:44:53 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE] = {0};
	ssize_t		read_ret;
	char		*string;

	if (fd == -1 || read(fd, buff, 0) == -1)
		return (NULL);
	read_ret = 1;
	string = malloc(STRING_MAX_SIZE);
	if (!string)
		return (0);
	while (read_ret && !ft_memchr(buff, '\n', read_ret))
	{
		read_ret = read(fd, buff, BUFFER_SIZE);
		string = ft_st
	}
}
