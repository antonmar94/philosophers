/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:44:07 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/28 19:51:43 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_takefork(void *thread)
{
	t_philist	*plist;

	plist = (t_philist *)thread;
	while (plist->philosopher->turn == 0)
	{
		if (ft_waiter(plist, thread, 10) == 0)
			return (NULL);
	}
	ft_take_leftfork(plist);
	while (plist->philosopher->right_fork->taken != 0)
	{
		if (ft_waiter(plist, thread, 10) == 0)
			return (NULL);
	}
	ft_take_rightfork(plist);
	ft_eat(plist);
	return (NULL);
}

void	*ft_eat(void *thread)
{
	t_philist	*plist;

	plist = (t_philist *)thread;
	if (plist->philosopher->forks_taken == 2)
	{
		ft_printer(plist, "\033[0;33mPhilosopher", "is eating", 0);
		*plist->philosopher->time_left = 0;
		plist->philosopher->number_of_times_toeat--;
		if (dead_counter(plist, thread, plist->philosopher->time_to_eat) == 0)
			return (NULL);
		pthread_mutex_lock(&plist->philosopher->right_fork->mutex_fork);
		plist->philosopher->right_fork->taken--;
		plist->philosopher->forks_taken--;
		pthread_mutex_unlock(&plist->philosopher->right_fork->mutex_fork);
		pthread_mutex_lock(&plist->prev->philosopher->right_fork->mutex_fork);
		plist->prev->philosopher->right_fork->taken--;
		plist->philosopher->forks_taken--;
		pthread_mutex_unlock(&plist->prev->philosopher->right_fork->mutex_fork);
		plist->philosopher->turn = 0;
		plist->next->philosopher->turn = 1;
		plist->philosopher->has_eaten = 1;
		plist->philosopher->has_sleep = 0;
	}
	ft_sleep(plist);
	return (NULL);
}

void	*ft_sleep(void *thread)
{
	t_philist	*plist;

	plist = (t_philist *)thread;
	if (plist->philosopher->has_eaten == 1)
	{
		ft_printer(plist, "\033[0;34mPhilosopher", "is sleeping", 0);
		if (!dead_counter(plist, thread, plist->philosopher->time_to_sleep))
			return (NULL);
		plist->philosopher->has_sleep = 1;
		plist->philosopher->has_eaten = 0;
	}
	ft_think(plist);
	return (NULL);
}

void	*ft_think(void *thread)
{
	t_philist				*plist;

	plist = (t_philist *)thread;
	ft_printer(plist, "\033[0;36mPhilosopher", "is thinking", 0);
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
			printf("%li ", ft_thistime() - plist->philosopher->start);
			printf("%s %i", str1, plist->philosopher->number);
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