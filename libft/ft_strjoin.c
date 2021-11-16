/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:16:34 by antonmar          #+#    #+#             */
/*   Updated: 2020/09/29 13:16:35 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = malloc(size + 1);
	i = -1;
	j = 0;
	if (str == NULL)
		return (NULL);
	while (++i < ft_strlen((char *)s1))
	{
		str[i] = s1[i];
	}
	while (i < size)
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
