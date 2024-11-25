#include "../cube.h"

void print_err(char *str)
{
	ft_putstr_fd("Error ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
