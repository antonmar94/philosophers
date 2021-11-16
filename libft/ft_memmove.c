/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 12:38:46 by antonmar          #+#    #+#             */
/*   Updated: 2021/10/25 18:41:44 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	char	*d;
	char	*s;
	int		i;

	d = (char *)dest;
	s = (char *)src;
	if (src == dest)
		return ((void *)src);
	if (src < dest)
	{
		i = size - 1;
		while (i >= 0)
		{
			d[i] = s[i];
			i--;
		}
	}
	else
	{
		i = -1;
		while (++i < (int)size)
			d[i] = s[i];
	}
	return ((void *)d);
}
