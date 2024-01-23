#pragma once

#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <string>

class Date {
    private:
        std::string Days[7] = { "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat", "Sun" };
        std::string Day;
        std::string Month;
        std::string Year;
        std::string time;

        int daynumerical;

        // void setday(std::string day);
        // void setmonth(std::string month);
        // void setyear(std::string year);
        // void settime(std::string year);
        // void setdaynumerical(int daynum);

    public:
        Date();
        Date(std::string _month,std::string _day,std::string _year);
        // Date(Date& date);
        
        void setDate(std::string _month,std::string _day,std::string _year);
        void setDate(Date &d);
        Date getDate();
        void printDate();
};

Date::Date() {
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::string full_date = std::ctime(&(end_time));
    std::stringstream ss(full_date);

    while(!ss.eof()) {
        ss >> Day >> Month >> daynumerical >> time >> Year;
    }

    // printDate();
}

Date::Date(std::string _month,std::string _day,std::string _year) : Day(_day), Month(_month), Year(_year) {
    // time = std::chrono::system_clock::now();
}

void Date::setDate(std::string _month,std::string _day,std::string _year) {
    Day = _day;
    Month = _month;
    Year = _year;
}

void Date::setDate(Date &d) {
    setDate(d.Day, d.Month, d.Year);
}

void Date::printDate() {
    std::cout << Day << " " << Month << " " << daynumerical << " " << time << " " << Year << std::endl;
}