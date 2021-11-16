/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:19:05 by antonmar          #+#    #+#             */
/*   Updated: 2021/11/16 11:14:29 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H
# include <stdio.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct philosopher
{
	int	number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_toeat;
}	t_philosopher;
typedef struct philosopher_list
{
	t_philosopher			*philosopher;
	struct philosopher_list	*next;
	struct philosopher_list	*prev;
}	t_philist;
int				ft_test_error(char **argv);
t_philosopher	*create_phil(char **argv);
t_philist		*create_pnode(char **argv);
t_philist		*create_plist(char **argv);
void			print_plist(t_philist *plist, int size);

#endif        