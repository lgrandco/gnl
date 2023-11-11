/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:48:59 by legrandc          #+#    #+#             */
/*   Updated: 2023/11/12 00:40:12 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	init_str(t_string *string)
{
	string->default_size = BUFFER_SIZE * 10;
	string->content = malloc(string->default_size);
	string->max_size = string->default_size;
	string->len = 0;
}

int	find_nl(char *s, ssize_t *len)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (*len += i + 1, 1);
	*len += i;
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

int	read_file(int fd, t_string *string)
{
	ssize_t	read_ret;
	ssize_t	line_len;
	char	*tmp;

	line_len = 0;
	read_ret = 1;
	while (!find_nl(string->content + line_len, &line_len) && read_ret)
	{
		if (string->len + BUFFER_SIZE >= string->max_size)
		{
			tmp = malloc(string->max_size + string->default_size);
			if (!tmp)
				return (-1);
			ft_memcpy(tmp, string->content, string->len + 1);
			free(string->content);
			string->content = tmp;
			string->max_size += string->default_size;
		}
		read_ret = read(fd, string->content + string->len, BUFFER_SIZE);
		string->len += read_ret;
		string->content[string->len] = 0;
	}
	return (line_len);
}

char	*get_next_line(int fd)
{
	ssize_t		line_len;
	char		*ret;
	t_string	string;
	static char	*save[FD];

	if (fd > FD || read(fd, "", 0) == -1 || BUFFER_SIZE < 1)
		return (NULL);
	if (!save[fd])
	{
		save[fd] = malloc(BUFFER_SIZE + 1);
		*save[fd] = 0;
	}
	init_str(&string);
	while (save[fd][string.len])
		string.len++;
	ft_memcpy(string.content, save[fd], string.len + 1);
	line_len = read_file(fd, &string);
	if (!*string.content || line_len == -1)
		return (free(string.content), NULL);
	ret = malloc(line_len + 1);
	if (!ret)
		return (free(string.content), NULL);
	ft_memcpy(ret, string.content, line_len);
	ft_memcpy(save[fd], string.content + line_len, string.len - line_len + 1);
	return (free(string.content), ret[line_len] = 0, ret);
}
// #include <fcntl.h>
// #include <stdio.h>

// int	main(int ac, char **av)
// {
// 	int		fd;
// 	char	*s;
// 	int		i;

// 	(void)ac;
// 	i = 0;
// 	while (i++ < 1000)
// 		fd = open(av[1], O_RDONLY);
// 	s = "";
// 	i = 0;
// 	while (s)
// 	{
// 		s = get_next_line(fd);
// 		printf("%s---", s);
// 		free(s);
// 	}
// 	printf("%d\n", fd);
// 	s = get_next_line(fd);
// 	printf("%s---", s);
// }