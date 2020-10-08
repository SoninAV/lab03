#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

#include <vector>
#include <string>

using namespace std;

struct Input {
    std::vector<double> numbers;
    size_t bin_count;
};

void show_histogram_text(vector<size_t> bins);
void find_minmax(const vector<double>& numbers, double& min, double& max);


#endif // HISTOGRAM_H_INCLUDED
