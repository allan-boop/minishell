/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:37:55 by gdoumer           #+#    #+#             */
/*   Updated: 2024/01/24 12:23:48 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*clean_stash(int fd, char **stash)
{
	int		end;
	char	*line;
	char	*time;

	end = 0;
	if (!stash[fd])
		return (NULL);
	while (stash[fd][end] && stash[fd][end] != '\n')
		end++;
	if (stash[fd][end] == '\n')
		end++;
	line = ft_substr_gnl(stash[fd], 0, end);
	time = ft_substr_gnl(stash[fd], end, ft_strlen_gnl(&stash[fd][end]));
	free(stash[fd]);
	stash[fd] = time;
	if (!line || !time || ft_strlen_gnl(line) == 0)
	{
		free(stash[fd]);
		free(line);
		stash[fd] = NULL;
		return (NULL);
	}
	return (line);
}

char	*add_buf_to_stash(int fd, char *buf, char **stash)
{
	char	*new_stash;

	if (!stash[fd])
		stash[fd] = ft_strdup_gnl(buf);
	else
	{
		new_stash = ft_strjoin_gnl(stash[fd], buf);
		free(stash[fd]);
		stash[fd] = new_stash;
	}
	return (stash[fd]);
}

char	*read_and_buf(int fd, char *buf, char **stash)
{
	int			readed;

	readed = 1;
	if (BUFFER_SIZE <= 0)
		return (NULL);
	while (readed >= 0)
	{
		ft_bzero_gnl(buf, BUFFER_SIZE + 1);
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed < 0)
		{
			free(stash[fd]);
			return (NULL);
		}
		stash[fd] = add_buf_to_stash(fd, buf, stash);
		if (stash[fd] && (ft_strchr_gnl(stash[fd], '\n') || readed == 0))
			return (stash[fd]);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*final_line;
	static char	*stash[1024];
	char		*tmp_buf;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	tmp_buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp_buf)
		return (NULL);
	stash[fd] = read_and_buf(fd, tmp_buf, stash);
	free(tmp_buf);
	if (!stash[fd])
		return (NULL);
	final_line = clean_stash(fd, stash);
	return (final_line);
}
