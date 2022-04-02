#define CURL_STATICLIB
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <locale.h>
#include <curl/curl.h>
#include "json/include/nlohmann/json.hpp"
#include <windows.h>
#include <cmath>

#define next_data next_data_(66);
#define next_data_mean next_data_(16);

#define country_number 34
#define max_co -1

std::string count [country_number] = { "AUD", "AZN", "GBP", "AMD", "BYN", "BGN", "BRL", "HUF", "HKD", 
"DKK", "USD", "EUR", "INR", "KZT", "CAD", "KGS", "CNY", "MDL", "NOK", "PLN", "RON", "XDR", "SGD", "TJS", 
"TRY", "TMT", "UZS", "UAH", "CZK", "SEK", "CHF", "ZAR", "KRW", "JPY"};


void next_data_(int n)
{
    std::cout << std::endl;
    for (int i = 0; i < n; i++)
        std::cout << "_";
    std::cout << std::endl;
}

namespace
{
    std::size_t callback(
        const char* in,
        std::size_t size,
        std::size_t num,
        std::string* out)
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
}

using json = nlohmann::json;

json jsonData;

class finish_data
{
private:
    double mean[country_number];
    int mean_number[country_number];
    std::vector <int> max_key;

    std::vector <std::vector <std::vector <double>>> median;

public:
    finish_data()
    {
        for (int i = 0; i < country_number; i++)
        {
            mean[i] = 0;
            mean_number[i] = 0;
        }
        max_key.resize(country_number, max_co);
        median.resize(country_number, std::vector <std::vector <double>> (100000));
    }

    ~finish_data()
    {
        system("cls");

        //print_mean_value
        std::cout << "Mean values. Press 'ESC' to print friquent values.";
        next_data_mean;
        std::cout << "|Cou|" << "MeanValue\t|";
        next_data_mean;
      
        for (int i = 0; i < country_number; i++)
        {
            std::cout << "|" << count[i] << "|";
            std::cout << mean[i]/mean_number[i] << "\t|";
            next_data_mean;
        }

        //waiting

        Sleep(2000);
        while (!GetAsyncKeyState(VK_ESCAPE))
        { }

        //print friquent
        system("cls");

        std::cout << "Friquent value:";
        next_data_mean;
        std::cout << "|Cou|" << "FriValue\t|";
        next_data_mean;

        for (int i = 0; i < country_number; i++)
        {
            int median_key;

            int it=0;
            while (true)
            {
                if (median[i][max_key[i] / 2 + it].size() != 0)
                {
                    median_key = max_key[i] / 2 + it;
                    break;
                }
                if (median[i][max_key[i] / 2 - it].size() != 0)
                {
                    median_key = max_key[i] / 2 - it;
                    break;
                }
                it++;
            }

            std::cout << "|" << count[i] << "|";
            std::cout <<  median[i][median_key][median[i][median_key].size()/2] << "\t|";
            next_data_mean;
        }
    }
    
    void go_mean(int it)
    { 
        mean[it] = jsonData["Valute"][count[it]]["Value"];
        mean_number[it]++;
    }

    void go_friquent_value(int it)
    {
        double value=jsonData["Valute"][count[it]]["Value"];
        int key= jsonData["Valute"][count[it]]["Value"];
        
        if (median[it][key].size() == 0 && max_key[it]<key)
            max_key[it] = key;

        median[it][key].push_back(value);

        int i = median[it][key].size() - 2;

        while ( i>0 && value < median[it][key][i])
        {
            median[it][key][i + 1] = median[it][key][i];
            i--;
        }
        median[it][key][i + 1] = value;
    }
};

finish_data fin;

void waiting(int max_time)
{
    int time=0;
    while (time < max_time)
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            std::cout << "nice" << std::endl;
            exit(0);
        }
        Sleep(1000);
        time++;
    }
}

void country_inf(std::string countree)
{
    std::cout << "| " << countree << " | ";
    std::cout << jsonData["Valute"][countree]["ID"] << "\t| ";
    std::cout << jsonData["Valute"][countree]["NumCode"] << "| ";
    std::cout << jsonData["Valute"][countree]["Nominal"] << "\t| ";
    std::cout << jsonData["Valute"][countree]["Value"] << " \t| ";
    std::cout << jsonData["Valute"][countree]["Previous"] << "| ";
    next_data;
}

void print_data()
{
    std::cout << "Date:" << jsonData["Date"] << std::endl;
    std::cout << "Previus_date:" << jsonData["PreviousDate"] << std::endl;
    next_data;

    std::cout << "|" << "count" << "|";
    std::cout << "       ID        " << "|";
    std::cout << "NumCod" << "|";
    std::cout << "Nominal " << "|";
    std::cout << "     Value     " << "|";
    std::cout << "Previous" << "|";
    next_data;


    for (int i = 0; i < country_number; i++)
    {

        country_inf(count[i]);
        fin.go_mean(i);
        fin.go_friquent_value(i);
    }
}

int main() {


    const std::string url("https://www.cbr-xml-daily.ru/daily_json.js");

    

    bool _end=false;


    while (true)
    {
        CURL* curl = curl_easy_init();

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        long httpCode(0);
        std::unique_ptr<std::string> httpData(new std::string());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);

        jsonData = json::parse(httpData->begin(), httpData->end());

        std::cout << "Press 'ESC' to end.\n";
        print_data();
        waiting(10);
        system("cls");
    }

    return 0;
}