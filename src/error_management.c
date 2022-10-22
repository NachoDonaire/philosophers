#include "../includes/philosophers.h"

int	check_error(char **s, int arg)
{
	int	i;
	int	y;

	i = 1;
	y = 0;
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
	i = 1;
	while (i < arg)
	{
		if (ft_atoi(s[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}
