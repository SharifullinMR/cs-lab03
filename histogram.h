#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include <vector>
using namespace std;
void find_minmax(const vector<double> &numbers, double &min, double &max);
struct Input {
    vector<double> numbers;
    size_t bin_count;
};
#endif // HISTOGRAM_H_INCLUDED
