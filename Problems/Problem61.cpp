#include <iostream>
#include <string>
using namespace std;
enum enDateCompare{Before = -1 , Equal = 0 , After = 1 };
struct stDate {
    short Day;
    short Month;
    short Year;
};

struct stPeriod {
    stDate StartDate;
    stDate EndDate;
};

bool IsLeapYear(short Year) {
    return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
}

bool IsDate1BeforeDate2(stDate Date1, stDate Date2)
{
    return (Date1.Year < Date2.Year) ? true : ((Date1.Year ==Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month ==Date2.Month ? Date1.Day < Date2.Day : false)) : false);
}

bool IsDate1EqualDate2(stDate Date1, stDate Date2)
{
    return (Date1.Year == Date2.Year) ? ((Date1.Month ==Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false): false;
}

bool IsDate1AfterDate2(stDate Date1, stDate Date2)
{
    return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
}

short NumberOfDaysInMonth(short Month, short Year)
{
    if (Month < 1 || Month>12)
        return 0;
    int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) :
    days[Month - 1];
}

bool IsLastDayInMonth(stDate Date)
{
    return (Date.Day == NumberOfDaysInMonth(Date.Month,Date.Year));
}

bool IsLastMonthInYear(short Month)
{
    return (Month == 12);
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

int GetDifferenceInDays(stDate Date1 , stDate Date2 , bool IncludeEndDay = false) {
    int Days = 0;
    while (IsDate1BeforeDate2(Date1, Date2)) {
        Days++;
        Date1 = IncreaseDateByOneDay(Date1);
    }
    return IncludeEndDay ? ++Days : Days;
}

int PeriodLengthInDays(stPeriod Period1) {
    return GetDifferenceInDays(Period1.StartDate, Period1.EndDate);
}

enDateCompare CompareDates(stDate Date1, stDate Date2) {
    if (IsDate1BeforeDate2(Date1, Date2)) {
        return enDateCompare::Before;
    }
    else if (IsDate1AfterDate2(Date1, Date2)) {
        return enDateCompare::After;
    }
    return enDateCompare::Equal;
}

bool IsOverlapPeriods(stPeriod Period1, stPeriod Period2) {
    if (CompareDates(Period1.EndDate, Period2.StartDate) == enDateCompare::Before || CompareDates(Period1.StartDate, Period2.EndDate) == enDateCompare::After) {
        return false;
    }
    return true;
}

bool IsDateInPeriod(stPeriod Period, stDate Date ) {
    return !(CompareDates(Date, Period.StartDate) ==
            enDateCompare::Before
            ||
        CompareDates(Date, Period.EndDate) ==
            enDateCompare::After);
}

short CountOverlapDays(stPeriod Period1, stPeriod Period2) {
    int Period1Length = PeriodLengthInDays(Period1);
    int Period2Length = PeriodLengthInDays(Period2);
    int OverLapsDays = 0;

    if (!IsOverlapPeriods(Period1, Period2)) {
        return 0;
    }

    if (Period1Length < Period2Length) {
        while (IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate)) {

            if (IsDateInPeriod(Period2, Period1.StartDate)) {
                     OverLapsDays++;
                 }
            Period1.StartDate = IncreaseDateByOneDay(Period1.StartDate);
        }
    }
    else {
        while (IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate)) {
            if (IsDateInPeriod(Period1, Period2.StartDate)) {
                OverLapsDays++;
            }
            Period2.StartDate = IncreaseDateByOneDay(Period2.StartDate);
        }
    }
    return OverLapsDays;
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

stPeriod ReadPeriod() {
    stPeriod Period;
    Period.StartDate = ReadFullDate();
    Period.EndDate = ReadFullDate();
    return Period;
}
int main() {
    cout << "\nEnter Period 1 :";
    stPeriod Period1 = ReadPeriod();
    cout << "\nEnter Period 2 :";
    stPeriod Period2 = ReadPeriod();
    cout << "\nOverlap Days Count Is: " <<
    CountOverlapDays(Period1, Period2);
    return 0;
}
