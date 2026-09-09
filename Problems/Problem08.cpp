#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

bool IsLeapYear(short Year) {
    return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
}

short NumberOfDaysInAMonth(short Month, short Year) {
    if (0 >= Month || Month > 12) {
        return 0;
    }
    int NumberOfDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
}

string MonthShortName(short Month) {
    string arrMonthsNames[12] = {"Jan", "Feb", "Mar",
        "Apr", "May", "Jun", "Jul", "Aug", "Sep",
        "Oct", "Nov", "Dec"};
    return arrMonthsNames[Month - 1];
}

short DayOfWeekOrder(short Day, short Month, short Year)
{
    short a, y, m;
    a = (14 - Month) / 12;
    y = Year - a;
    m = Month + (12 * a) - 2;
    // Gregorian:
    //0:sun, 1:Mon, 2:Tue...etc
    return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m)/ 12)) % 7;
}

void PrintMonthCalendar(short Month, short Year) {
    string MonthName = MonthShortName(Month);
    short NumbersOfDays = NumberOfDaysInAMonth(Month, Year);
    short Space = DayOfWeekOrder(1, Month, Year);

    cout << "\n__________________" << MonthName << "__________________\n";
    cout << "Sun   Mon   Tue   Wed   Thu   Fri   Sat \n";

    for (short i = 0; i < Space; i++) {
        cout << "      ";
    }

    for (short day = 1; day <= NumbersOfDays; day++) {
        cout << setw(3) << right << day << "   ";
        if ((day + Space) % 7 == 0) {
            cout << endl;
        }
    }
    cout << "\n_________________________________________\n";
}
short ReadMonth()
{
    short Month;
    cout << "\nPlease enter a Month? ";
    cin >> Month;
    return Month;
}

short ReadYear()
{
    short Year;
    cout << "\nPlease enter a year? ";
    cin >> Year;
    return Year;
}
int main() {
    short Year = ReadYear();
    short Month = ReadMonth();
    PrintMonthCalendar(Month, Year);
    return 0;
}
