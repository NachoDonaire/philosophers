/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:40:14 by ndonaire          #+#    #+#             */
/*   Updated: 2022/10/24 13:42:00 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	create_threads(char **args, t_philos_data *philos)
{
	int	i;

	i = 0;
	while (i < ft_atoi(args[1]))
	{
		if (0 != pthread_create(&philos[i].pthread, NULL, routine, &philos[i]))
			printf("no se creo bien el hilo");
		i++;
	}
}

void	join_threads(char **args, t_philos_data *philos)
{
	int	i;

	i = 0;
	while (i < ft_atoi(args[1]))
	{
		pthread_join(philos[i].pthread, NULL);
		i++;
	}
}
