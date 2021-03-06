/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:51:02 by skharjo           #+#    #+#             */
/*   Updated: 2020/11/06 20:34:36 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *tmp;

	tmp = *lst;
	if ((*lst) && del)
	{
		while (tmp)
		{
			tmp = tmp->next;
			del(*lst);
			*lst = tmp;
		}
	}
	*lst = NULL;
}
