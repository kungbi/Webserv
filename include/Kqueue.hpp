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

    void initialize();

public:
    Kqueue();
    ~Kqueue();

    void addFd(int fd, int filter, int flags);
    void removeFd(int fd, int filter);
    std::vector< std::pair<int, int> > pollEvents(int maxEvents, int timeoutMs);
};


#endif