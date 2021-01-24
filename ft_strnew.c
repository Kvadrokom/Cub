/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:34:59 by skharjo           #+#    #+#             */
/*   Updated: 2021/01/04 20:01:25 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(int size)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (new)
	{
		while (i < size)
			new[i++] = '\0';
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}
