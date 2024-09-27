/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:28:40 by rtamouss          #+#    #+#             */
/*   Updated: 2023/11/17 17:07:06 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp -> next)
			tmp = tmp -> next;
		tmp -> next = new;
	}
}

// int	main(void)
// {
// 	t_list *n1 = ft_lstnew("hello");
// 	t_list *n2 = ft_lstnew("world");
// 	t_list *n3 = malloc(sizeof(t_list));
// 	if (!n3)
// 		return 1;
// 	n3 -> content = "hhhhh";
// 	n3 -> next = NULL;
// 	ft_lstadd_back(&n1, n2);
// 	ft_lstadd_back(&n1, n3);
// 	while(n1)
// 	{
// 		printf("%s\n" , n1->content);
// 		n1 = n1 -> next;
// 	}
// 	return (0);
// }