/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 16:58:53 by antonmar          #+#    #+#             */
/*   Updated: 2021/10/25 18:41:19 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void *str1, void *str2, size_t n)
{
	size_t	a;
	size_t	i;
	char	*s1;
	char	*s2;

	i = 0;
	a = (unsigned int)n;
	s1 = (char *)str1;
	s2 = (char *)str2;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < a - 1)
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
