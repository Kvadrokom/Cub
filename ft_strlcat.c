/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:10:22 by skharjo           #+#    #+#             */
/*   Updated: 2020/11/06 20:36:56 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		n;
	int		i;
	int		len;

	len = size < ft_strlen(dst) ? size : ft_strlen(dst);
	i = len + ft_strlen(src);
	n = size - ft_strlen(dst) - 1;
	while (*dst)
		dst++;
	if (n > 0)
	{
		while (n-- && size--)
			*dst++ = *src++;
	}
	else
		return (i);
	if (size)
		*dst = '\0';
	return (i);
}
