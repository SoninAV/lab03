
#include "svg.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include<cstdio>
#include<windows.h>
using namespace std;

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
void svg_text(double left, double baseline, string text)
{

cout<< "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>" <<endl;

}

void svg_rect(double x, double y, double wid, double heig, string stroke, string fill = "white")
{

cout<< "<rect x='" << x << "' y='" << y << "' width='" <<wid<< "' height='" <<heig<< "' stroke='" << stroke << "' fill='" << fill << "'/>" <<endl;

};

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
void show_histogram_svg(const vector<size_t>& bins, size_t bin_count, bool flag, const string& address, vector<string>& colors)
{
    DWORD info = GetVersion();
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;
    mask = 0x000000ff;
    DWORD platform = info >> 16;
    DWORD version_major = version & mask;
    DWORD version_minor = version >> 8;
    DWORD build;

    if ((info & 0x80000000) == 0)
    {
        build = platform;
        //   printf("Windows v%u.%u (build %u)\n", version_major, version_minor, build);

    }
    char computer_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computer_name);
    GetComputerNameA(computer_name, &size);
    //  printf("Computer name: %s\n", computer_name);

    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);


    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count >max_count)
        {
           max_count = count;
        }
    }

    const bool scaling_needed = (max_count * BLOCK_WIDTH) > (IMAGE_WIDTH - TEXT_WIDTH);
    const double scaling_factor = (double)((IMAGE_WIDTH - TEXT_WIDTH)) / (double)((max_count * BLOCK_WIDTH));

    if (scaling_needed)
    {

        double top = 0;

        for (size_t i = 0; i<bin_count; i++)
        {
            const double bin_width = double(BLOCK_WIDTH * bins[i] * scaling_factor);
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, colors[i]);
            top += BIN_HEIGHT;
        }

    if(flag == true)
        {
            cout<< "<text x='" << TEXT_LEFT << "' y='" << top + TEXT_BASELINE << "'>" << "Windows v" <<version_major<< "." <<version_minor<< " (build " << build << ")" << "</text>" <<endl;
            cout<< "<text x='" << TEXT_LEFT << "' y='" << top + 20 + TEXT_BASELINE << "'>" << "Computer name: " <<computer_name<< "</text>" <<endl;
        }
    else
        {
            cout<< "<text x='" << TEXT_LEFT << "' y='" << top + TEXT_BASELINE << "'>" << "Windows v" <<version_major<< "." <<version_minor<< " (build " << build << ")" << "</text>" <<endl;
            cout<< "<text x='" << TEXT_LEFT << "' y='" << top + 20 + TEXT_BASELINE << "'>" << "Computer name: " <<computer_name<< "</text>" <<endl;
            curl_global_init(CURL_GLOBAL_ALL);
            CURL *curl = curl_easy_init();
            if(curl)
             {
                CURLcode res;
                double connect;
                curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
                res = curl_easy_perform(curl);
                   if(CURLE_OK == res)
                     {
                    res = curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &connect);
                   if(CURLE_OK == res)
                    {

    cout<< "<text x='" << TEXT_LEFT << "' y='" << top + 50 + TEXT_BASELINE << "'>" << "Time: " << connect << "</text>" <<endl;

                    }
                }
    curl_easy_cleanup(curl);
            }

        }
    }

    else
    {

        double top = 0;

        for (size_t i = 0; i<bin_count; i++)
        {
            const double bin_width = BLOCK_WIDTH * bins[i];
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, colors[i]);
            top += BIN_HEIGHT;
             }
            if(flag == true)
             {
            cout<< "<text x='" << TEXT_LEFT << "' y='" << top + TEXT_BASELINE << "'>" << "Windows v" <<version_major<< "." <<version_minor<< " (build " << build << ")" << "</text>" <<endl;
            cout<< "<text x='" << TEXT_LEFT << "' y='" << top + 20 + TEXT_BASELINE << "'>" << "Computer name: " <<computer_name<< "</text>" <<endl;
             }
            else
             {
               cout<< "<text x='" << TEXT_LEFT << "' y='" << top + TEXT_BASELINE << "'>" << "Windows v" <<version_major<< "." <<version_minor<< " (build " << build << ")" << "</text>" <<endl;
               cout<< "<text x='" << TEXT_LEFT << "' y='" << top + 20 + TEXT_BASELINE << "'>" << "Computer name: " <<computer_name<< "</text>" <<endl;
               curl_global_init(CURL_GLOBAL_ALL);
               CURL *curl = curl_easy_init();
               if(curl)
                {
                  CURLcode res;
                  double connect;
                  curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
                  res = curl_easy_perform(curl);
             if(CURLE_OK == res)
                {
                    res = curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &connect);
             if(CURLE_OK == res)
                    {
                        //   printf("Time: %.1f", connect);
              cout<< "<text x='" << TEXT_LEFT << "' y='" << top + 50 + TEXT_BASELINE << "'>" << "Time: " << connect << "</text>" <<endl;

                    }
                }
          curl_easy_cleanup(curl);
            }

        }

    }


svg_end();

}

vector <string>input_colors(size_t bin_count, bool flag)
{
    vector<string> colors(bin_count);
    if(flag)
    {
        bool flag2;
        for (size_t i = 0; i<bin_count; i++)
        {
            do
            {
                cin>> colors[i];
                bool flag1 = true;
                for (auto s : colors[i])
                {
                    if (s == ' ')
                    {
                        flag1 = false;
                    }
                }
                if(colors[i][0] == '#')
                {
                    if (flag1 == true)
                    {
                        flag2 = true;
                    }
                    else
                    {
                        flag2 = false;
                        cerr<< "Error1";
                    }
                }

                else if(colors[i][0] != '#')
                {
                        if(flag1 = true)
                    {
                        flag2 = true;
                    }
                    else
                    {
                        flag2 = false;
                        cerr<< "Error2";
                    }
                }

            }
               while(flag2 == false);
        }
    }
    else
    {
        for (size_t i = 0; i<bin_count; i++)
        {
            colors[i] = "red";
        }
    }
    return colors;
}
