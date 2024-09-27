/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:17:55 by rtamouss          #+#    #+#             */
/*   Updated: 2023/11/17 16:19:05 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*s;

	len = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = count_digits(n);
	s = (char *)malloc(len + 1);
	if (!s)
		return (0);
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
	}
	s[len--] = '\0';
	while (n != 0)
	{
		s[len] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	return (s);
}

// int main(void)
// {
// 	printf("%d\n",count_digits(21474836494));
// 	printf("%s\n",ft_itoa(214748364));
// 	return (0);
// }