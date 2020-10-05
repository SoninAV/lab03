#include <iostream>
#include "svg.h"
#include <string>
#include <sstream>
#include<cstdio>
vector<string> colors(size_t bin_count)
{
    vector<string> cin_colors(bin_count);
    for (size_t i = 0; i < bin_count; i++)
    {
        getline(cin, cin_colors[i]);
    }
    return cin_colors;
}

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";

}

void svg_text(double left, double baseline, size_t text)
{
    cout << "<text x='" << left << "' y='" << baseline <<"'>" <<text <<"</text>";

}

void svg_rect(double x, double y, double width, double height,string stroke,string fill)
{
    cout << "<rect x='"<<x<< "' y='" <<y<<"' width='" <<width <<"' height='" <<height <<"' stroke='"<<stroke<<"' fill='"<<fill<<"'/>";
}

size_t find_min(const vector<size_t>& bins) {
    size_t min = bins[0];
    for (const auto& bin : bins)
    {
        if (bin < min)
        {
            min = bin;
        }
    }
    return min;
}

size_t find_max(const vector<size_t>& bins) {
    size_t max = bins[0];
    for (const auto& bin : bins)
    {
        if (bin > max)
        {
            max = bin;
        }
    }
    return max;
}

string make_color(const vector<size_t>& bins, size_t bin, size_t max_count) {
    ostringstream os;
    size_t min = find_min(bins);
    size_t max = find_max(bins);
    size_t x;
    if (bin == max)
    {
        x = 1;
    }
    else if (bin == min)
    {
        x = 9;
    }
    else
    {
        x =10 - (bin * 9) / max_count;
    }
    os << x;
    string color = os.str();
    color += color + color;
    return color;
}

/*void show_version(double y, const double TEXT_BSLN)
{
    DWORD dwVersion = GetVersion();

    DWORD mask = 0x0000ffff;
    DWORD version = dwVersion&mask;

    DWORD platform = dwVersion >> 16;

    DWORD mask2 = 0x00ff;
    DWORD version_major = version&mask2;
    DWORD version_minor = version >> 8;

    if ((version & 0x80000000) == 0) {
        char buffer[MAX_COMPUTERNAME_LENGTH+1]="";
        DWORD size =MAX_COMPUTERNAME_LENGTH+1;
        GetComputerNameA(buffer, &size);
        cout << "<text x='" << left << "' y='" << y + 2*TEXT_BSLN << "'>Computer name: " << buffer << "</text>";
    }

    DWORD build = platform;

    cout << "<text x='" << left << "' y='" << y + TEXT_BSLN << "'>Windows v" << version_major << "."
    << version_minor << " (build " << build << ")</text>";
}*/

void show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const size_t MAX_ASTERISK = IMAGE_WIDTH - TEXT_LEFT - TEXT_WIDTH;

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }

    const bool scaling_needed = max_count * BLOCK_WIDTH > MAX_ASTERISK;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);


    double top = 0;
    for (size_t bin : bins) {

        string color = make_color(bins, bin, max_count);

        cout << endl << color << endl;

        size_t height = bin;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_ASTERISK / (max_count * BLOCK_WIDTH);
            height = (size_t)(bin * scaling_factor);
        }

        const double bin_width = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, bin);
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", "#" + color);
        top += BIN_HEIGHT;
    }

    //show_version(top, TEXT_BASELINE);

    svg_end();
}
