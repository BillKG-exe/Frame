// stats.h

#ifndef STATS_H
#define STATS_H

#include "Series.hpp"

template <typename T>
double mean(std::vector<T> list);

double mean(Series serie);


template <typename T>
double mode(std::vector<T> list);

double mode(Series s);

template <typename T>
double median(std::vector<T> list);

double median(Series s);

template <typename T>
double variance(std::vector<T> list);

double variance(Series s);

template <typename T>
double std_error(std::vector<T> list);

double std_error(Series s);

template <typename T>
double comb(std::vector<T> list);

double comb(Series s);

//void printMessage(const std::string& message);

#endif