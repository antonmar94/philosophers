/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:44:07 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/27 18:03:43 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_eat(void *thread)
{
	t_philist	*plist;

	plist = (t_philist *)thread;
	if (ft_diechecker(plist) || ft_eatchecker(plist))
		return (NULL);
	ft_printer(plist, "\033[0;33mPhilosopher", "is eating", 0);
	*plist->philosopher->time_left = 0;
	plist->philosopher->number_of_times_toeat--;
	ft_usleep(plist, plist->philosopher->time_to_eat);
	pthread_mutex_unlock(&(plist->philosopher->right_fork));
	pthread_mutex_unlock(&(plist->prev->philosopher->right_fork));
	plist->philosopher->turn = 0;
	ft_sleep(plist);
	return (NULL);
}

void	*ft_takefork(void *thread)
{
	t_philist	*plist;

	plist = (t_philist *)thread;
	if (ft_diechecker(plist) || ft_eatchecker(plist))
		return (NULL);
	pthread_mutex_lock(&(plist->prev->philosopher->right_fork));
	ft_printer(plist, "\033[0;32mPhilosopher", "has taken a fork", 0);
	ft_printer(plist, "\033[0;36mPhilosopher", "is thinking", 0);
	pthread_mutex_lock(&(plist->philosopher->right_fork));
	ft_printer(plist, "\033[0;32mPhilosopher", "has taken a fork", 0);
	ft_eat(plist);
	return (NULL);
}

void	*ft_sleep(void *thread)
{
	t_philist	*plist;

	plist = (t_philist *)thread;
	if (ft_diechecker(plist) || ft_eatchecker(plist))
		return (NULL);
	ft_printer(plist, "\033[0;34mPhilosopher", "is sleeping", 0);
	plist->philosopher->turn = 1;
	ft_usleep(plist, plist->philosopher->time_to_sleep);
	ft_think(plist);
	return (NULL);
}

void	*ft_think(void *thread)
{
	t_philist				*plist;
	static pthread_mutex_t	turn = PTHREAD_MUTEX_INITIALIZER;

	plist = (t_philist *)thread;
	if (ft_diechecker(plist) || ft_eatchecker(plist))
		return (NULL);
	ft_printer(plist, "\033[0;36mPhilosopher", "is thinking", 0);
	pthread_mutex_lock(&turn);
	if (plist->philosopher->turn)
	{
		pthread_mutex_unlock(&turn);
		ft_takefork(plist);
	}
	else
	{
		pthread_mutex_unlock(&turn);
		ft_sleep(plist);
	}
	return (NULL);
}

void	asign_turn(t_philist *plist, int size)
{
	while (size)
	{
		if (plist->philosopher->number % 2 != 0)
			plist->philosopher->turn = 1;
		else
			plist->philosopher->turn = 0;
		plist = plist->next;
		size--;
	}
}
