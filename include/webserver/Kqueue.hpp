#ifndef KQUEUE_HPP
# define KQUEUE_HPP

#include <iostream>
#include <vector>
#include <sys/event.h>
#include <sys/types.h>
#include <unistd.h>

class Kqueue {
private:
	int kqueueFd;
	int maxEvents;

	void initialize();

public:
	Kqueue(int maxEvents);
	~Kqueue();

	void addFd(int fd, int filter, int flags);
	void removeFd(int fd, int filter);
	struct kevent* pollEvents();
};


#endif