/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_list_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:43:05 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/29 16:05:44 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	asign_turn(t_philist *plist, int size)
{
	int	nolast;

	nolast = 0;
	if (size % 2 != 0 && size != 1)
		nolast = 1;
	while (size)
	{
		if (plist->philosopher->number % 2 != 0)
			plist->philosopher->turn = 1;
		else
			plist->philosopher->turn = 0;
		plist = plist->next;
		size--;
	}
	if (nolast)
		plist->philosopher->turn = 0;
}

t_fork	*create_fork(void)
{
	t_fork	*fork;

	fork = (t_fork *)malloc(sizeof(t_fork));
	fork->taken = 0;
	pthread_mutex_init(&(fork->mutex_fork), NULL);
	return (fork);
}

t_philosopher	*create_phil(char **argv)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->right_fork = create_fork();
	philosopher->time_to_die = ft_atoi(argv[2]);
	philosopher->count = 0;
	philosopher->time_left = &philosopher->count;
	philosopher->time_to_eat = ft_atoi(argv[3]);
	philosopher->time_to_sleep = ft_atoi(argv[4]);
	if (!argv[5])
	{
		philosopher->numeat = 0;
		philosopher->number_of_times_toeat = 0;
	}
	else
	{
		philosopher->numeat = 1;
		philosopher->number_of_times_toeat = ft_atoi(argv[5]);
	}
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

t_philist	*create_plist(char **argv, int size)
{
	t_philist		*list;
	t_philist		*list_init;
	t_philist		*aux;
	int				i;
	int				esto;

	i = 1;
	list = create_pnode(argv);
	list->philosopher->number = 1;
	list_init = list;
	while (++i <= size)
	{
		list->next = create_pnode(argv);
		aux = list;
		list = list->next;
		list->prev = aux;
		list->philosopher->number = i;
	}
	list->next = list_init;
	list_init->prev = list;
	esto = list->philosopher->time_to_die;
	asign_turn(list, size);
	list = list->next;
	return (list);
}
