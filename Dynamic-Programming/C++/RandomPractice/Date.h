#pragma once

#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <random>
#include <ctime>

class Date {
    private:
        // std::string Days[7] = { "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat", "Sun" };
        // std::string Day;
        // std::string Month;
        // std::string Year;
        std::string time;
        tm* _Date;

        int daynumerical;

        // void setday(std::string day);
        // void setmonth(std::string month);
        // void setyear(std::string year);
        void settime();
        // void setdaynumerical(int daynum);

    public:
        Date();
        ~Date();
        Date(const Date &d);
        Date(int _month,int _day,int _year);
        
        void setDate(std::string _month,std::string _day,std::string _year);
        void setDate(Date &d);

        std::string getTime() const;
        tm* getDate() const;
        // tm* getCurrentDate() const;

        void printDate();
        void random();

        Date& operator=(const Date& rhs);
};

Date::Date() {
    auto now = std::chrono::system_clock::now();
    std::time_t date = std::chrono::system_clock::to_time_t(now);

    // std::string full_date = std::ctime(&(end_time));

    _Date = new tm(*std::localtime(&date));
    // Set time
    settime();
    // _Date = getCurrentDate();
}

Date::Date(const Date &d) {
    if(this != &d) {
        time = d.getTime();
        daynumerical = d.daynumerical;
        _Date = new tm(*d.getDate());
    }
}

Date::Date(int _month,int _day,int _year) {
    std::chrono::year_month_day customDate{std::chrono::year(_year) / _month / _day};

    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> hourDist(0, 23);
    std::uniform_int_distribution<int> minuteDist(0, 59);
    std::uniform_int_distribution<int> secondDist(0, 59);

    int randomHour = hourDist(gen);
    int randomMinute = minuteDist(gen);
    int randomSecond = secondDist(gen);

    auto currentTimePoint = std::chrono::system_clock::now();
    auto randomTimePoint = currentTimePoint 
        + std::chrono::hours(randomHour)
        + std::chrono::minutes(randomMinute)
        + std::chrono::seconds(randomSecond);

    // Convert the random time point to a time_t value
    auto randomTime = std::chrono::system_clock::to_time_t(randomTimePoint);

    // Convert to local time and set Date
    _Date = new tm(*std::localtime(&randomTime));
    settime();

    // Print the random time
    // std::cout << std::put_time(_Date, "%a %b %d %H:%M:%S %Y") << std::endl;
    // std::cout << date << std::endl;

    // customDate
    // Year = std::to_string(int(customDate.year()));

}

Date::~Date() {
    delete _Date;
}

void Date::settime() {
    // Set time
    time = std::to_string(_Date->tm_hour) + ":" 
            + std::to_string(_Date->tm_min) + ":"
            + std::to_string(_Date->tm_sec);

}

void Date::random() {
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> __rtime(0, 364);
    
    auto currentTime_Point = std::chrono::system_clock::now();

    auto randomDuration = std::chrono::hours(__rtime(gen) * 24);
    auto randomDateTime_Point = currentTime_Point - randomDuration;

    std::time_t new_date = std::chrono::system_clock::to_time_t(randomDateTime_Point);
    delete _Date;
    _Date = new tm(*std::localtime(&new_date));
    settime();
    // Month = std::to_string(full_date->tm_mon);
    // Day = Days[full_date->tm_wday];
    // daynumerical = full_date->tm_mday;
    // Year = std::to_string(1900 + full_date->tm_year);

    // auto date = std::put_time(full_date, "%a %b %d %H:%M:%S %Y");  
}


// tm* Date::getCurrentDate() const {
//     auto now = std::chrono::system_clock::now();
//     std::time_t date = std::chrono::system_clock::to_time_t(now);

//     // std::string full_date = std::ctime(&(end_time));

//     return std::localtime(&date);
// }

tm* Date::getDate() const {
    return _Date;
}

std::string Date::getTime() const {
    return time;
}

void Date::printDate() {
    std::cout << std::put_time(_Date, "%a %b %d %H:%M:%S %Y") << std::endl;
}

Date& Date::operator=(const Date& rhs) {
    if(this != &rhs) {
        time = rhs.getTime();
        daynumerical = rhs.daynumerical;
        delete _Date;
        _Date = new tm(*rhs.getDate());
    }

    return *this;
}