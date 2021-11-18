/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:53:10 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/18 18:25:12 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_philist			*list;
	pthread_t			philosopher;
	int					i;
	int					size;

	i = 0;
	if (!ft_test_error(argc, argv))
		exit (-1);
	size = ft_atoi(argv[1]);
	list = create_plist(argv, size);
	print_plist(list, size);
	while (i < size)
	{
		if (list->philosopher->turn)
			pthread_create(&philosopher, NULL, ft_phil_turnthread, list);
		else
			pthread_create(&philosopher, NULL, ft_phil_no_turnthread, list);
		list = list->next;
		i++;
	}
	pthread_join(philosopher, NULL);
	return (0);
}
