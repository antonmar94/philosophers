/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 20:02:47 by antonmar          #+#    #+#             */
/*   Updated: 2020/10/02 13:33:53 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	int		i;
	void	*tams;

	i = 0;
	tams = malloc(ft_strlen(string) + 1);
	if (tams != NULL)
	{
		while (i < ft_strlen(string) + 1)
		{
			((char *)tams)[i] = string[i];
			i++;
		}
	}
	return (tams);
}
