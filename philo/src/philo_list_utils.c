/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:43:05 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/30 14:41:48 by antonmar         ###   ########.fr       */
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
	philo->count = 0;
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

void	print_plist(t_philist *plist, int size)
{
	int			i;
	t_philist	*aux;

	i = 0;
	aux = plist;
	printf("\n");
	printf("\033[0;31m%65s", " 📚 philo 📚 ");
	printf("\n");
	printf("\033[0;31m%57s", "------------\n");
	while (i < size)
	{
		printf("\033[0mphilo %-3i", i + 1);
		printf("\033[0;32mnumber: \033[0m%-3i",
			aux->philo->number);
		printf("\033[0;35mtime to die: \033[0m[%d] ",
			aux->philo->time_to_die);
		printf("\033[0;33mtime to eat: \033[0m[%i] ",
			aux->philo->time_to_eat);
		printf("\033[0;34mtime to sleep: \033[0m[%i] ",
			aux->philo->time_to_sleep);
		printf("\033[0;36mnumber of times to eat: \033[0m[%i]\n ",
			aux->philo->number_of_times_toeat);
		aux = aux->next;
		i++;
	}
}
