/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:01:59 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/17 15:59:36 by antonmar         ###   ########.fr       */
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

int	ft_test_error(char **argv)
{
	argv++;
	while (*argv)
	{
		if (!ft_parse_string(*argv))
			return (0);
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
	philosopher->time_to_die = ft_atoi(argv[2]);
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

void	del_function(t_philist *list)
{
	t_philist	*aux;

	while (list)
	{
		aux = list;
		free (list);
		list = aux->next;
	}
}

float	ft_difftime(struct timeval *start, struct timeval *end) //revisar esto
{
	float res;
	printf("%i\n", start->tv_usec);
	printf("%i\n", end->tv_usec);
	res = (end->tv_usec / 1000) - (start->tv_usec / 1000);
	return (res);
}
