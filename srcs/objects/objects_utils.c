/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:05:13 by lpradene          #+#    #+#             */
/*   Updated: 2024/01/17 17:05:15 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	free_objects(t_obj_list **lst)
{
	t_obj_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		(*lst) = tmp;
	}
}

t_obj_list	*last_objects(t_obj_list *lst)
{
	t_obj_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_objects(t_obj_list **lst, t_obj_list *new)
{
	if (!lst || !new)
		return ;
	new->next = NULL;
	if (*lst)
		last_objects(*lst)->next = new;
	else
		*lst = new;
}

t_obj_type	check_obj_type(char *type)
{
	int					i;
	static const char	*types[] = {"C", "A", "L", "sp", "pl", "cy", NULL};

	if (!type)
		return (ERROR);
	i = -1;
	while (types[++i])
	{
		if (!ft_strcmp(types[i], type))
			return (i + 1);
	}
	return (ERROR);
}
