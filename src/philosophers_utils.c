/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:01:59 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/24 19:52:50 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_parse_string(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
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
			write(1, "Error, wrong argument\n", 25);
			return (0);
		}
		argv++;
	}
	return (1);
}

t_philosopher	*create_phil(char **argv)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	pthread_mutex_init(&(philosopher->right_fork), NULL);
	philosopher->time = 0;
	philosopher->time_to_die = ft_atoi(argv[2]);
	philosopher->count = philosopher->time_to_die;
	philosopher->time_left = &philosopher->count;
	philosopher->time_to_eat = ft_atoi(argv[3]);
	philosopher->time_to_sleep = ft_atoi(argv[4]);
	if (!argv[5])
		philosopher->number_of_times_toeat = 0;
	else
		philosopher->number_of_times_toeat = ft_atoi(argv[5]);
	return (philosopher);
}

t_philist	*create_pnode(char **argv)
{
	t_philist		*list;

	list = (t_philist *)malloc(sizeof(t_philist));
	if (!list)
		return (NULL);
	list->philosopher = create_phil(argv);
	if (!(list->philosopher))
		return (NULL);
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

float	ft_difftime(struct timeval *start, struct timeval *end)
{
	float res;

	res = 0;
	res = ((end->tv_sec * 1000) + (end->tv_usec / 1000))
	- ((start->tv_sec * 1000) + (start->tv_usec / 1000));
	return (res);
}

time_t	ft_thistime(void)
{
	struct timeval start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
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

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	return (0);
}
