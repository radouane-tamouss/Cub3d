#include "../cube.h"

void print_err(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
}
