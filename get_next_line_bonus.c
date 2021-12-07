/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:35:00 by yunselee          #+#    #+#             */
/*   Updated: 2021/06/26 18:40:59 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

static int	free_ret_error(char **str)
{
	free(*str);
	*str = NULL;
	return (ERROR);
}

static int	copy_line(char **line, char **str_fd)
{
	int		size;
	int		i;
	int		ret;

	i = 0;
	size = 0;
	while ((*str_fd)[size] != '\0' && (*str_fd)[size] != '\n')
		size++;
	if ((*line = (char *)malloc(size + 1)) == NULL)
		return (free_ret_error(str_fd));
	(*line)[0] = '\0';
	ft_strlcat(*line, *str_fd, size + 1);
	ret = ((*str_fd)[size] == '\n') ? SUCCESS : FILE_EOF;
	if (ret == SUCCESS)
		ft_strcpy(*str_fd, (*str_fd + size + 1));
	if (ret == FILE_EOF && *str_fd)
	{
		free(*str_fd);
		*str_fd = NULL;
	}
	return (ret);
}

int			get_next_line(int fd, char **line)
{
	static char	*str[OPEN_MAX];
	long long	len;
	char		buffer[BUFFER_SIZE + 1];
	char		*temp;

	len = 0;
	if (fd < 0 || fd >= OPEN_MAX || line == NULL || BUFFER_SIZE <= 0)
		return (ERROR);
	if (str[fd] == NULL && (str[fd] = ft_strjoin("", "")) == NULL)
		return (ERROR);
	while (ft_strchr(str[fd], '\n') == NULL &&
		((len = read(fd, buffer, BUFFER_SIZE)) > 0))
	{
		buffer[len] = '\0';
		if ((temp = ft_strjoin(str[fd], buffer)) == NULL)
			return (free_ret_error(&str[fd]));
		free(str[fd]);
		str[fd] = temp;
	}
	if (len < 0)
		return (free_ret_error(&str[fd]));
	return (copy_line(line, &str[fd]));
}