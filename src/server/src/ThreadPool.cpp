/*
 * ThreadPool.cpp
 */

#include "ThreadPool.h"
#include <unistd.h>

ThreadPool::ThreadPool(int threads_num): stopped(false) {
	threads = new pthread_t[threads_num];
	num_of_threads = threads_num;
	for (int i = 0; i < threads_num; i++) {
		pthread_create(threads + i, NULL, execute, this);
	}
	pthread_mutex_init(&lock, NULL);
}

ThreadPool::~ThreadPool() {
	delete[] threads;
}

void ThreadPool::terminate() {
	pthread_mutex_destroy(&lock);
	stopped = true;
	joinThreads();
}

void* ThreadPool::execute(void *arg) {
	ThreadPool *pool = (ThreadPool *) arg;
	pool->executeTasks();
	return NULL;
}

void ThreadPool::joinThreads() {
	for (int i = 0; i < num_of_threads; i++) {
		pthread_cancel(*(threads + i));
		pthread_join(*(threads + i), NULL);
	}
}

void ThreadPool::addTask(Task *task) {
	tasksQueue.push(task);
}

void ThreadPool::executeTasks() {
	while (!stopped) {
		pthread_mutex_lock(&lock);
		if (!tasksQueue.empty()) {
			Task *task = tasksQueue.front();
			tasksQueue.pop();
			pthread_mutex_unlock(&lock);
			task->execute();
		} else {
			pthread_mutex_unlock(&lock);
			sleep(1);
		}
	}
}
