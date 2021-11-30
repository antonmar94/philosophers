/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:44:07 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/29 16:20:49 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_takefork(void *thread)
{
	t_philist				*plist;
	static pthread_mutex_t	my_turn = PTHREAD_MUTEX_INITIALIZER;

	plist = (t_philist *)thread;
	pthread_mutex_lock(&my_turn);
	while (ft_take_leftfork(plist) == 0)
	{
		pthread_mutex_unlock(&my_turn);
		if (ft_waiter(plist, thread, 10) == 0)
			return (NULL);
	}
	pthread_mutex_unlock(&my_turn);
	while (ft_take_rightfork(plist) == 0)
	{
		if (ft_waiter(plist, thread, 10) == 0)
			return (NULL);
	}
	ft_eat(plist);
	return (NULL);
}

void	*ft_eat(void *thread)
{
	t_philist	*plist;

	plist = (t_philist *)thread;
	ft_printer(plist, "\033[0;33mPhilosopher", "is eating 🍝", 0);
	*plist->philo->time_left = 0;
	plist->philo->number_of_times_toeat--;
	if (dead_counter(plist, thread, plist->philo->time_to_eat) == 0)
		return (NULL);
	pthread_mutex_lock(&plist->philo->right_fork->mutex_fork);
	plist->philo->right_fork->taken--;
	pthread_mutex_unlock(&plist->philo->right_fork->mutex_fork);
	pthread_mutex_lock(&plist->prev->philo->right_fork->mutex_fork);
	plist->prev->philo->right_fork->taken--;
	pthread_mutex_unlock(&plist->prev->philo->right_fork->mutex_fork);
	ft_sleep(plist);
	return (NULL);
}

void	*ft_sleep(void *thread)
{
	t_philist	*plist;

	plist = (t_philist *)thread;
	ft_printer(plist, "\033[0;34mPhilosopher", "is sleeping 😴", 0);
	if (!dead_counter(plist, thread, plist->philo->time_to_sleep))
		return (NULL);
	ft_think(plist);
	return (NULL);
}

void	*ft_think(void *thread)
{
	t_philist				*plist;

	plist = (t_philist *)thread;
	ft_printer(plist, "\033[0;36mPhilosopher", "is thinking 🤔", 0);
	ft_takefork(plist);
	return (NULL);
}

void	ft_printer(t_philist *plist, char *str1, char *str2, int ded)
{
	static pthread_mutex_t	printing = PTHREAD_MUTEX_INITIALIZER;
	static int				noprint;

	if (!noprint)
	{
		pthread_mutex_lock(&printing);
		if (!noprint)
		{
			printf("%li ", ft_thistime() - plist->philo->start);
			printf("%s %i", str1, plist->philo->number);
			printf(" %s\n\033[0m", str2);
			if (ded)
			{
				noprint = 1;
				pthread_mutex_destroy(&printing);
			}
			pthread_mutex_unlock(&printing);
		}
	}
}
