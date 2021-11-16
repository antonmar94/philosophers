/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:37:33 by antonmar          #+#    #+#             */
/*   Updated: 2021/10/25 18:38:28 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*nonull;

	if (!lst)
		return (NULL);
	res = ft_lstnew(f(lst->content));
	if (!res)
	{
		ft_lstclear(&res, del);
		return (NULL);
	}
	while (lst->next)
	{
		nonull = ft_lstnew(f(lst->content));
		if (!(nonull))
		{
			ft_lstclear(&lst, del);
			return (res);
		}
		ft_lstadd_back(&res, nonull);
		lst = lst->next;
	}
	return (res);
}
