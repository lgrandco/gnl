/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:51:59 by legrandc          #+#    #+#             */
/*   Updated: 2023/11/11 22:24:35 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define STRING_MAX_SIZE BUFFER_SIZE * 10

typedef struct s_string
{
	char	*content;
	size_t	len;
	size_t	max_len;
}			t_string;

/* FUNCTIONS */
char		*get_next_line(int fd);

#endif
