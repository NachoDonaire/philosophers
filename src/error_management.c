/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:36:49 by ndonaire          #+#    #+#             */
/*   Updated: 2022/10/24 13:39:50 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_argy(int arg)
{
	if (arg < 5 || arg > 6)
		return (1);
	return (0);
}

int	check_num(int arg, char **s)
{
	int	i;

	i = 1;
	while (i < arg)
	{
		if (ft_atoi(s[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_error(char **s, int arg)
{
	int	i;
	int	y;

	i = 1;
	y = 0;
	if (check_argy(arg) == 1)
		return (1);
	while (i < arg)
	{
		while (s[i][y])
		{
			if (s[i][y] < '0' || s[i][y] > '9')
				return (1);
			y++;
		}
		y = 0;
		i++;
	}
	return (check_num(arg, s));
}
