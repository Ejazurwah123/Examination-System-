#pragma warning(disable : 4996)
#include <ctime>
#include <string>
#include <iostream>

class DateTime {
    time_t publishedTime;
    time_t dueTime;
public:
    DateTime() {
        publishedTime = time(nullptr);
        dueTime = 0;
    }

    void setDateTime(long long publishedTime, long long dueTime) {
        this->publishedTime = publishedTime;
        this->dueTime = dueTime;
    }

    string getDateTime() {
        return to_string(publishedTime) + ',' + to_string(dueTime);
    }

    void setTime(std::string date, int hourInt, int minInt) {
        int year, month, day;
        sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);
        struct tm timeinfo = { 0 };
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month - 1;
        timeinfo.tm_mday = day;
        timeinfo.tm_hour = hourInt;
        timeinfo.tm_min = minInt;
        dueTime = mktime(&timeinfo);
    }

    bool isInDueTime() const {
        time_t currentTime = time(nullptr);
        /*cout << "DueTime = " << dueTime << endl;
        cout << "Published Time = " << publishedTime << endl;
        cout << "Current Time = " << currentTime << endl;*/
        return (publishedTime <= currentTime && currentTime <= dueTime);
    }

    void printTime() const {
        cout << "DueTime = " << dueTime << endl;
        cout << "Published Time = " << publishedTime << endl;
    }

};
