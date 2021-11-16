/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:17:59 by antonmar          #+#    #+#             */
/*   Updated: 2021/10/25 18:39:15 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfiller(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	str[i] = c;
	return (str);
}

int	ft_sizeof_num(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n == 2147483647)
		return (10);
	if (n < 0)
	{
		size = 1;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

void	ft_putn(char *str, int n)
{
	if (n < 0)
	{
		ft_strfiller(str, '-');
		ft_putn(str, n * -1);
		return ;
	}
	if (n > 9)
	{
		ft_putn(str, n / 10);
		n = n % 10;
	}
	ft_strfiller(str, n + 48);
}

char	*ft_itoa(int n)
{
	char	*str;

	str = ft_calloc(ft_sizeof_num(n) + 1, 1);
	if (str == NULL)
		return (NULL);
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		ft_putn(str, (n % 1000000000) * -1);
		ft_strfiller(str, '\0');
		return (str);
	}
	ft_putn(str, n);
	ft_strfiller(str, '\0');
	return (str);
}
