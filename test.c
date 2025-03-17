#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd;
    char buffer[1024];
    ssize_t bytes_read;

    if (argc != 2)
    {
        printf("Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }

    printf("File opened successfully\n");

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }

    close(fd);
    printf("\nFile read successfully\n");

    return 0;
} 