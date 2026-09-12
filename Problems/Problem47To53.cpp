#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
struct stDate
{
    short Year;
    short Month;
    short Day;
};

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

string DayShortName(short Day) {
    string arrDaysNames[7] = {
        "Sun", "Mon", "Tue", "Wed",
        "Thu", "Fri", "Sat"
    };
    return arrDaysNames[Day];
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

short DayOfWeekOrder(stDate Date)
{
    return DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
}

bool IsEndOfWeek(short DayOfWeekOrder) {
    return (DayOfWeekOrder == 6);
}

bool IsWeekEnd(short DayOfWeekOrder) {
    return (DayOfWeekOrder == 5 || DayOfWeekOrder == 6);
}

bool IsWeekEnd(stDate Date) {
    return IsWeekEnd(DayOfWeekOrder(Date));
}

bool IsBusinessDay(short DayOfWeekOrder) {
    return !IsWeekEnd(DayOfWeekOrder);
}

short DaysUntilTheEndOfWeek(short Day) {

    return 6 - Day;
}

short DaysUntilTheEndOfMonth(stDate Date) {
    return NumberOfDaysInAMonth(Date.Month, Date.Year) - Date.Day ;
}

short DaysUntilTheEndOfYear(stDate Date) {
    short TotalDays = DaysUntilTheEndOfMonth(Date);

    for (short Month = Date.Month+1 ; Month <= 12; Month++) {
        TotalDays += NumberOfDaysInAMonth(Month, Date.Year);
    }
    return TotalDays;
}

// void PrintMonthCalendar(short Month, short Year) {
//     string MonthName = MonthShortName(Month);
//     short NumbersOfDays = NumberOfDaysInAMonth(Month, Year);
//     short Space = DayOfWeekOrder(1, Month, Year);
//
//     cout << "\n__________________" << MonthName << "__________________\n";
//     cout << "Sun   Mon   Tue   Wed   Thu   Fri   Sat \n";
//
//     for (short i = 0; i < Space; i++) {
//         cout << "      ";
//     }
//
//     for (short day = 1; day <= NumbersOfDays; day++) {
//         cout << setw(3) << right << day << "   ";
//         if ((day + Space) % 7 == 0) {
//             cout << endl;
//         }
//     }
//     cout << "\n_________________________________________\n";
// }

short ReadDay()
{
    short Day;
    cout << "\nPlease enter a Day? ";
    cin >> Day;
    return Day;
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

stDate ReadFullDate()
{
    stDate Date;
    Date.Day = ReadDay();
    Date.Month = ReadMonth();
    Date.Year = ReadYear();
    return Date;
}

stDate GetSystemDate()
{
    stDate Date;
    time_t t = time(0);
    tm* now = localtime(&t);
    Date.Year = now->tm_year + 1900;
    Date.Month = now->tm_mon + 1;
    Date.Day = now->tm_mday;
    return Date;
}

int main() {
    stDate Date1 = GetSystemDate();
    short DataDayOfWeekOrder = DayOfWeekOrder(Date1);

    cout << "\nToday is " << DayShortName(DataDayOfWeekOrder)
    << " , "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year <<
    endl;


    cout << "\nIs it End of Week?\n";
    if (IsEndOfWeek(DataDayOfWeekOrder))
        cout << "Yes it is Saturday, it's of Week.";
    else
        cout << "No it's Not end of week.";


    cout << "\n\nIs it Weekend?\n";
    if (IsWeekEnd(DataDayOfWeekOrder))
        cout << "Yes it is a week end.";
    else
        cout << "No today is " <<
        DayShortName(DataDayOfWeekOrder) << ", Not a weekend.";

    cout << "\n\nIs it Business Day?\n";
    if (IsBusinessDay(DataDayOfWeekOrder))
        cout << "Yes it is a business day.";
    else
        cout << "No it is NOT a business day.";

    cout << "\n\nDays until end of week : "
    << DaysUntilTheEndOfWeek(DataDayOfWeekOrder) << " Day(s).";

    cout << "\nDays until end of month : "
    << DaysUntilTheEndOfMonth(Date1) << " Day(s).";

    cout << "\nDays until end of year : "
    << DaysUntilTheEndOfYear(Date1) << " Day(s).";
    return 0;
}
