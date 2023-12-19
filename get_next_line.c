/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:39:11 by ttreichl          #+#    #+#             */
/*   Updated: 2023/12/13 19:03:15 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
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
	{
		free (string);
		return (NULL);
	}
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
	if (string[i] == '\n' && string[i])
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
	while (bytread > 0)
	{
		bytread = read(fd, buf, BUFFER_SIZE);
		if (bytread == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[bytread] = '\0';
		string = join_buf(buf, string);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (string);
}

char	*get_next_line(int fd)
{
	static char		*buf;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
	{
		if (buf != NULL)
			free(buf);
		buf = NULL;
		return (0);
	}
	next_line = NULL;
	buf = read_file(fd, buf);
	if (buf == NULL)
		return (NULL);
	next_line = ft_get_line(buf);
	buf = just_rest(buf);
	return (next_line);
}
/*
int main(void)
{
	char *line;
	int fd1;


	fd1 = open("karmine.txt", O_RDONLY);

	if (fd1 == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return 1;
	}
	//1
	line = get_next_line(fd1);
	printf("(%s)", line);
	//2
	line = get_next_line(fd1);
	printf("(%s)", line);
	if (BUFFER_SIZE > 100) {
		char *temp;
		do {
			temp = get_next_line(fd1);
			free(temp);
		} while (temp != NULL);
	}
	//3
	line = get_next_line(fd1);
	printf("(%s)", line);
	close(fd1);

	fd1 = open("karmine.txt", O_RDONLY);
	//4
	line = get_next_line(fd1);
	printf("(%s)", line);
	//5
	line = get_next_line(fd1);
	printf("(%s)", line);
	//6
	line = get_next_line(fd1);
	printf("(%s)", line);
	//7
	line = get_next_line(fd1);
	printf("(%s)", line);
	//8
	line = get_next_line(fd1);
	printf("(%s)", line);

	close(fd1);

	return 0;
}

*/