/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:52:42 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/10 16:53:25 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	create_object_type(t_data *data, char **args, t_obj_type type)
{
	static int	(*func[])() = {camera, ambient_light, light, \
	sphere, plane, cylinder};

	return ((*func[type - 1])(data, args));
}

int	create_object(t_data *data, char *line)
{
	char		**args;
	t_obj_type	type;
	int			status;

	if (!line)
		return (0);
	args = ft_split(line, ' ');
	if (!args)
		return (0);
	if (!args[0])
		return (string_array_free(args), 1);
	type = check_obj_type(args[0]);
	if (type == ERROR)
		return (string_array_free(args), 0);
	status = create_object_type(data, args, type);
	string_array_free(args);
	return (status);
}

int	create_objects(char **sa)
{
	t_data	*data;
	int		i;

	if (!sa)
		return (1);
	i = -1;
	data = get_data();
	while (sa[++i])
	{
		if (!create_object(data, sa[i]))
			return (1);
	}
	return (0);
}
