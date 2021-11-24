/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:53:10 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/24 19:59:12 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_counter(void *element)
{
	t_philist 		*plist;
	struct timeval	start;
	struct timeval	end;

	plist = (t_philist *)element;
	while (1)
	{
		gettimeofday(&start, NULL);
		usleep(1000);
		gettimeofday(&end, NULL);
		*plist->philosopher->time_left -= ft_difftime(&start, &end);
		if (*plist->philosopher->time_left <= 0) //tengo que matarlos y que pare
			ft_die(plist);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philist			*plist;
	pthread_t			philosopher;
	int					i;
	int					size;

	i = 0;
	
	if (!ft_test_error(argc, argv))
		return (-1);
	size = ft_atoi(argv[1]);
	plist = create_plist(argv, size);
	plist->philosopher->start = ft_thistime();
	while (i < size)
	{
		plist->next->philosopher->start = plist->philosopher->start;
		plist = plist->next; 
		i++;
	}
	i = 0;
	while (i < size)
	{
		pthread_create(&philosopher, NULL, ft_phil_turnthread, plist);
		plist = plist->next; 
		i++;
	}
	pthread_join(philosopher, NULL);
	return (0);
}
