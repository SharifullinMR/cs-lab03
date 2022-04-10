#include "histogram.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}
void test_negative(){
    double min = 0;
    double max = 0;
    find_minmax({-11, -9, -2003}, min, max);
    assert(min == -2003);
    assert(max == -9);
}
void test_identical(){
    double min = 0;
    double max = 0;
    find_minmax({7, 7, 7}, min, max);
    assert(min == 7);
    assert(max == 7);
}
void test_one(){
    double min = 0;
    double max = 0;
    find_minmax({14}, min, max);
    assert(min == 14);
    assert(max == 14);
}
void test_empty(){
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}
int
main() {
    test_positive();
    test_negative();
    test_identical();
    test_one();
    test_empty();
}
