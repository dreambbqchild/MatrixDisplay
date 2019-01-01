#pragma once
#include <random>

template<int TMax>
class Random
{
private:

	std::random_device seed;
	std::default_random_engine generator;
	std::uniform_int_distribution<size_t> distribution;

public:
	Random() : seed(), generator(seed()), distribution(0, TMax) {}
	size_t Next() { return distribution(generator); }
};