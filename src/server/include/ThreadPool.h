/*
 * ThreadPool.h
 */

#ifndef SRC_THREADPOOL_H_
#define SRC_THREADPOOL_H_

#include "Task.h"
#include <queue>
#include <pthread.h>
using namespace std;

class ThreadPool {
public:
	ThreadPool(int threads_num);
	void addTask(Task *task);
	void terminate();
	void joinThreads();
	virtual ~ThreadPool();
private:
	int num_of_threads;
	queue<Task *> tasksQueue;
	pthread_t * threads;
	void executeTasks();
	bool stopped;
	pthread_mutex_t lock;
	static void *execute(void *arg);
};

#endif /* SRC_THREADPOOL_H_ */
