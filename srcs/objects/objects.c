#include "../../includes/rt.h"

void    free_objects(t_obj_list **lst)
{
    t_obj_list  *tmp;

    if (!lst)
        return ;
    while (*lst)
    {
        tmp = (*lst)->next;
        free(*lst);
        (*lst) = tmp;
    }
}

static t_obj_list   *last_objects(t_obj_list *lst)
{
    t_obj_list  *tmp;

    if (!lst)
        return (NULL);
    tmp = lst;
    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

void    add_objects(t_obj_list **lst, t_obj_list *new)
{
    t_obj_list	*tmp;

	if (!lst)
        return ;
	if (*lst)
	{
		tmp = last_objects(*lst);
		tmp->next = new;
	}
	else
    {
		*lst = new;
    }
}

t_obj_type  check_obj_type(char *type)
{
    int                 i;
    static const char   *types[] = {"C", "A", "L", "sp", "pl", "cy", NULL};

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

int check_ambient_light(t_alight light)
{
    if (!check_color(light.color) || !check_brightness(light.brightness))
        return (0);
    return (1);
}

int ambient_light(char **args)
{
    t_data  *data;
    char    *tmp;

    data = get_data();
    if (string_array_size(args) != 3)
        return (0);
    if (data->alight.created)
        return (0);
    data->alight.brightness = ft_atof(args[1], &tmp);
    if (tmp != args[1] + ft_strlen(args[1]))
        return (0);
    data->alight.color = atocolor(args[2]);
    data->alight.created = 1;
    if (!check_ambient_light(data->alight))
        return (0);
    return (1);
}

int check_light(t_light light)
{
    if (!check_color(light.color) || !check_brightness(light.brightness))
        return (0);
    return (1);
}

int light(char **args)
{
    t_data  *data;
    char    *tmp;

    data = get_data();
    if (string_array_size(args) != 4)
        return (0);
    if (data->light.created)
        return (0);
    data->light.origin = atov3(args[1]);
    data->light.brightness = ft_atof(args[2], &tmp);
    data->light.color = atocolor(args[3]);
    data->light.created = 1;
    if (!check_light(data->light))
        return (0);
    return (1);
}

int sphere(char **args)
{
    t_obj_list  *obj;
    t_data      *data;
    char        *tmp;

    data = get_data();
    if (string_array_size(args) != 4)
        return (0);
    obj = malloc(sizeof(t_obj_list));
    if (!obj)
        return (0);
    obj->next = NULL;
    obj->object.type = SPHERE;
    obj->object.origin = atov3(args[1]);
    obj->object.diameter = ft_atof(args[2], &tmp);
    obj->object.color = atocolor(args[3]);
    add_objects(&data->objects, obj);
    return (1);
}

int plane(char **args)
{
    t_obj_list  *obj;
    t_data  *data;

    data = get_data();
    if (string_array_size(args) != 4)
        return (0);
    obj = malloc(sizeof(t_obj_list));
    if (!obj)
        return (0);
    obj->next = NULL;
    obj->object.type = PLANE;
    obj->object.origin = atov3(args[1]);
    obj->object.rotation = atov3(args[2]);
    obj->object.rotation = normalize(obj->object.rotation);
    obj->object.color = atocolor(args[3]);
    add_objects(&data->objects, obj);
    return (1);
}

int cylinder(char **args)
{
    t_obj_list  *obj;
    t_data      *data;
    char        *tmp;

    data = get_data();
    if (string_array_size(args) != 6)
        return (0);
    obj = malloc(sizeof(t_obj_list));
    if (!obj)
        return (0);
    obj->next = NULL;
    obj->object.type = CYLINDER;
    obj->object.origin = atov3(args[1]);
    obj->object.rotation = atov3(args[2]);
    obj->object.rotation = normalize(obj->object.rotation);
    obj->object.diameter = ft_atof(args[3], &tmp);
    obj->object.height = ft_atof(args[4], &tmp);
    obj->object.color = atocolor(args[5]);
    add_objects(&data->objects, obj);
    return (1);
}

int create_object_type(char **args, t_obj_type type)
{
    int (*func[])() = {camera, ambient_light, light, sphere, plane, cylinder};

    return ((*func[type - 1])(args));
}

int create_object(char *line)
{
    char        **args;
    t_obj_type  type;
    int         status;

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
    status = create_object_type(args, type);
    string_array_free(args);
    return (status);
}

int create_objects(char **sa)
{
    t_data  *data;
    int     i;

    if (!sa)
        return (1);
    i = -1;
    data = get_data();
    while (sa[++i])
    {
        if (!create_object(sa[i]))
            return (1);
    }
    return (0);
}