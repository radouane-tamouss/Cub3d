/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtamouss <rtamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:57:44 by rtamouss          #+#    #+#             */
/*   Updated: 2023/11/17 18:20:17 by rtamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

// void		*to_uppercase(void *content)
// {
// 	char	*str;
// 	char	*new_str;
// 	int		i;

// 	str = (char *)content;
// 	new_str = malloc(ft_strlen(str) + 1);
// 	if (!new_str)
// 		return (NULL);
// 	i = 0;
// 	while (str[i])
// 	{
// 		new_str[i] = ft_toupper(str[i]);
// 		i++;
// 	}
// 	new_str[i] = '\0';
// 	return (new_str);
// }
// void	del(void *content)
// {
//     free(content);
// }

// int	main(void)
// {
// 	t_list 	*list = ft_lstnew("Hello");
// 	ft_lstadd_back(&list, ft_lstnew("world"));
// 	t_list	*new_list = ft_lstmap(list, to_uppercase, del);
// 	t_list *temp = new_list;
// 	printf("our list : \n");
// 	while(list)
// 	{
// 		printf("%s\n", (char *)list->content);
// 		list = list -> next;
// 	}
// 	printf("the new_list : \n");
// 	while(temp)
// 	{
// 		printf("%s\n", (char *)temp->content);
// 		temp = temp -> next;
// 	}
// 	return (0);
// }