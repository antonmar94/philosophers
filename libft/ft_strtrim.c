/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 10:13:37 by antonmar          #+#    #+#             */
/*   Updated: 2021/10/25 18:50:07 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	findsize(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		size;
	int		finded;

	i = 0;
	size = 0;
	while (i < ft_strlen((char *)s1))
	{
		j = 0;
		finded = 0;
		while (j < ft_strlen((char *)set))
		{
			if (s1[i] == set[j])
				finded = 1;
			j++;
		}
		if (finded == 0)
		{
			size = i;
			i = ft_strlen((char *)s1) - 1;
		}
		i++;
	}
	return (size);
}

int	findsizet(char const *s1, char const *set, int size)
{
	int		i;
	int		j;
	int		sizet;
	int		finded;

	i = ft_strlen((char *)s1) - 1;
	sizet = 0;
	while (i > size)
	{
		j = 0;
		finded = 0;
		while (j < ft_strlen((char *)set))
		{
			if (s1[i] == set[j])
				finded = 1;
			j++;
		}
		if (finded == 0)
		{
			sizet = i - size + 1;
			i = 0;
		}
		i--;
	}
	return (sizet);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		size;
	int		sizet;
	int		i;

	if (!s1 || !set)
		return (0);
	size = findsize(s1, set);
	sizet = findsizet(s1, set, size);
	str = malloc(sizet + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < sizet)
	{
		str[i] = s1[size];
		size++;
		i++;
	}
	str[sizet] = '\0';
	return (str);
}
