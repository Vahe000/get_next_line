/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:04:57 by vasargsy          #+#    #+#             */
/*   Updated: 2022/04/21 14:17:37 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

char	*fill_line(char *line, int fd, int len)
{
	char	buff[BUFFER_SIZE + 1];

	while (1)
	{
		len = read(fd, buff, BUFFER_SIZE);
		buff[len] = 0;
		if (len == -1)
			return (0);
		if (!line)
			line = ft_strdup(buff);
		else
			line = ft_strjoin(line, buff);
		if (ft_strchr(buff, '\n') || len == 0)
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	int			len;
	int			line_len;
	char		*temp;
	char		*ret_line;

	len = 1;
	line[fd] = fill_line(line[fd], fd, len);
	if (!line[fd])
		return (0);
	line_len = ft_strlen(line[fd]) - ft_strlen(ft_strchr(line[fd], '\n')) + 1;
	ret_line = ft_substr(line[fd], 0, line_len);
	temp = line[fd];
	line[fd] = ft_substr(temp, line_len, ft_strlen(line[fd]) - line_len);
	free(temp);
	return (ret_line);
}

int main()
{
    int fd1;
	int fd2;

    fd1 = open("test.txt", O_RDONLY);
    printf("%s", get_next_line(fd1));
    fd2 = open("test2.txt", O_RDONLY);
	printf("%s", get_next_line(fd1));
    printf("%s", get_next_line(fd2));
}
