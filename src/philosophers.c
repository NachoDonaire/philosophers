#include "../includes/philosophers.h"

/*
void	*routineA()
{
	int 	i;

	i = 0;
	while (i++ < 2000)
		a++;
	return (0);
}

void	*routineB()
{
	int	i;

	i = 0;
	while (i < 2001)
	{
		i++;
		a--;
	}
	return (0);
}
*/
int		gemiro = 0;
void	preliminar(t_gen_data *gen_data, char **s)
{
	int	i;

	i = 0;
	gen_data->philos = malloc(sizeof(t_philos_data) * (ft_atoi(s[1]) + 1));
	gen_data->n_philos = malloc(sizeof(int) * (ft_atoi(s[1] + 1)));
	while (i < ft_atoi(s[i]))
	{
		gen_data->n_philos[i] = i;
		i++;
	}
	gen_data->n_philos[i] = -1;
}

void	check_arg(int arg)
{
	if (arg < 5 || arg > 6)
	{
		printf("Arguments needed");
		exit(0);
	}
}

void	*thread_routine_1(void *)
{
	int	i;

	i = 0;
	printf("sumando..\n");
	while (i < 200)
	{
		i++;
		gemiro++;
	}
	return (0);
}

void	*thread_routine_2(void *)
{
	int	i;

	i = 0;
	printf("restando..\n");
	while (i < 200)
	{
		gemiro--;
		i++;
	}
	return (0);
}

int	main(int arg, char **args)
{
	int		argy;
	t_gen_data	gen_data;

	gemiro = 0;
	if (arg != 2)
		return (0);
	preliminar(&gen_data, args);
	if (0 != pthread_create(&gen_data.n_philos[0], NULL, thread_routine_1, &argy))
	{
		printf("no se creo el hilo");
		return (0);
	}
	if (0 != pthread_create(&gen_data.n_philos[1], NULL, thread_routine_2, &argy))
	{
		printf("no se creo el hilo");
		return (0);
	}

	pthread_join(gen_data.n_philos[0], NULL);
	pthread_join(gen_data.n_philos[1], NULL);
	printf("--%d--\n", gemiro);
	return (0);
}





	/*pthread_t	thread_1;
	pthread_t	thread_2;

	if (0 != pthread_create(&thread_1, NULL, routineA, NULL))
	{
		printf("Nose creo el hilo 2");
		return (0);
	}
	if (0 != pthread_create(&thread_2, NULL, routineB, NULL))
	{
		printf("Nose creo el hilo 2");
		return (0);
	}
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	printf("%d\n", a);
	return (0);
	*/
