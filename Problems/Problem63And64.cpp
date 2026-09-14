#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct stDate {
    short Day;
    short Month;
    short Year;
};

string ReadStringDate(string Message) {
    string dateString;

    cout << Message ;
    getline(cin >> ws, dateString);
    return dateString;
}

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }
    return vString;
}

stDate StringToDate(string DateString, string Delim = "/") {
   vector<string> vDate ;
    stDate Date;
    vDate = SplitString(DateString, Delim);
    Date.Day = stoi(vDate[0]);
    Date.Month = stoi(vDate[1]);
    Date.Year = stoi(vDate[2]);

    return Date;
}

string DateToString(stDate Date, string Delim = "/") {
    return to_string(Date.Day) + Delim + to_string(Date.Month) + Delim + to_string(Date.Year);
}



int main() {

    string DateString = ReadStringDate("\nPlease Enter Date dd/mm/yyyy? ");
    stDate Date = StringToDate(DateString);
    cout << "\nDay:" << Date.Day << endl;
    cout << "Month:" << Date.Month << endl;
    cout << "Year:" << Date.Year << endl;
    cout << "\nYou Entered: " << DateToString(Date) << "\n";
    return 0;
}
