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

short NumberOfDaysInMonth(short Month, short Year) {
    if (0 >= Month || Month > 12) {
        return 0;
    }
    int NumberOfDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
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

bool IsBusinessDay(stDate Date) {

    return !IsWeekEnd(DayOfWeekOrder(Date));
}

short DaysUntilTheEndOfWeek(short Day) {

    return 6 - Day;
}

short DaysUntilTheEndOfMonth(stDate Date) {
    return NumberOfDaysInMonth(Date.Month, Date.Year) - Date.Day ;
}

short DaysUntilTheEndOfYear(stDate Date) {
    short TotalDays = DaysUntilTheEndOfMonth(Date);

    for (short Month = Date.Month+1 ; Month <= 12; Month++) {
        TotalDays += NumberOfDaysInMonth(Month, Date.Year);
    }
    return TotalDays;
}

bool IsLastDayInMonth(stDate Date)
{
    return (Date.Day == NumberOfDaysInMonth(Date.Month,Date.Year));
}

bool IsLastMonthInYear(short Month)
{
    return (Month == 12);
}

bool IsDate1BeforeDate2(stDate Date1, stDate Date2) {
    return (Date1.Year < Date2.Year) ? true : (Date1.Year == Date2.Year) ? ((Date1.Month < Date2.Month) ? true : (Date1.Month == Date2.Month) ? (Date1.Day < Date2.Day) : false) : false;
}


stDate IncreaseDateByOneDay(stDate Date)
{
    if (IsLastDayInMonth(Date))
    {
        if (IsLastMonthInYear(Date.Month))
        {
            Date.Month = 1;
            Date.Day = 1;
            Date.Year++;
        }
        else
        {
            Date.Day = 1;
            Date.Month++;
        }
    }
    else
    {
        Date.Day++;
    }
    return Date;
}

short CalculateVacationDays(stDate DateStartVacation, stDate DateEndVacation) {
    short DaysCount = 0;
     while (IsDate1BeforeDate2(DateStartVacation, DateEndVacation)) {
         if (IsBusinessDay(DateStartVacation)) {
             DaysCount++;
         }
         DateStartVacation = IncreaseDateByOneDay(DateStartVacation);
     }
    return DaysCount;
}

stDate CalculateVacationReturnDate(stDate DateFrom, short VacationDays) {
   stDate ReturnDate = DateFrom;
    while (VacationDays != 0) {
        if (IsBusinessDay(ReturnDate)) {
            VacationDays--;
        }
        ReturnDate = IncreaseDateByOneDay(ReturnDate);
    }
    return ReturnDate;
}

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

short ReadVacationDays() {
    short Day;
    cout << "\nPlease enter vacation days? ";
    cin >> Day;
    return Day;
}

int main() {
    cout << "\nVacation Starts: ";
    stDate DateFrom = ReadFullDate();

    short VacationDays = ReadVacationDays();

    stDate ReturnDate = CalculateVacationReturnDate(DateFrom, VacationDays);

    cout << "\n\nReturn Date: "
    << DayShortName(DayOfWeekOrder(ReturnDate)) << " , "
        << ReturnDate.Day << "/"
    << ReturnDate.Month << "/" << ReturnDate.Year << endl;
    return 0;
}
