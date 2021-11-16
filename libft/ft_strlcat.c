/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 18:10:18 by antonmar          #+#    #+#             */
/*   Updated: 2021/10/25 18:46:05 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int	i;
	int	j;
	int	lend;

	j = 0;
	lend = ft_strlen(dst);
	i = lend;
	if (lend < (int)size && size > 0)
	{
		while (src[j] != '\0' && i < (int)size - 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
	}
	if ((int)size > lend)
		return (lend + ft_strlen(src));
	else
		return (size + ft_strlen(src));
}
