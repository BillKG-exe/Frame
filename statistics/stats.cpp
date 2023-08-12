#include "stats.h"
#include <unordered_map>
#include <algorithm>
#include <cmath>

template <typename T>
double mean(std::vector<T> list) {
    double m = 0.0;

    for(auto val : list)  m += val;

    return m / list.size();
}

double mean(Series s) {
    double m = 0.0;
    
    for(int i = 0; i < s.size(); i++) m += s.get(i);

    return m / s.size();
}


template <typename T>
double mode(std::vector<T> list) {
    std::unordered_map<int, int> valueCount;

    // Count the occurrences of each value in the dataset
    for (int value : list) {
        valueCount[value]++;
    }

    int mode = 0;
    int maxCount = 0;

    // Find the mode by identifying the value with the highest count
    for (const auto& entry : valueCount) {
        if (entry.second > maxCount) {
            maxCount = entry.second;
            mode = entry.first;
        }
    }

    return mode;
}

double mode(Series s) {
    std::unordered_map<int, int> valueCount;

    // Count the occurrences of each value in the dataset
    for(int i = 0; i < s.size(); i++) valueCount[s.get(i)]++;

    int mode = 0;
    int maxCount = 0;

    // Find the mode by identifying the value with the highest count
    for (const auto& entry : valueCount) {
        if (entry.second > maxCount) {
            maxCount = entry.second;
            mode = entry.first;
        }
    }

    return mode;
}

template <typename T>
double median(std::vector<T> list) {
    std::sort(list.begin(), list.end());

    if(list.size() % 2 == 0) {
        int mid = list.size() / 2;
        return (list[mid] + list[mid+1]) / 2;
    }
    
    return list[list.size() / 2];
}

/* bool compareSeries(const Series &s1, const Series &s2) {
    return s1.age < s2.age;
} */

double median(Series s) {
    s.sort();

    if(s.size() % 2 == 0) {
        int mid = s.size() / 2;
        return (s.get(mid) + s.get(mid + 1)) / 2;
    } 

    return s.get(s.size() / 2);
}

template <typename T>
double variance(std::vector<T> list, bool sample=true) {
    double mn = mean(list);
    double var = 0.0;

    for(auto val : list) {
        var += (val - mn) * (val - mn);
    }

    return sample? var / (list.size() - 1) : var / list.size();
}

double variance(Series s, bool sample=true) {
    double mn = mean(s);
    double var = 0.0;

    for(auto val : s.toVector()) {
        var += (val - mn) * (val - mn);
    }

    return sample? var / (s.size() - 1) : var / s.size();
}

template <typename T>
double std_dev(std::vector<T> list) {
    return pow(variance(list), 0.5);
}

double std_dev(Series s) {
    return pow(variance(s, true), 0.5);
}

template <typename T>
double comb(std::vector<T> list) {

}

double comb(Series s) {

}