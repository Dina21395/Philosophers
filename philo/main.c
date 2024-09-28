#include "philo.h"

int	main(int argc, char **argv)
{
	t_table_data	tbl_data;

	ft_validate_fill(argc, argv, &tbl_data);
	ft_tbl_data_init(&tbl_data);
	ft_dining_start(&tbl_data);
	ft_clean_memory(&tbl_data);
	return (0);
}
