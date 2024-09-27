/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:40:35 by rtamouss          #+#    #+#             */
/*   Updated: 2024/03/08 09:46:57 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fcntl.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr < 10)
		ft_putchar_fd(nbr + '0', fd);
	else
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd((nbr % 10) + '0', fd);
	}
}
