/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:01:59 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/29 16:27:59 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_parse_string(char *str)
{
	while (*str)
	{
		if (!(*str >= 48 && *str <= 57))
			return (0);
		str++;
	}
	return (1);
}

int	ft_plist_size(t_philist *plist)
{
	int	size;

	if (!plist->next)
		return (1);
	size = 1;
	plist = plist->next;
	while (plist->philo->number != 1)
	{
		size++;
		plist = plist->next;
	}
	return (size);
}

int	ft_test_error(int argc, char **argv)
{
	argv++;
	if (argc < 5 || argc > 6)
	{
		write(1, "Error, wrong number of arguments\n", 34);
		return (0);
	}
	while (*argv)
	{
		if (!ft_parse_string(*argv))
		{
			write(1, "Error, wrong argument\n", 23);
			return (0);
		}
		argv++;
	}
	return (1);
}

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
