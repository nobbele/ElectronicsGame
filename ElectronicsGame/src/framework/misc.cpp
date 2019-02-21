#include "misc.h"
#include <random>
#include <time.h>

void nop(void*)
{
	return;
}

std::mt19937 mt((unsigned int)time(0));
std::uniform_int_distribution<int> dist(0);

std::vector<std::function<void()>> after_frame_queue;

int eg_prand()
{
	return dist(mt);
}

void dispatch_after_frame(std::function<void()> func)
{
	after_frame_queue.push_back(func);
}