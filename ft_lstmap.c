/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:40:36 by skharjo           #+#    #+#             */
/*   Updated: 2020/11/06 20:35:08 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	new = NULL;
	if (!f)
		return (NULL);
	while (lst)
	{
		if ((tmp = ft_lstnew(f(lst->content))) == NULL && del)
		{
			while (new)
			{
				tmp = new->next;
				del(new->content);
				free(new);
				new = tmp;
			}
			lst = NULL;
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&new, tmp);
	}
	return (new);
}
