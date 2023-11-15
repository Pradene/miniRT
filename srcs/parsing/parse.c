#include "../../includes/rt.h"

static char **read_file(int fd)
{
    int     i;
    char    *line;
    char    **tmp;
    char    **file;

    i = -1;
    file = NULL;
    line = gnl(fd);
    if (!line)
        return (NULL);
    while (line)
    {
        tmp = NULL;
        line[ft_strlen(line) - 1] = '\0';
        tmp = malloc(sizeof(char *) * ((++i + 1) + 1));
        if (!tmp)
            return (free_string_array(file), free(line), NULL);
        copy_string_array(tmp, file);
        free(file);
        tmp[i] = line;
        tmp[i + 1] = NULL;
        file = tmp;
        line = gnl(fd);
    }
    return (file);
}

void    parsing(char *path)
{
    int     fd;
    char    **file;
    t_data  *data;

    data = get_data();
    if (!ft_strrcmp(path, ".rt"))
    {
        printf("Error: the map file has to finish by .rt\n");
        free_data();
    }
    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: invald file\n");
        free_data();
    }
    file = read_file(fd);
    create_objects(file);
    print_objects();
    free_string_array(file);
    close(fd);
}