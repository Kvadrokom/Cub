/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:52:22 by skharjo           #+#    #+#             */
/*   Updated: 2020/11/07 20:38:09 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_length(const char *s, char c)
{
	int		len;

	len = 0;
	while (*s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static int			ft_numstr(const char *s, char c, int numstr)
{
	int	inword;

	inword = 1;
	if (s)
	{
		while (*s)
		{
			if (*s == c)
			{
				inword = 1;
				s++;
			}
			if (*s != c && *s)
			{
				if (inword)
				{
					numstr++;
					inword = 0;
				}
				s++;
			}
		}
		return (numstr);
	}
	return (0);
}

static char			*ft_makestr(const char *s, char c)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_length(s, c);
	str = (char*)malloc(sizeof(char) * (len + 1));
	while (i < len)
		str[i++] = *s++;
	str[i] = '\0';
	return (str);
}

static char			**ft_split_d(char **split, int numstr,
								char c, const char *s)
{
	int i;

	i = 0;
	while (i < numstr && *s)
	{
		if (*s == c)
			s++;
		else
		{
			split[i++] = ft_makestr(s, c);
			if (!split)
			{
				while (i >= 0)
					free(split[i--]);
				free(split);
				return (NULL);
			}
			s = s + ft_length(s, c);
		}
	}
	split[i] = 0;
	return (split);
}

char				**ft_split(char const *s, char c)
{
	char	**split;
	int		numstr;
	int		i;

	i = 0;
	numstr = 0;
	if (!s)
		return (NULL);
	numstr = ft_numstr(s, c, numstr);
	split = (char **)malloc(sizeof(char *) * (numstr + 1));
	if (!split)
		return (NULL);
	return (ft_split_d(split, numstr, c, s));
}
