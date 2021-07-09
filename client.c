#include "minitalk.h"

int	put_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	send_string(pid_t serv, const char *str)
{
	unsigned char	c;
	int				i;
	int				j;

	i = 0;
	while (str[i] != '\0')
	{
		c = str[i];
		j = 0;
		while (j < 8)
		{
			if (c % 2 == 0)
				kill(serv, SIGUSR1);
			else
				kill(serv, SIGUSR2);
			c /= 2;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char const *argv[])
{
	pid_t	serv;

	if (argc != 3)
		return (put_error("invalid arguments."));
	serv = ft_atoi(argv[1]);
	signal(SIGUSR1, SIG_IGN);
	signal(SIGUSR2, SIG_IGN);
	send_string(serv, argv[2]);
	return (EXIT_SUCCESS);
}
