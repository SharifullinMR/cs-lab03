#include <iostream>
#include <sstream>
#include <string>
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
size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast<const char*>(items), data_size);
    return data_size;
}
Input
download(const string& address) {
    stringstream buffer;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    if(curl){
        CURLcode res; char *ip;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res!=CURLE_OK){
            cerr<<" Error text  = "<<curl_easy_strerror(res);
            exit(1);
        }
        if ((res == CURLE_OK ) && !curl_easy_getinfo(curl, CURLINFO_PRIMARY_IP, &ip) && ip) {
            cerr<<("IP: %s\n", ip);
        }

    }
    curl_easy_cleanup(curl);
    return read_input(buffer,false);

}
int main(int argc,char* argv[])
{
    Input input;
    if (argc>1){
        input = download(argv[1]);
    }
    else{
        input = read_input(cin,true);
    }
    const auto bins = make_histogram(input);
    show_histogram_svg(bins);
    return 0;
}

