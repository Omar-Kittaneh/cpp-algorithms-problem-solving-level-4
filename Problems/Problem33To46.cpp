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

short NumberOfDaysInMonth(short Month, short Year)
{
    if (Month < 1 || Month>12)
        return 0;
    int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) :
    days[Month - 1];
}

bool IsDate1BeforeDate2(stDate Date1, stDate Date2) {
    return (Date1.Year < Date2.Year) ? true : (Date1.Year == Date2.Year) ? ((Date1.Month < Date2.Month) ? true : (Date1.Month == Date2.Month) ? (Date1.Day < Date2.Day) : false) : false;
}

bool IsLastDayInMonth(stDate Date)
{
    return (Date.Day == NumberOfDaysInMonth(Date.Month,Date.Year));
}

bool IsFirstDayInMonth(short Day)
{
    return (Day == 1);
}

bool IsFirstMonthInYear(short Month)
{
    return (Month == 1);
}

stDate DecreaseDateByOneDay(stDate Date)
{
    if (IsFirstDayInMonth(Date.Day))
    {
        if (IsFirstMonthInYear(Date.Month))
        {
            Date.Month = 12;
            Date.Day = 31;
            Date.Year--;
        }
        else
        {
            Date.Month--;
            Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
        }
    }
    else
    {
        Date.Day--;
    }
    return Date;
}

stDate DecreaseDateByXDays(short Days, stDate Date) {
    for (short i = 0; i < Days; i++) {
        Date = DecreaseDateByOneDay(Date);
    }
    return Date;
}

stDate DecreaseDateByOneWeek(stDate Date) {
    for (short i = 1; i <= 7; i++) {
        Date = DecreaseDateByOneDay(Date);
    }
    return Date;
}

stDate DecreaseDateByXWeeks(short Weeks, stDate Date) {
    for (short i = 1; i <= Weeks; i++) {
        Date = DecreaseDateByOneWeek(Date);
    }
    return Date;
}

stDate DecreaseDateByOneMonth(stDate Date) {
    if (IsFirstMonthInYear(Date.Month)) {
        Date.Month = 12;
        Date.Year--;
    }
    else {
        Date.Month--;
        }

    short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month,Date.Year);
    if (Date.Day > NumberOfDaysInCurrentMonth) {
        Date.Day = NumberOfDaysInCurrentMonth;
    }

    return Date;
}

stDate DecreaseDateByXMonths(short Months, stDate Date) {
    for (short i = 1; i <= Months; i++) {
        Date = DecreaseDateByOneMonth(Date);
    }
    return Date;
}

stDate DecreaseDateByOneYear(stDate Date) {
    Date.Year--;
    if (!IsLeapYear(Date.Year) && Date.Day == 29 && Date.Month == 2) {
        Date.Day--;
    }
    return Date;
}

stDate DecreaseDateByXYears(short Years, stDate Date) {
    for (short i = 1; i <= Years; i++) {
        Date = DecreaseDateByOneYear(Date);
    }
    return Date;
}

stDate DecreaseDateByXYearsFaster(short Years, stDate Date) {
    Date.Year -= Years;
    if (!IsLeapYear(Date.Year) && Date.Day == 29 && Date.Month == 2) {
        Date.Day--;
    }
    return Date;
}

stDate DecreaseDateByOneDecade(stDate Date) {
    Date.Year -= 10;
    if (!IsLeapYear(Date.Year) && Date.Day == 29 && Date.Month == 2) {
        Date.Day--;
    }
    return Date;
}

stDate DecreaseDateByXDecades(short Decades, stDate Date) {
    for (short i = 1; i <= Decades; i++) {
        Date = DecreaseDateByOneDecade(Date);
    }
    return Date;
}

stDate DecreaseDateByXDecadesFaster(short Decades, stDate Date) {
    Date.Year -= Decades * 10 ;
    if (!IsLeapYear(Date.Year) && Date.Month == 2 && Date.Day == 29) {
        Date.Day--;
    }
    return Date;
}

stDate DecreaseDateByOneCentury(stDate Date) {
    Date.Year -= 100;
    if (!IsLeapYear(Date.Year) && Date.Month == 2 && Date.Day == 29) {
        Date.Day--;
    }
    return Date;

}

stDate DecreaseDateByOneMillennium(stDate Date) {
    Date.Year -= 1000;
    if (!IsLeapYear(Date.Year) && Date.Month == 2 && Date.Day == 29) {
        Date.Day--;
    }
    return Date;
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
    stDate Date1 = ReadFullDate();
    cout << "\nDate After: \n";

     Date1 = DecreaseDateByOneDay(Date1);
    cout << "\n01-Subtracting one day is: "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = DecreaseDateByXDays(10, Date1);
    cout << "\n02-Subtracting 10 days is: "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = DecreaseDateByOneWeek(Date1);
    cout << "\n03-Subtracting one week is: "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = DecreaseDateByXWeeks(10, Date1);
    cout << "\n04-Subtracting 10 weeks is: "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = DecreaseDateByOneMonth(Date1);
    cout << "\n05-Subtracting one month is: "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = DecreaseDateByXMonths(5, Date1);
    cout << "\n06-Subtracting 5 months is: "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = DecreaseDateByOneYear(Date1);
    cout << "\n07-Subtracting one year is: "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = DecreaseDateByXYears(10, Date1);
    cout << "\n08-Subtracting 10 Years is: "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = DecreaseDateByXYearsFaster(10, Date1);
    cout << "\n09-Subtracting 10 Years (faster) is: "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = DecreaseDateByOneDecade(Date1);
    cout << "\n10-Subtracting one Decade is: "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = DecreaseDateByXDecades(10, Date1);
    cout << "\n11-Subtracting 10 Decades is: "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = DecreaseDateByXDecadesFaster(10, Date1);
    cout << "\n12-Subtracting 10 Decade (faster) is: "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = DecreaseDateByOneCentury(Date1);
    cout << "\n13-Subtracting One Century is: "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = DecreaseDateByOneMillennium(Date1);
    cout << "\n14-Subtracting One Millennium is: "
    << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    return 0;
}