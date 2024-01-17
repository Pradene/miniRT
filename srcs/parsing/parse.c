/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:25:59 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 12:26:23 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

static void	replace_newline(char **line)
{
	if ((*line)[ft_strlen(*line) - 1] == '\n')
		(*line)[ft_strlen(*line) - 1] = '\0';
}

static char	**read_file(int fd)
{
	int		i;
	char	*line;
	char	**tmp;
	char	**file;

	i = -1;
	file = NULL;
	line = gnl(fd);
	if (!line)
		return (NULL);
	while (line)
	{
		tmp = NULL;
		replace_newline(&line);
		tmp = malloc(sizeof(char *) * ((++i + 1) + 1));
		if (!tmp)
			return (string_array_free(file), free(line), NULL);
		string_array_copy(tmp, file);
		free(file);
		tmp[i] = line;
		tmp[i + 1] = NULL;
		file = tmp;
		line = gnl(fd);
	}
	return (file);
}

int	parsing(char *path)
{
	int		fd;
	char	**file;
	t_data	*data;

	data = get_data();
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		return (printf("Error: invald file\n"), 1);
	}
	file = read_file(fd);
	if (!file)
	{
		close(fd);
		return (printf("Error: couldn't read %s file\n", path), 1);
	}
	if (create_objects(file))
	{
		string_array_free(file);
		close(fd);
		return (printf("Error: couldn't parse %s file\n", path), 1);
	}
	string_array_free(file);
	close(fd);
	return (0);
}
