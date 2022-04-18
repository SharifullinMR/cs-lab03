#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
#include <iostream>
#include <vector>
using namespace std;
void show_histogram_text(const vector<size_t> &bins);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height,string stroke="#990000", string fill = "#66FFFF");
void show_histogram_svg(const vector<size_t>& bins);
void svg_blockwidth(double &BLOCK_WIDTH,bool &block);
#endif // SVG_H_INCLUDED
