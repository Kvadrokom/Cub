/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:18:43 by skharjo           #+#    #+#             */
/*   Updated: 2020/11/06 20:37:31 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	j;

	j = 0;
	if (ft_strlen(little) > ft_strlen(big))
		return (NULL);
	if (!n || !ft_strlen(little))
		return (big);
	while (*big && n)
	{
		if (n-- && *big == *little)
		{
			while (little[j] && *big)
			{
				if (*big++ != little[j])
					break ;
				j++;
			}
		}
		if (little[j] == 0)
			return ((char *)big - j);
		j = 0;
		big++;
	}
	return (NULL);
}
