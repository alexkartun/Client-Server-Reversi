/*
 * Task.h
 */

#ifndef SRC_TASK_H_
#define SRC_TASK_H_

class Task {
public:
	Task(void *(*func)(void *arg), void *arg):
		func(func), arg(arg) {}
	void execute() {
		func(arg);
	}
	virtual ~Task() {}
private:
	void *(*func)(void *arg);
	void *arg;
};

#endif /* SRC_TASK_H_ */
