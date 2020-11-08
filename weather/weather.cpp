// weather.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
#include <cpr/cpr.h>
#include "json/json.h"
using namespace std;

void show_weather(Json::Value root, int number) {
    string winds[] = {
    "N",
    "NE",
    "E",
    "SE",
    "S",
    "SW",
    "W",
    "NW",
    "N",
    };
    Json::Value currentDay;
    currentDay = root["list"][number];
  
        string average_temp = to_string(int(round((currentDay["temp"]["max"].asDouble() + currentDay["temp"]["min"].asDouble()) / 2))); //Среднее арифметическое макс. и мин. погод
        time_t t = currentDay["dt"].asLargestInt();
        cout << asctime(localtime(&t));

        cout << currentDay["weather"][0]["main"].asString() << " (" << currentDay["weather"][0]["description"].asString() << ')' << endl;

        cout << "Temperature (min/max): " << round(currentDay["temp"]["min"].asDouble()) << " / " << round(currentDay["temp"]["max"].asDouble()) << " °C (" << average_temp << ')' << endl;
        cout << "Pressure: " << round(currentDay["pressure"].asDouble() / 1.33322387415) << " mm Hg" << endl;
        cout << "Humidity: " << round(currentDay["humidity"].asDouble()) << '%' << endl;
        int wind = round(currentDay["deg"].asDouble() / 45);
        cout << "Wind: " << currentDay["speed"] << " m/s, " << winds[wind] << endl; 
}

int main(int argc, char** argv) {
    string city;
    if (argc) {
        city = argv[1];
    }
    else {
        cout << "Usage: weather [ city ] [-a/--all] (not implemented)";
    }
    //string result;
    //cin >> city;
    
    cpr::Response r = cpr::Get(cpr::Url{ "http://api.openweathermap.org/data/2.5/forecast/daily?&appid=98ba4333281c6d0711ca78d2d0481c3d&units=metric&cnt=17&q="+city });
    if (r.text.length()) {

        //Json::Reader reader;
        Json::CharReaderBuilder builder;
        Json::CharReader* reader = builder.newCharReader();
        Json::Value root;   // starts as "null"; will contain the root value after parsing
        string errors;

        bool parsingSuccessful = reader->parse(r.text.c_str(), r.text.c_str() + r.text.size(), &root, &errors);
        delete reader;
        if (!parsingSuccessful)
        {
            cout << "Error parsing the string" << endl;
            cout << r.text << endl;
            cout << errors << endl;
        }
        if (root["list"]) {
            cout << root["city"]["name"].asString() << ", " << root["city"]["country"].asString() << endl;
            cout << "Population: " << root["city"]["population"].asString() << endl;
            cout << "---------" << endl;
        }
        else {
            cout << root["message"].asString() << endl;
        }
        for (int i = 0; i < root["list"].size(); i++)
        {
            show_weather(root, i);
            cout << endl;
        }
    }
    else {
        cout << "Wrong result.";
    }

    
            
       
    
    
  
    //cout << currentDay["dt"]
    //cout << "Day: " << currentDay["temp"]["day"].asDouble(); 
    //cout << "Night: " << currentDay["temp"]["night"].asDouble(); 
    //cout << "Evening " << currentDay["temp"]["eve"].asDouble();
    //cout << "Morning " << currentDay["temp"]["morn"].asDouble();

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
