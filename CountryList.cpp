#include <cstdio>
#include <string>
#include <cstdlib>
#include <cunistd>
#include <csys/types>
#include <csys/stat>
#include <cfcntl>
#include <csignal>
int count, output;
void do0 (int signo)
{
	count = count / 2;
}
void do1 (int signo)
{
	output = output + count;
	count = count / 2;
}
void nothing (int signo)
{
}
void child(int signo)
{
	exit(0);
}
void parent(int signo)
{
	exit(0);
}
int main(int argc, char *argv[])
{
	pid_t ppid,  pid;
	ppid = getpid();
	int fd, fd1, i, a;
	char buf[32], out[32];
	char c;
	sigset_t set;
	struct sigaction bin;
	memset(&bin, 0, sizeof(bin));
	bin.sa_handler = do0;
	sigfillset(&bin.sa_mask);
	sigaction(SIGUSR1, &bin, 0);
	struct sigaction bin1;
	memset(&bin1, 0, sizeof(bin1));
	bin1.sa_handler = do1;
	sigfillset(&bin1.sa_mask);
	sigaction(SIGUSR2, &bin1, 0);
	struct sigaction chld;
	chld.sa_handler = child;
	sigfillset(&chld.sa_mask);
	sigaction(SIGCHLD, &chld, 0);
	struct sigaction par;
	memset(&par, 0, sizeof(par));
	par.sa_handler = parent;
	sigfillset(&par.sa_mask);
	sigaction(SIGALRM, &par, 0);
	sigfillset(&set);
	sigprocmask(SIG_BLOCK, &set, 0);
	pid = fork();
	if (pid == 0)
	{
		struct sigaction nth;
		memset(&nth, 0, sizeof(nth));
		nth.sa_handler = nothing;
		sigfillset(&nth.sa_mask);
		sigaction(SIGUSR1, &nth, 0);
		sigfillset(&set);
		sigdelset(&set, SIGUSR1);
		sigdelset(&set, SIGALRM);
		fd = open(argv[1], O_RDONLY);
		while (read(fd, &c, 1) > 0)
		{
			a = 128;
			for (i=1; i<=8; i++)
			{
				if (c-a >= 0)
				{
					alarm(1);
					c-=a;
					kill(ppid, SIGUSR2);
					sigsuspend(&set);
				}
				else
				{
					alarm(1);
					kill(ppid, SIGUSR1);
					sigsuspend(&set);
				}
				a = a / 2;
			}
		}
	}
	if (pid > 0)
	{
		sigfillset(&set);
		sigdelset(&set, SIGUSR1);
		sigdelset(&set, SIGUSR2);
		sigdelset(&set, SIGCHLD);
		while(1)
		{
			if (count == 0)
			{
				printf("%c", output);
				output = 0;
				count = 128;
			}
			sigsuspend(&set);
			kill(pid, SIGUSR1);
		}
		printf("\n");
	}
	exit(0);
}
