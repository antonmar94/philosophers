/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 12:09:12 by antonmar          #+#    #+#             */
/*   Updated: 2021/10/25 18:47:39 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*s;

	s = (char *)str;
	while (*s)
		s++;
	if (c == '\0')
		return ((char *)s);
	while (s >= str)
	{
		if (c == *s)
			return ((char *)s);
		s--;
	}
	return (0);
}
