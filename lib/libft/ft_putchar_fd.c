/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:59:33 by rtamouss          #+#    #+#             */
/*   Updated: 2023/11/22 17:39:03 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

// #include "libft.h"
// #include <fcntl.h>

// int main(void)
// {
// 	ft_putchar_fd('0',0);
// 	write(1,"\n",1);
//     ft_putchar_fd('A', 1);
//     write(1, "\n", 1);
//     ft_putchar_fd('B', 2);
//     write(2, "\n", 1);
//     int fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
//     if (fd != -1)
//     {
//         ft_putchar_fd('C', fd);
//         close(fd);
//     }
//     ft_putchar_fd('\t', 1);
//     write(1, "\n", 1);

//     return 0;
// }