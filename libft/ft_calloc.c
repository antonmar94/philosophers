/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 19:42:08 by antonmar          #+#    #+#             */
/*   Updated: 2020/10/05 14:18:31 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*pointer;
	int		i;

	i = 0;
	pointer = malloc(nitems * size);
	if (pointer == NULL)
		return (NULL);
	while (i < (int)nitems * (int)size)
	{
		((char *)pointer)[i] = '\0';
		i++;
	}
	return (pointer);
}
