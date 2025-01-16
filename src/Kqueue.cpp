#include "Kqueue.hpp"

void Kqueue::initialize() {
	kqueueFd = kqueue();
	if (kqueueFd == -1) {
		perror("kqueue creation failed");
		exit(EXIT_FAILURE);
	}
	std::cout << "Kqueue initialized with FD: " << kqueueFd << std::endl;
}

Kqueue::Kqueue() {
	initialize();
}

Kqueue::~Kqueue() {
	if (close(kqueueFd) == -1) {
		perror("Failed to close kqueue");
	} else {
		std::cout << "Kqueue closed." << std::endl;
	}
}

void Kqueue::addFd(int fd, int filter, int flags) {
	struct kevent event;
	EV_SET(&event, fd, filter, flags, 0, 0, nullptr);
	if (kevent(kqueueFd, &event, 1, nullptr, 0, nullptr) == -1) {
		perror("Failed to add FD to kqueue");
	} else {
		std::cout << "FD: " << fd << " added with filter: " << filter << std::endl;
	}
}

void Kqueue::removeFd(int fd, int filter) {
	struct kevent event;
	EV_SET(&event, fd, filter, EV_DELETE, 0, 0, nullptr);
	if (kevent(kqueueFd, &event, 1, nullptr, 0, nullptr) == -1) {
		perror("Failed to remove FD from kqueue");
	} else {
		std::cout << "FD: " << fd << " removed." << std::endl;
	}
}

static const int MAX_EVENTS = 10;
static const int TIMEOUT_MS = -1;

std::vector< std::pair<int, int> > Kqueue::pollEvents() {
	struct kevent events[MAX_EVENTS];
	struct timespec timeout;
	struct timespec *timeoutPtr = nullptr;

	if (TIMEOUT_MS >= 0) {
		timeout.tv_sec = TIMEOUT_MS / 1000;
		timeout.tv_nsec = (TIMEOUT_MS % 1000) * 1000000;
		timeoutPtr = &timeout;
	}

	int eventCount = kevent(kqueueFd, nullptr, 0, events, MAX_EVENTS, timeoutPtr);
	if (eventCount == -1) {
		perror("Error polling kqueue events");
		return std::vector<std::pair<int, int> >(); // 빈 벡터 반환
	}
	std::cout << "Event count: " << eventCount << std::endl;

	std::vector< std::pair<int, int> > activeEvents;
	for (int i = 0; i < eventCount; ++i) {
		activeEvents.push_back(std::make_pair(events[i].ident, events[i].filter));
		std::cout << "Event occurred - FD: " << events[i].ident
				  << ", Filter: " << events[i].filter << std::endl;
	}

	return activeEvents;
}
