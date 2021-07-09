#define _GNU_SOURCE
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include "./libft/libft.h"

void send_received(siginfo_t *info)
{
	if (kill(info->si_pid, SIGUSR1) == -1)
	{
		ft_putendl_fd("failed to send signal to client.", 2);
		exit(1);
	}
}

// siguser1 = 0, siguser2 = 1
void	handler(int signo, siginfo_t *info, void *ctx)
{
	unsigned char	c;
	static int		num = 0;
	static int		digit = 0;

	(void)ctx;
	if (digit < 8)
	{
		num = num << 1;
		if (signo == SIGUSR2)
			num += 1;
		digit++;
	}
	if (digit == 8)
	{
		c = num;
		if (c == '\0')
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			send_received(info);
		}
		else
			ft_putchar_fd(c, STDOUT_FILENO);
		num = 0;
		digit = 0;
	}
}

bool	set_signal(){
	struct sigaction	act;

	if (sigemptyset(&act.sa_mask) == -1)
		return (false);
	act.sa_sigaction = handler;
	act.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		return (false);
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		return (false);
	return (true);
}

int	main(int argc, char const *argv[])
{
	pid_t	pid;

	if (argc != 1 || argv[1] != NULL)
	{
		ft_putendl_fd("Invalid argument.", STDOUT_FILENO);
		return (1);
	}
	pid = getpid();
	ft_putstr_fd("pid: ", STDOUT_FILENO);
	ft_putnbr_fd(pid, STDOUT_FILENO);
	ft_putendl_fd("", STDOUT_FILENO);
	if (!set_signal())
		return (1);
	while (1)
		pause();
	return (0);
}
