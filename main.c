//
// Created by Anton Lushenko on 2/17/17.
//

#include "FdF.h"





int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc != 2)
        return (0);

    fd = open(argv[1], O_RDONLY);
    while (get_next_line(fd, &line))
    {
        printf("%s\n", line);
        free(line);
    }
    //fdf();
    return (0);
}