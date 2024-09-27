/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:32:24 by rtamouss          #+#    #+#             */
/*   Updated: 2023/11/17 17:39:01 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (lst && del)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = tmp;
		}
		*lst = NULL;
	}
}

// static void	del(void *content)
// {
// 	free(content);
// }
// int	main(void)
// {
// 	t_list *n1 = ft_lstnew("hello");
// 	t_list *n2 = ft_lstnew("world");
// 	t_list *n3 = ft_lstnew("hhh");
// 	ft_lstadd_back(&n1, n2);
// 	ft_lstadd_back(&n1, n3);
// 	while (n1)
// 	{
// 		printf("%s\n", n1 -> content);
// 		n1 = n1 -> next;
// 	}
// 	printf("after freeing\n");
// 	ft_lstclear(&n1, del);
// 	while (n1)
// 	{
// 		printf("%s\n", n1 -> content);
// 		n1 = n1 -> next;
// 	}
// 	return (0);
// }