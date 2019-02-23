#pragma once

#include <functional>

void nop(void*);

int eg_prand();

void dispatch_after_frame(std::function<void()> func);

template<typename T, int sz>
constexpr size_t countof_array(const T(&)[sz])
{
	return sz;
}

template<typename T, int sz>
constexpr size_t sizeof_array(const T(&)[sz])
{
	return sz * sizeof(T);
}

template<typename T>
bool within_rectangle(T x, T y, T x1, T y1, T x2, T y2)
{
	return x > x1 && y > y1 && x < x2 && y < y2;
}