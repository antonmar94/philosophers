/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:10:37 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/27 19:50:05 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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

int	ft_diechecker(t_philist *plist)
{
	t_philist	*p_init;

	p_init = plist;
	if (p_init->philosopher->dead == 1)
		return (1);
	p_init = p_init->next;
	while (p_init->philosopher->number != plist->philosopher->number)
	{
		if (p_init->philosopher->dead == 1)
			return (1);
		p_init = p_init->next;
	}
	return (0);
}

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

int	ft_killp(t_philist *plist, pthread_t philosopher)
{
	if (*plist->philosopher->time_left
		>= plist->philosopher->time_to_die)
	{
		plist->philosopher->dead = 1;
		pthread_detach(philosopher);
		ft_printer(plist, "\033[0;35mPhilosopher", "died", 1);
		return (1);
	}
	return (0);
}

int	ft_checker(t_philist *plist, pthread_t philosopher)
{
	time_t			start;
	time_t			sum;
	int				size;
	int				i;

	size = ft_plist_size(plist);
	while (1)
	{
		start = ft_thistime();
		ft_usleep(plist, 1);
		sum = ft_thistime() - start;
		i = 0;
		while (i < size)
		{
			*plist->philosopher->time_left += sum;
			if (ft_killp(plist, philosopher) == 1)
				return (0);
			if (ft_eatchecker(plist))
				return (0);
			plist = plist->next;
			i++;
		}
	}
	return (1);
}
