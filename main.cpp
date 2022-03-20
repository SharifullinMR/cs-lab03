#include <iostream>
#include <vector>
using namespace std;
vector<double> input_numbers(size_t count){
    vector<double> result(count);
    for (size_t i = 0; i<count; i++)
    {
        cin >> result[i];
    }
    return result;
}
void find_minmax(const vector<double> &numbers, double &min, double &max){
    min = numbers[0];
    max = numbers[0];
    for (double number : numbers)
    {
        if (number < min )
        {
            min = number;
        }
        else if (number>max)
        {
            max = number;
        }

    }

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
void show_histogram_text(const vector<size_t> &bins){
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1 ;
    size_t max_bin = bins[0];
    for (size_t bin : bins){
        if (bin>max_bin){
            max_bin=bin;
        }
    }
    for (size_t bin: bins)
    {
        double height = bin;
        if (max_bin > MAX_ASTERISK){
            height = MAX_ASTERISK * (static_cast<double>(bin)/max_bin);
        }
        if (bin < 100){
            cout<<" ";
        }
        if (bin < 10){
            cout<<" ";
        }
        cout<<bin<<"|";
        for (size_t i = 0; i<height; i++){
            cout<<"*";
        }
        cout<<endl;
    }
}
int main()
{
    size_t number_count;
    cerr<<"Enter number count:";
    cin >> number_count;
    cerr<<"Enter numbers:";
    const auto numbers = input_numbers(number_count);
    size_t bin_count;
    cerr <<"Enter bin count:";
    cin >> bin_count;
    const auto bins = make_histogram(numbers,bin_count);
    show_histogram_text(bins);
    return 0;
}
