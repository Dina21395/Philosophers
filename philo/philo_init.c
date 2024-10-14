#include "philo.h"

void	fork_assigment_init(int i, t_table_data *tbl)
{
	if ((i + 1) % 2 == 0)
	{
		tbl->lst_philos[i].r_fork = &tbl->lst_forks[i];
		tbl->lst_philos[i].l_fork = &tbl->lst_forks[(i + 1) % tbl->num_philos];
	}
	else
	{
		tbl->lst_philos[i].r_fork = &tbl->lst_forks[(i + 1) % tbl->num_philos];
		tbl->lst_philos[i].l_fork = &tbl->lst_forks[i];
	}
}

void	lst_philo_init(t_table_data *tbl)
{
	int	i;

	i = -1;
	tbl->lst_philos = (t_philo *)malloc(sizeof(t_philo) * tbl->num_philos);
	if (!tbl->lst_philos)
		error_free_exit("philo memory reservation error", tbl);
	while (++i < tbl->num_philos)
	{
		tbl->lst_philos[i].philo_id = i + 1;
		tbl->lst_philos[i].is_max_num_of_meals = 0;
		tbl->lst_philos[i].num_of_eaten = 0;
		tbl->lst_philos[i].last_eating_time = 0;
		tbl->lst_philos[i].tb_data = tbl;
		fork_assigment_init(i, tbl);
		if (pthread_mutex_init(&tbl->lst_philos[i].philo_mutex, NULL) != 0)
			error_free_exit("philo Mutex initialization failed", tbl);
	}
}

void	ft_tbl_data_init(t_table_data *tbl_data)
{
	int	i;

	i = 0;
	tbl_data->is_tbl_end = 0;
	tbl_data->is_all_created = 0;
	tbl_data->count_running_philos = 0;
	tbl_data->lst_forks = (t_fork *)malloc(sizeof(t_fork)
			* tbl_data->num_philos);
	if (!tbl_data->lst_forks)
		error_free_exit("unexcepected error during forks memory reservation",
			tbl_data);
	while (i < tbl_data->num_philos)
	{
		tbl_data->lst_forks[i].fork_id = i + 1;
		if (pthread_mutex_init(&tbl_data->lst_forks[i].fork_mutex, NULL) != 0)
			error_free_exit("Fork Mutex initialization failed", tbl_data);
		i++;
	}
	lst_philo_init(tbl_data);
	if (pthread_mutex_init(&tbl_data->tbl_mutex, NULL) != 0)
		error_free_exit("Table Mutex initialization failed", tbl_data);
	if (pthread_mutex_init(&tbl_data->tbl_mutex_print, NULL) != 0)
		error_free_exit("Table Mutex Print initialization failed", tbl_data);
}
