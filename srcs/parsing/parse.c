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
        if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';
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

int parsing(char *path)
{
    int     fd;
    char    **file;
    t_data  *data;

    data = get_data();
    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: invald file\n");
        return (1);
    }
    file = read_file(fd);
    if (!file)
    {
        printf("Error: couldn't read %s file\n", path);
        close(fd);
        return (1);
    }
    if (create_objects(file))
    {
        printf("Error: couldn't parse %s file\n", path);
        string_array_free(file);
        close(fd);
        return (1);
    }
    string_array_free(file);
    close(fd);
    return (0);
}