/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:44:07 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/17 17:30:19 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_phil_turnthread(void *element)
{
	t_philist 	*plist;

	plist = (t_philist *)element;
	//printf("philo %i before turn %i\n",plist->philosopher->number, plist->philosopher->turn);
	ft_take_rightfork(plist);
	//printf("philo %i during turn %i\n",plist->philosopher->number, plist->philosopher->turn);
	return (NULL);
}

void	*ft_phil_no_turnthread(void *element)
{
	t_philist 	*plist;

	plist = (t_philist *)element;
	//printf("philo %i before turn %i\n",plist->philosopher->number, plist->philosopher->turn);
	ft_sleep(plist);
	//printf("philo %i during turn %i\n",plist->philosopher->number, plist->philosopher->turn);
	return (NULL);
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void	ft_take_rightfork(t_philist *plist)
{
	pthread_mutex_lock(&(plist->philosopher->right_fork));
	printf("\033[0;32mPhilosopher %i has taken a fork\n", plist->philosopher->number);
	ft_take_leftfork(plist);
}

void	ft_take_leftfork(t_philist *plist)
{
	pthread_mutex_lock(&(plist->prev->philosopher->right_fork));
	printf("\033[0;32mPhilosopher %i has taken a fork\n", plist->philosopher->number);
	ft_eat(plist);
}

void	ft_eat(t_philist *plist)
{
	printf("\033[0;33mPhilosopher %i is eating\n", plist->philosopher->number);
	usleep(plist->philosopher->time_to_eat);
	pthread_mutex_unlock(&(plist->philosopher->right_fork));
	pthread_mutex_unlock(&(plist->prev->philosopher->right_fork));
	ft_sleep(plist);
}

void	ft_sleep(t_philist *plist)
{
	printf("\033[0;34mPhilosopher %i is sleeping\n", plist->philosopher->number);
	usleep(plist->philosopher->time_to_sleep);
	ft_think(plist);
}

void	ft_think(t_philist *plist)
{
	printf("\033[0;36mPhilosopher %i is thinking\n", plist->philosopher->number);
	ft_phil_turnthread(&plist->philosopher);
}

void	*ft_die(void *philosopher)
{
	t_philist *plist;

	plist = (t_philist *)philosopher;
	printf("\033[0;35mPhilosopher %i died", plist->philosopher->number);
	pthread_detach(philosopher);
	exit(0);
	return (NULL);
}