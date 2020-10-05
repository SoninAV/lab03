#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <windows.h>
#include "histogram.h"
#include "svg.h"

using namespace std;

vector<double> input_numbers(istream& in, const size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in, bool prompt) {
    Input data;
    size_t number_count;

    if (prompt)
    {
        cerr << "Enter number count: ";
        in >> number_count;

        cerr << "Enter numbers: ";
        data.numbers = input_numbers(in, number_count);

        cerr << "Enter column count: ";
        in >> data.bin_count;
    }
    else
    {
        in >> number_count;
        data.numbers = input_numbers(in, number_count);
        in >> data.bin_count;
    }

    /*if (data.bin_count == 0)
    {
        data.bin_count = zero_bin_count(number_count);
    }*/


    return data;
}

/*vector <size_t> make_histogram(const vector<double> &numbers,size_t bin_count)
{
    double min;
    double max;
    find_minmax(numbers,min,max);
    vector<size_t> bins(bin_count,0);
    for (double number : numbers)
    {
        size_t bin;
        bin = (number - min) / (max - min) * bin_count;
        if (bin == bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}*/
vector<size_t> make_histogram(const Input& data) {
    vector<size_t> result(data.bin_count);
    double min;
    double max;
    find_minmax(data.numbers, min, max);
    for (double number : data.numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * data.bin_count);
        if (bin == data.bin_count) {
            bin--;
        }
        result[bin]++;
    }

    return result;
}


void show_histogram_text(const vector<size_t> &bins)
{

    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins)
    {
        if (bin < 100)
        {
            cout << ' ';
        }
        if (bin < 10)
        {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++)
        {
            cout << '*';
        }
        cout << '\n';
    }
}

int main()
{
    const auto input = read_input(cin, true);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins);
    /*size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    const auto numbers = input_numbers(cin, number_count);
    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;
    double min, max;

    find_minmax(numbers, min, max);
    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins, bin_count);
    */
    return 0;
}
