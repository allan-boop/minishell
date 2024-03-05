/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:23:04 by gdoumer           #+#    #+#             */
/*   Updated: 2024/01/23 14:26:08 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first_lst;
	t_list	*new_lst;
	void	*content;

	if (!f || !del)
		return (NULL);
	first_lst = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_lst = ft_lstnew(content);
		if (!new_lst)
		{
			del(content);
			ft_lstclear(&first_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&first_lst, new_lst);
		lst = lst->next;
	}
	return (first_lst);
}
