#include <iostream>
#include <string>
using namespace std;

bool IsLeapYear(short Year) {
    return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
}

short ReadYear()
{
    short Year;
    cout << "\nPlease enter a year to check? ";
    cin >> Year;
    return Year;
}

short ReadMonth()
{
    short Month;
    cout << "\nPlease enter a Month to check? ";
    cin >> Month;
    return Month;
}

short NumberOfDaysInAMonth(short Month, short Year) {
    if (0 >= Month || Month > 12) {
        return 0;
    }
    int NumberOfDays[13] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
   return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1] + NumberOfDays[Month - 1];
}

short NumberOfHoursInAMonth(short Month, short Year)
{
    return NumberOfDaysInAMonth(Month, Year) * 24;
}
int NumberOfMinutesInAMonth(short Month, short Year)
{
    return NumberOfHoursInAMonth(Month, Year) * 60;
}
int NumberOfSecondsInAMonth(short Month, short Year)
{
    return NumberOfMinutesInAMonth(Month, Year) * 60;
}

int main() {

    short Year = ReadYear();
    short Month = ReadMonth();
    cout << "\nNumber of Days in Month [" << Month << "] is "
    << NumberOfDaysInAMonth(Month, Year);
    cout << "\nNumber of Hours in Month [" << Month << "] is "
    << NumberOfHoursInAMonth(Month, Year);
    cout << "\nNumber of Minutes in Month [" << Month << "] is "
    << NumberOfMinutesInAMonth(Month, Year);
    cout << "\nNumber of Seconds in Month [" << Month << "] is "
    << NumberOfSecondsInAMonth(Month, Year);
    return 0;
}
