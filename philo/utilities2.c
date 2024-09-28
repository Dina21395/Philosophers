#include "philo.h"

void	ft_sleep(long time_sleep, t_table_data *tbl)
{
	long	start_t;
	long	spend_t;
	long	remain_t;

	start_t = get_curr_time_ml(tbl);
	while (get_curr_time_ml(tbl) - start_t < time_sleep)
	{
		if (is_table_end(tbl))
			break ;
		spend_t = get_curr_time_ml(tbl) - start_t;
		remain_t = time_sleep - spend_t;
		if (remain_t > 1)
			usleep((remain_t * 1000) / 2);
		else
			while (get_curr_time_ml(tbl) - start_t < time_sleep)
				;
	}
}

void	ft_clean_memory(t_table_data *tbl)
{
	int	i;

	i = 0;
	while (i < tbl->num_philos)
	{
		if (pthread_mutex_destroy(&tbl->lst_philos[i].philo_mutex) != 0)
			error_free_exit("fail philo_mutex destroy", tbl);
		i++;
	}
	if (pthread_mutex_destroy(&tbl->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex destroy", tbl);
	if (pthread_mutex_destroy(&tbl->tbl_mutex_print) != 0)
		error_free_exit("fail print_mutex destroy", tbl);
	free(tbl->lst_forks);
	free(tbl->lst_philos);
}
