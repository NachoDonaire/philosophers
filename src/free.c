#include "../includes/philosophers.h"

void	needed_free(t_philos_data *philos, t_gen_data *gen_data)
{
	if (gen_data->n_philos)
		free(gen_data->n_philos);
	if (gen_data->forks)
		free(gen_data->forks);
	free(gen_data);
	free(philos);
}
