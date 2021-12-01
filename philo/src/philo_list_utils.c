/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:43:05 by antonmar          #+#    #+#             */
/*   Updated: 2021/12/01 12:53:15 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_fork	*create_fork(void)
{
	t_fork	*fork;

	fork = (t_fork *)malloc(sizeof(t_fork));
	fork->taken = 0;
	pthread_mutex_init(&(fork->mutex_fork), NULL);
	return (fork);
}

t_philo	*create_phil(char **argv)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->right_fork = create_fork();
	philo->time_to_die = ft_atoi(argv[2]);
	philo->turn = 0;
	philo->count = 0;
	philo->forks_taken = 0;
	philo->time_left = &philo->count;
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (!argv[5])
	{
		philo->numeat = 0;
		philo->number_of_times_toeat = 0;
	}
	else
	{
		philo->numeat = 1;
		philo->number_of_times_toeat = ft_atoi(argv[5]);
	}
	return (philo);
}

t_philist	*create_pnode(char **argv)
{
	t_philist		*list;

	list = (t_philist *)malloc(sizeof(t_philist));
	if (!list)
		return (NULL);
	list->philo = create_phil(argv);
	if (!(list->philo))
		return (NULL);
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

t_philist	*create_plist(char **argv, int size)
{
	t_philist		*list;
	t_philist		*list_init;
	t_philist		*aux;
	int				i;

	i = 1;
	list = create_pnode(argv);
	list->philo->number = 1;
	list_init = list;
	while (++i <= size)
	{
		list->next = create_pnode(argv);
		aux = list;
		list = list->next;
		list->prev = aux;
		list->philo->number = i;
	}
	list->next = list_init;
	list_init->prev = list;
	list = list->next;
	return (list);
}

int	ft_finisher(t_philist *plist, pthread_t philo)
{
	t_philist	*p_init;

	p_init = plist;
	while (1)
	{
		usleep(1000);
		if (p_init->philo->dead == 1)
		{
			pthread_detach(philo);
			return (0);
		}
		p_init = p_init->next;
		while (p_init->philo->number != plist->philo->number)
		{
			if (p_init->philo->dead == 1)
			{
				pthread_detach(philo);
				return (0);
			}
			p_init = p_init->next;
		}
		if (ft_eatchecker(plist) == 1)
			return (0);
	}
	return (1);
}
