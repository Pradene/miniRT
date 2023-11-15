#include "libft.h"

#define BUFFER_SIZE 32

static void ft_strcpy(char *s1, char *s2, int n)
{
    int i;

    i = -1;
    while (++i < n)
        s1[i] = s2[i];
}

static void ft_stradd(char **s1, char *s2)
{
    int     ss1;
    int     ss2;
    char    *s;

    ss1 = ft_strlen(*s1);
    ss2 = ft_strlen(s2);
    s = malloc(sizeof(char) * (ss1 + ss2 + 1));
    if (!s)
        return ;
    ft_strcpy(s, *s1, ss1);
    ft_strcpy(s + ss1, s2, ss2);
    s[ss1 + ss2] = '\0';
    free(*s1);
    *s1 = s;
}

static void read_file(int fd, char **line)
{
    int     n;
    int     readc;
    char    buf[BUFFER_SIZE + 1];

    readc = 1;
    while (readc && !ft_strchr(*line, '\n'))
    {
        readc = read(fd, buf, BUFFER_SIZE);
        if ((readc == -1 && *line == NULL) || readc == 0)
            return ;
        n = readc - 1;
        while (++n < BUFFER_SIZE + 1)
            buf[n] = '\0';
        ft_stradd(line, buf);
    }
}

static void make_line(char **line, char *stash)
{
    int     size;
    int     index;
    char    *s;

    index = ft_strchr(*line, '\n') - (*line) + 1;
    if (index < 0)
        return ;
    s = malloc(sizeof(char) * (index + 1));
    if (!s)
        return ;
    ft_strcpy(s, *line, index + 1);
    s[index] = '\0';
    size = ft_strlen(*line) - index;
    ft_strcpy(stash, *line + index, size);
    while (size < BUFFER_SIZE)
        stash[size++] = '\0';
    free(*line);
    *line = s;
}

char    *gnl(int fd)
{
    static  char    stash[BUFFER_SIZE + 1] = {0};
    char            *line;

    line = NULL;
    ft_stradd(&line, stash);
    ft_bzero(stash, BUFFER_SIZE + 1);
    read_file(fd, &line);
    make_line(&line, stash);
    if (*line == 0)
    {
        free(line);
        return (NULL);
    }
    return (line);
}