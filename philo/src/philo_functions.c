/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:10:37 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/29 16:05:35 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_eatchecker(t_philist *plist)
{
	t_philist	*p_init;

	p_init = plist;
	if (p_init->philo->numeat == 0)
		return (0);
	if (p_init->philo->number_of_times_toeat > 0)
		return (0);
	p_init = p_init->next;
	while (p_init->philo->number != plist->philo->number)
	{
		if (p_init->philo->number_of_times_toeat > 0)
			return (0);
		p_init = p_init->next;
	}
	return (1);
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

int	ft_killp(t_philist *plist, pthread_t philo)
{
	if (*plist->philo->time_left
		>= plist->philo->time_to_die)
	{
		plist->philo->dead = 1;
		pthread_detach(philo);
		pthread_mutex_destroy(&plist->philo->right_fork->mutex_fork);
		ft_printer(plist, "\033[0;35mPhilosopher", "died ☠️", 1);
		return (1);
	}
	return (0);
}

void	ft_take_leftfork(t_philist *plist)
{
	pthread_mutex_lock(&plist->prev->philo->right_fork->mutex_fork);
	if (plist->prev->philo->right_fork->taken == 0
		&& plist->philo->turn == 1)
	{
		ft_printer(plist, "\033[0;32mPhilosopher", "has taken a fork 🍴", 0);
		plist->prev->philo->right_fork->taken++;
	}
	pthread_mutex_unlock(&plist->prev->philo->right_fork->mutex_fork);
}

void	ft_take_rightfork(t_philist *plist)
{
	pthread_mutex_lock(&plist->philo->right_fork->mutex_fork);
	if (plist->philo->right_fork->taken == 0
		&& plist->philo->turn == 1)
	{
		ft_printer(plist, "\033[0;32mPhilosopher", "has taken a fork 🍴", 0);
		plist->philo->right_fork->taken++;
	}
	pthread_mutex_unlock(&plist->philo->right_fork->mutex_fork);
}
