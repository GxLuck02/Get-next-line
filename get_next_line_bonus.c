/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:46:05 by ttreichl          #+#    #+#             */
/*   Updated: 2023/12/13 19:07:49 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*just_rest(char *string)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (string[i] != '\n' && string[i])
		i++;
	if (!string[i])
	{
		free(string);
		return (NULL);
	}
	res = (char *)ft_calloc(((ft_strlen(string)- i + 1)), sizeof (char));
	if (!res)
		return (NULL);
	i++;
	j = 0;
	while (string[i])
		res[j++] = string[i++];
	res[j] = '\0';
	free (string);
	return (res);
}

char	*ft_get_line(char *string)
{
	char	*nextstring;
	int		i;

	i = 0;
	if (!string[i])
		return (NULL);
	while (string[i] && string[i] != '\n')
		i++;
	nextstring = (char *)ft_calloc((i + 2), sizeof (char));
	if (nextstring == NULL)
		return (NULL);
	i = 0;
	while (string[i] != '\n' && string[i])
	{
		nextstring[i] = string[i];
		i++;
	}
	if (string[i] == '\n')
	{
		nextstring[i] = string[i];
		i++;
	}
	nextstring[i] = '\0';
	return (nextstring);
}

char	*read_file(int fd, char *string)
{
	char	*buf;
	int		bytread;

	buf = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
		return (NULL);
	bytread = 1;
	while (!ft_strchr(string, '\n') && bytread != 0)
	{
		bytread = read(fd, buf, BUFFER_SIZE);
		if (bytread == -1)
		{
			free (buf);
			return (NULL);
		}
		buf[bytread] = '\0';
		string = join_buf(buf, string);
	}
	free (buf);
	return (string);
}

char	*get_next_line(int fd)
{
	static char		*buf[4096];
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
	{
		if (buf[fd] != NULL)
			free(buf[fd]);
		buf[fd] = NULL;
		return (0);
	}
	buf[fd] = read_file(fd, buf[fd]);
	if (!buf[fd])
		return (NULL);
	next_line = ft_get_line(buf[fd]);
	buf[fd] = just_rest(buf[fd]);
	return (next_line);
}
