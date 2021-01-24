/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:59:09 by skharjo           #+#    #+#             */
/*   Updated: 2020/11/06 20:37:49 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	else
		len = (len > ft_strlen(&s[start])) ? ft_strlen(&s[start]) : len;
	sub = (char*)malloc(sizeof(char) * (len + 1));
	if (!sub || !s)
		return (NULL);
	while (s[start] && len)
	{
		sub[i++] = s[start++];
		len--;
	}
	sub[i] = '\0';
	return (sub);
}
