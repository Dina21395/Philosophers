#include "philo.h"

void	lock_forks(t_philo *curr_philo)
{
	if (pthread_mutex_lock(&curr_philo->r_fork->fork_mutex) != 0)
		error_free_exit("fail Right fork mutex lock", curr_philo->tb_data);
	print_philo_state(TAKEFORK, curr_philo);
	if (pthread_mutex_lock(&curr_philo->l_fork->fork_mutex) != 0)
		error_free_exit("fail left fork mutex lock", curr_philo->tb_data);
	print_philo_state(TAKEFORK, curr_philo);
}

void	unlock_fork(t_philo *curr_philo)
{
	if (pthread_mutex_unlock(&curr_philo->r_fork->fork_mutex) != 0)
		error_free_exit("fail Right fork mutex unlock", curr_philo->tb_data);
	if (pthread_mutex_unlock(&curr_philo->l_fork->fork_mutex) != 0)
		error_free_exit("fail left fork mutex unlock", curr_philo->tb_data);
}

void	create_threads(t_table_data *tbl_data)
{
	int	i;

	i = 0;
	if (tbl_data->num_philos == 1)
	{
		if ((pthread_create(&tbl_data->lst_philos[0].philo_thread, NULL,
					one_philo_th_handler, &tbl_data->lst_philos[0])) != 0)
			error_free_exit("fail thread creation", tbl_data);
	}
	else
	{
		while (i < tbl_data->num_philos)
		{
			if ((pthread_create(&tbl_data->lst_philos[i].philo_thread, NULL,
						philo_th_handler, &tbl_data->lst_philos[i])) != 0)
				error_free_exit("fail thread creation", tbl_data);
			i++;
		}
	}
	if ((pthread_create(&tbl_data->death_monitor_thread, NULL,
				death_monitor_handler, tbl_data)) != 0)
		error_free_exit("fail death monitor thread creation", tbl_data);
}

void	end_table(t_table_data *tbl_data)
{
	if (pthread_mutex_lock(&tbl_data->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex lock", tbl_data);
	tbl_data->is_tbl_end = 1;
	if (pthread_mutex_unlock(&tbl_data->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex unlock", tbl_data);
}
