/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:49:59 by skharjo           #+#    #+#             */
/*   Updated: 2020/11/06 20:35:13 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*tmp;

	tmp = (t_list*)malloc(sizeof(t_list));
	if (tmp)
	{
		tmp->next = 0;
		tmp->content = content;
		return (tmp);
	}
	return (NULL);
}
