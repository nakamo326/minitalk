#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int	main(int argc, char const *argv[])
{
	pid_t pid;

	pid = getpid();

	return 0;
}
