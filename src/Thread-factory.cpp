#include <stdio.h>
#include <iostream>
#include <thread>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <mutex>
#include <semaphore.h>
#include <fcntl.h>
using namespace std;

struct sigaction event;


sem_t *semaphore;

volatile sig_atomic_t usr1Happened = 1;

void SIGUSR1Handler(int sig);

void threadfunc(){
	printf("Thread %d created!\n", this_thread::get_id());
	while(true){
		sem_wait(semaphore);
		printf("Thread %d unblocked!\n", this_thread::get_id());
		sleep(5);
	}
}

int main() {
	unsigned short numThreads;
	printf("Enter the number of threads to spawn(1-255): ");
	do{

		cin >> numThreads;
		cin.ignore(256, '\n');
		cin.clear();
	}while(cin.fail());

	thread threads[numThreads];

	semaphore = sem_open("threads", O_CREAT, S_IRWXO | S_IRWXU, 0);

	for(int i = 0; i < numThreads; i++){
		threads[i] = thread(threadfunc);
	}
	for(int i = 0; i < numThreads; i++){
		threads[i].join();
	}


	event.sa_flags = 0;
	event.sa_handler = SIGUSR1Handler;

	sigemptyset(&event.sa_mask);
	if(sigaction(SIGUSR1, &event, NULL) == -1){
		perror("sigaction");
		exit(1);
	}

	while(usr1Happened);

	sleep(10);

	sem_close(semaphore);

	sem_destroy(semaphore);
	return 0;
}

void SIGUSR1Handler(int sig){
	cout << "SIGUSR1 processed on " << getpid() << endl;
	usr1Happened = 0;
}
