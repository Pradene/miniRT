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
    static const char   *types[] = {"A", "C", "L", "sp", "pl", "cy", NULL};

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

int check_camera(t_camera camera)
{
    if (!check_fov(camera.fov) || !check_direction(camera.direction))
        return (0);
    return (1);
}

int camera(char **args)
{
    t_data  *data;
    char    *tmp;

    data = get_data();
    if (string_array_size(args) != 4)
        return (0);
    if (data->camera.created)
        return (0);
    data->camera.position = atov4(args[1], false);
    data->camera.direction = atov4(args[2], true);
    data->camera.fov = (int)ft_atof(args[3], &tmp);
    data->camera.created = 1;
    if (!check_camera(data->camera))
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
    data->light.position = atov4(args[1], false);
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
    obj->object.position = atov4(args[1], false);
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
    obj->object.position = atov4(args[1], false);
    obj->object.rotation = atov4(args[2], true);
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
    obj->object.position = atov4(args[1], false);
    obj->object.rotation = atov4(args[2], true);
    obj->object.diameter = ft_atof(args[3], &tmp);
    obj->object.height = ft_atof(args[4], &tmp);
    obj->object.color = atocolor(args[5]);
    add_objects(&data->objects, obj);
    return (1);
}

int create_object_type(char **args, t_obj_type type)
{
    int (*func[])() = {ambient_light, camera, light, sphere, plane, cylinder};

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
        return (free_string_array(args), 1);
    type = check_obj_type(args[0]);
    if (type == ERROR)
        return (free_string_array(args), 0);
    status = create_object_type(args, type);
    free_string_array(args);
    return (status);
}

void    create_objects(char **sa)
{
    t_data  *data;
    int     i;

    if (!sa)
        return ;
    i = -1;
    data = get_data();
    while (sa[++i])
    {
        if (!create_object(sa[i]))
        {
            printf("Error during parsing at line %d\n", i + 1);
            break ;
        }
    }
}