/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 17:40:42 by antonmar          #+#    #+#             */
/*   Updated: 2021/10/29 14:22:46 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	find_simb(const char *str, int i)
{
	long	simb;

	simb = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			simb = -1;
	}
	return (simb);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	res;
	long	simb;

	res = 0;
	i = 0;
	simb = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	simb = find_simb(str, i);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = str[i] - 48 + res * 10;
		if (res * simb >= 2147483648)
			return (-1);
		else if (res * simb < -2147483648)
			return (-1);
		i++;
	}
	res *= simb;
	return (res);
}
