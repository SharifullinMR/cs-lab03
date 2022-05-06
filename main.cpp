#include <iostream>
#include <vector>
#include "histogram.h"
#include "SVG.h"
using namespace std;
vector<double> input_numbers(istream& in,size_t count){
    vector<double> result(count);
    for (size_t i = 0; i<count; i++)
    {
        in >> result[i];
    }
    return result;
}
vector<size_t> make_histogram(const vector<double> &numbers, size_t bin_count)
{
    double min,max;
    find_minmax(numbers, min , max);
    double bin_size = (max-min)/bin_count;
    vector <size_t> bins(bin_count, 0);
    for (double number_count : numbers)
    {
        bool found = false;
        for(size_t j = 0; j < (bin_count-1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + ( j + 1 ) * bin_size;
            if ((lo <= number_count) && (number_count < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[bin_count-1]++;
        }
    }
    return bins;
}
int main()
{
    size_t number_count;
    cerr<<"Enter number count:";
    cin >> number_count;
    cerr<<"Enter numbers:";
    const auto numbers = input_numbers(cin,number_count);
    size_t bin_count;
    cerr <<"Enter bin count:";
    cin >> bin_count;
    const auto bins = make_histogram(numbers,bin_count);
    show_histogram_svg(bins);
    return 0;
}

