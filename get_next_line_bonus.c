/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:48:59 by legrandc          #+#    #+#             */
/*   Updated: 2023/11/14 20:42:58 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

void	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && i + 1 < size)
	{
		dst[i] = src[i];
		++i;
	}
	if (size)
		dst[i] = 0;
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
			tmp = malloc(string->max_size * 2);
			if (!tmp)
				return (-1);
			ft_strlcpy(tmp, string->content, string->len + 1);
			free(string->content);
			string->content = tmp;
			string->max_size *= 2;
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
	static char	save[FD][BUFFER_SIZE + 1];

	if (fd > FD || read(fd, "", 0) == -1 || BUFFER_SIZE < 1)
		return (NULL);
	string.max_size = BUFFER_SIZE + 1;
	string.content = malloc(string.max_size);
	if (!string.content)
		return (NULL);
	string.len = 0;
	while (save[fd][string.len])
		string.len++;
	ft_strlcpy(string.content, save[fd], string.len + 1);
	line_len = read_file(fd, &string);
	if (!*string.content || line_len == -1)
		return (free(string.content), NULL);
	ret = malloc(line_len + 1);
	if (!ret)
		return (free(string.content), NULL);
	ft_strlcpy(ret, string.content, line_len + 1);
	ft_strlcpy(save[fd], string.content + line_len, string.len - line_len + 1);
	return (free(string.content), ret);
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
// 	while (i++ < 10)
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
// 	free(s);
// }
