#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>


int x = 0;

void sigHandler(int sig) {
	if (x == 0) {
		printf("\n(HINT) Multiplication is repeated addition!\n");
	}
}

int main() {

	signal(SIGUSR1, sigHandler);

	pid_t pid = fork();

	if (pid == -1) {
		return -1;
	}

	if (pid == 0) { // pid 0 == child process
		sleep(5);
		kill(getppid(), SIGUSR1); // If no answer after delay, signal parent
	}
	else {
//		struct sigaction sa{};
//		sa.sa_flags = SA_RESTART;
//		sa.sa_handler = &sigHandler;
//		sigaction(SIGUSR1, &sa, NULL);

		printf("What is 3 x 5: ");
		scanf("%d", &x);
		if (x == 15) {
			printf("Correct.\n");
		} else {
			printf("Wrong!\n");
		}
		wait(NULL);
	}
	return 0;
}
