#include <iostream>
#include <vector>
#include "histogram.h"
#include "SVG.h"
#include <curl/curl.h>
using namespace std;
vector<double> input_numbers(istream& in,size_t count){
    vector<double> result(count);
    for (size_t i = 0; i<count; i++)
    {
        in >> result[i];
    }
    return result;
}
Input read_input(istream& in, bool prompt){
    Input data;
    size_t number_count;
    if (prompt){
            cerr<<"Enter number count:";
    }
    in >> number_count;
    if (prompt){
    cerr<<"Enter numbers:";
    }
    data.numbers = input_numbers(in,number_count);
    if (prompt){
    cerr <<"Enter bin count:";
    }
    in>>data.bin_count;
    return data;
}
vector<size_t> make_histogram(Input input)
{
    double min,max;
    find_minmax(input.numbers, min , max);
    double bin_size = (max-min)/input.bin_count;
    vector <size_t> bins(input.bin_count, 0);
    for (double number_count : input.numbers)
    {
        bool found = false;
        for(size_t j = 0; j < (input.bin_count-1) && !found; j++)
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
            bins[input.bin_count-1]++;
        }
    }
    return bins;
}
int main(int argc,char* argv[])
{
    if (argc>1){
        cout<<"argc = "<<argc<<endl;
        for(size_t i = 0; i<argc; i ++ ){
            cout<<"argv["<<i<<"] = "<<argv[i]<<endl;
        }
        return 0;
    }
    curl_global_init(CURL_GLOBAL_ALL);
    const auto input = read_input(cin,true);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins);
    return 0;
}

