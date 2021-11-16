/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:53:10 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/16 11:16:08 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_philist	*list;
	int			size;

	size = ft_atoi(argv[1]);
	if (argc < 5 || argc > 6)
	{
		write(1, "Error, wrong number of arguments\n", 34);
		exit (-1);
	}
	if (!ft_test_error(argv))
	{
		write(1, "Error, wrong argument\n", 25);
		exit (-1);
	}
	list = create_plist(argv);
	print_plist(list, size);
	return (0);
}
