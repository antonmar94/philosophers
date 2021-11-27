/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_list_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:43:05 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/27 19:50:05 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_plist_size(t_philist *plist)
{
	int	size;

	if (!plist->next)
		return (1);
	size = 1;
	plist = plist->next;
	while (plist->philosopher->number != 1)
	{
		size++;
		plist = plist->next;
	}
	return (size);
}

t_philosopher	*create_phil(char **argv)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	pthread_mutex_init(&(philosopher->right_fork), NULL);
	philosopher->dead = 0;
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

void	print_plist(t_philist *plist, int size)
{
	int			i;
	t_philist	*aux;

	i = 0;
	aux = plist;
	printf("\n");
	printf("\033[0;31m%65s", " 📚 Philosophers 📚 ");
	printf("\n");
	printf("\033[0;31m%57s", "------------\n");
	while (i < size)
	{
		printf("\033[0mPhilosopher %-3i", i + 1);
		printf("\033[0;32mnumber: \033[0m%-3i",
			aux->philosopher->number);
		printf("\033[0;35mtime to die: \033[0m[%d] ",
			aux->philosopher->time_to_die);
		printf("\033[0;33mtime to eat: \033[0m[%i] ",
			aux->philosopher->time_to_eat);
		printf("\033[0;34mtime to sleep: \033[0m[%i] ",
			aux->philosopher->time_to_sleep);
		printf("\033[0;36mnumber of times to eat: \033[0m[%i]\n ",
			aux->philosopher->number_of_times_toeat);
		aux = aux->next;
		i++;
	}
}
