/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 13:10:47 by antonmar          #+#    #+#             */
/*   Updated: 2021/10/25 18:47:03 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *s, size_t len)
{
	int	lens;

	if (!*s)
		return ((char *)str);
	lens = ft_strlen((char *)s);
	while (*str)
	{
		if (*str == *s && !ft_strncmp((char *)str, (char *)s, lens))
			return ((char *)str);
		str++;
		if (lens >= (int)len--)
			break ;
	}
	return (NULL);
}
