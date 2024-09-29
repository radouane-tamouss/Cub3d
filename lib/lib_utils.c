/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lib_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rtamouss <rtamouss@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/02 10:16:01 by rtamouss      #+#    #+#                 */
/*   Updated: 2024/09/28 10:28:34 by rtamouss      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	ptr = NULL;
	while (i <= len)
	{
		if (s[i] == (const char)c)
			ptr = (char *)(s + i);
		i++;
	}
	if (ptr != NULL)
		return (ptr);
	else
		return (NULL);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*s;

	i = 0;
	len = ft_strlen(s1);
	s = (char *)malloc(len * sizeof(char) + 1);
	if (s == NULL)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}
