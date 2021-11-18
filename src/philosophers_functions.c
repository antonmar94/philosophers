/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:10:37 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/18 14:59:27 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	asign_parity(t_philist *plist, int size)
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

t_philist	*create_plist(char **argv, int size)
{
	t_philist		*list;
	t_philist		*list_init;
	t_philist		*aux;
	int				i;

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
	asign_parity(list, size);
	return (list_init);
}

int		ft_plist_size(t_philist *plist)
{
	t_philist	*aux;
	int			tam;

	tam = 0;
	aux = plist;
	aux = aux->next;
	while (aux->philosopher->number != plist->philosopher->number)
	{
		aux = aux->next;
		tam++;
	}
	return (tam);
}

void	print_plist(t_philist *plist, int size)
{
	int	i;

	i = 0;
	printf("\n");
	printf("\033[0;31m%65s", " 📚 Philosophers 📚 ");
	printf("\n");
	printf("\033[0;31m%57s", "------------");
	printf("\n");
	while (i < size)
	{
		printf("\033[0mPhilosopher %-3i", i + 1);
		printf("\033[0;32mnumber: \033[0m%-3i",
			plist->philosopher->number);
		printf("\033[0;35mtime to die: \033[0m[%i] ",
			plist->philosopher->time_to_die);
		printf("\033[0;33mtime to eat: \033[0m[%i] ",
			plist->philosopher->time_to_eat);
		printf("\033[0;34mtime to sleep: \033[0m[%i] ",
			plist->philosopher->time_to_sleep);
		printf("\033[0;36mnumber of times to eat: \033[0m[%i] ",
			plist->philosopher->number_of_times_toeat);
		printf("\n");
		plist = plist->next;
		i++;
	}
}
