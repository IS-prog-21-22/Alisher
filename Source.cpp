#define CURL_STATICLIB
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <locale.h>
#include <curl/curl.h>
#include "json/include/nlohmann/json.hpp"
#include <windows.h>

#define next_data next_data_(66);
#define next_data_mean next_data_(16);

#define country_number 35

std::string count [country_number] = { "AUD", "AZN", "GBP", "AMD", "BYN", "BGN", "BRL", "HUF", "HKD", 
"DKK", "USD", "EUR", "INR", "KZT", "CAD", "KGS", "CNY", "MDL", "NOK", "PLN", "RON", "XDR", "SGD", "TJS", 
"TRY", "TMT", "TRY", "UZS", "UAH", "CZK", "SEK", "CHF", "ZAR", "KRW", "JPY"};

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

    json friquent;

    std::vector<std::vector <double>> friq_val;

    double found_max_friquent(int it)
    {
        int max_num=0;
        double max_val=0;

        for (int i = 0; i < friq_val[it].size(); i++)
        {
            int num = friquent[it][friq_val[it][i]]["number"];
            if (num > max_num)
            {
                max_num = num;
                max_val = friq_val[it][i];
            }
        };
        return max_val;
    }

public:
    finish_data()
    {
        for (int i = 0; i < country_number; i++)
        {
            mean[i] = 0;
            mean_number[i] = 0;
        }
        friq_val.resize(country_number);
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
            std::cout << "|" << count[i] << "|";
            std::cout <<  found_max_friquent(i) << "\t|";
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
        double data = jsonData["Valute"][count[it]]["Value"];
        if (friquent[it][data]["find"] != 1)
        {
            friquent[it][data]["find"] = 1;
            friquent[it][data]["number"] = 1;
            friq_val[it].push_back(data);
        }
        else
        {
            double new_data = friquent[it][data]["number"] + 1;
            friquent[it][data]["number"]=new_data;
        }
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

    bool _end=false;


    while (true)
    {
        std::cout << "Press 'ESC' to end.\n";
        print_data();
        waiting(10);
        system("cls");
    }

    return 0;
}