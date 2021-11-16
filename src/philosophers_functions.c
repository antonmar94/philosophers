/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:10:37 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/16 12:12:36 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philist	*create_plist(char **argv)
{
	t_philist		*list;
	t_philist		*list_init;
	t_philist		*aux;
	int				i;
	int				size;

	i = 0;
	list = create_pnode(argv);
	list->philosopher->number = 1;
	list_init = list;
	size = ft_atoi(argv[1]);
	while (i < size)
	{
		list->next = create_pnode(argv);
		aux = list;
		list = list->next;
		list->prev = aux;
		list->philosopher->number = i + 2;
		i++;
	}
	list->next = list_init;
	return (list_init);
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
	printf("\033[0m");
	while (i < size)
	{
		printf("Philosopher %-3i", i + 1);
		printf("\033[0;32mnumber: \033[0m%-3i", plist->philosopher->number);
		printf("\033[0;35mtime to die: \033[0m[%i] ", plist->philosopher->time_to_die);
		printf("\033[0;33mtime to eat: \033[0m[%i] ", plist->philosopher->time_to_eat);
		printf("\033[0;34mtime to sleep: \033[0m[%i] ", plist->philosopher->time_to_sleep);
		printf("\033[0;36mnumber of times to eat: \033[0m[%i] ", plist->philosopher->number_of_times_toeat);
		printf("\n");
		plist = plist->next;
		i++;
	}
}