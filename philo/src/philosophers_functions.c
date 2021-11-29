/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:10:37 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/29 16:05:35 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_eatchecker(t_philist *plist)
{
	t_philist	*p_init;

	p_init = plist;
	if (p_init->philosopher->numeat == 0)
		return (0);
	if (p_init->philosopher->number_of_times_toeat > 0)
		return (0);
	p_init = p_init->next;
	while (p_init->philosopher->number != plist->philosopher->number)
	{
		if (p_init->philosopher->number_of_times_toeat > 0)
			return (0);
		p_init = p_init->next;
	}
	return (1);
}

int	ft_finisher(t_philist *plist, pthread_t philosopher)
{
	t_philist	*p_init;

	p_init = plist;
	while (1)
	{
		usleep(1000);
		if (p_init->philosopher->dead == 1)
		{
			pthread_detach(philosopher);
			return (0);
		}
		p_init = p_init->next;
		while (p_init->philosopher->number != plist->philosopher->number)
		{
			if (p_init->philosopher->dead == 1)
			{
				pthread_detach(philosopher);
				return (0);
			}
			p_init = p_init->next;
		}
		if (ft_eatchecker(plist) == 1)
			return (0);
	}
	return (1);
}

int	ft_killp(t_philist *plist, pthread_t philosopher)
{
	if (*plist->philosopher->time_left
		>= plist->philosopher->time_to_die)
	{
		plist->philosopher->dead = 1;
		pthread_detach(philosopher);
		pthread_mutex_destroy(&plist->philosopher->right_fork->mutex_fork);
		ft_printer(plist, "\033[0;35mPhilosopher", "died", 1);
		return (1);
	}
	return (0);
}

void	ft_take_leftfork(t_philist *plist)
{
	pthread_mutex_lock(&plist->prev->philosopher->right_fork->mutex_fork);
	if (plist->prev->philosopher->right_fork->taken == 0
		&& plist->philosopher->turn == 1)
	{
		ft_printer(plist, "\033[0;32mPhilosopher", "has taken a fork", 0);
		plist->prev->philosopher->right_fork->taken++;
	}
	pthread_mutex_unlock(&plist->prev->philosopher->right_fork->mutex_fork);
}

void	ft_take_rightfork(t_philist *plist)
{
	pthread_mutex_lock(&plist->philosopher->right_fork->mutex_fork);
	if (plist->philosopher->right_fork->taken == 0
		&& plist->philosopher->turn == 1)
	{
		ft_printer(plist, "\033[0;32mPhilosopher", "has taken a fork", 0);
		plist->philosopher->right_fork->taken++;
	}
	pthread_mutex_unlock(&plist->philosopher->right_fork->mutex_fork);
}
