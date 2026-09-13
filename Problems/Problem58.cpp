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
    cout << "\nEnter Period 1:";
    stPeriod Period1 = ReadPeriod();
    cout << "\nEnter Period 2:";
    stPeriod Period2 = ReadPeriod();
    if (IsOverlapPeriods(Period1, Period2))
        cout << "\nYes, Periods Overlap\n";
    else
        cout << "\nNo, Periods do not Overlap\n";
    return 0;
}
