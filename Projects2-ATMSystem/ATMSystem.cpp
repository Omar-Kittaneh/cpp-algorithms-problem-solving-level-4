#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <vector>

using namespace std;

const string ClientsFileName = "Clients.txt";

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    int AccountBalance = 0;
};

enum enAtmMainMenuOptions
{
    eQuickWithdraw = 1,
    eNormalWithdraw = 2,
    eDeposit = 3,
    eCheckBalance = 4,
    eLogout = 5
};

enum enQuickWithdrawOptions
{
    e20 = 1,
    e50 = 2,
    e100 = 3,
    e200 = 4,
    e400 = 5,
    e600 = 6,
    e800 = 7,
    e1000 = 8,
    eExit = 9
};

vector<string> SplitString(string Line, string Seperator = "#//#")
{
    string sWord = "";
    short Pos = 0;
    vector<string> vTokens;

    while ((Pos = Line.find(Seperator)) != string::npos)
    {
        sWord = Line.substr(0, Pos);

        if (sWord != "")
        {
            vTokens.push_back(sWord);
        }

        Line = Line.erase(0, Pos + Seperator.length());
    }

    if (Line != "")
    {
        vTokens.push_back(Line);
    }

    return vTokens;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    return Client.AccountNumber + Seperator +
        Client.PinCode + Seperator +
        Client.Name + Seperator +
        Client.Phone + Seperator +
        to_string(Client.AccountBalance);
}

sClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    vector<string> vClient = SplitString(Line, Seperator);

    sClient Client;

    Client.AccountNumber = vClient[0];
    Client.PinCode = vClient[1];
    Client.Name = vClient[2];
    Client.Phone = vClient[3];
    Client.AccountBalance = stod(vClient[4]);

    return Client;
}

vector<sClient> LoadDataFromFile(string FileName)
{
    vector<sClient> vClients;

    fstream MyFile(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;

        while (getline(MyFile, Line))
        {
            if (Line != "")
            {
                vClients.push_back(ConvertLineToRecord(Line));
            }
        }

        MyFile.close();
    }

    return vClients;
}

void SaveClientsDataToFile(string FileName, const vector<sClient>& ClientList)
{
    fstream MyFile(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (const sClient& C : ClientList)
        {
            MyFile << ConvertRecordToLine(C) << endl;
        }

        MyFile.close();
    }
}

bool ExistsAccountNumber(const vector<sClient>& vClients, string AccountNumber)
{
    for (const sClient& Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber)
            return true;
    }

    return false;
}

bool FindClientByAccountNumber(
    const vector<sClient>& vClients,
    sClient& Client,
    string AccountNumber)
{
    for (const sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }

    return false;
}

void GoBackToMainMenu()
{
    cout << "\n\nPress Enter to go back...";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

short GetQuickWithdrawAmount(short Option)
{
    switch (Option)
    {
    case enQuickWithdrawOptions::e20:
        return 20;

    case enQuickWithdrawOptions::e50:
        return 50;

    case enQuickWithdrawOptions::e100:
        return 100;

    case enQuickWithdrawOptions::e200:
        return 200;

    case enQuickWithdrawOptions::e400:
        return 400;

    case enQuickWithdrawOptions::e600:
        return 600;

    case enQuickWithdrawOptions::e800:
        return 800;

    case enQuickWithdrawOptions::e1000:
        return 1000;

    default:
        return 0;
    }
}

void ShowNameScreen(const string& NameScreen)
{
    system("cls");

    cout << "\n-----------------------------------\n";
    cout << "\t" << NameScreen << " Screen";
    cout << "\n-----------------------------------\n";
}

void ShowQuickWithdrawScreen(double Balance)
{
    system("cls");

    cout << "=================================================\n";
    cout << "\t\tQuick Withdraw\n";
    cout << "=================================================\n";
    cout << "\t[1] 20\t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "=================================================\n";

    cout << "Your Balance is " << Balance << endl;
    cout << "Choose what to withdraw from [1] to [9] ? ";
}

void ShowAtmMainMenu()
{
    system("cls");

    cout << "=================================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "=================================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "=================================================\n";

    cout << "Choose what do you want to do? [1 to 5]? ";
}

bool QuickWithdrawBalance(sClient& Client)
{
    int Amount = 0;
    int Option = 0;

    ShowQuickWithdrawScreen(Client.AccountBalance);

    cin >> Option;

    while (Option < 1 || Option > 9)
    {
        cout << "\nInvalid choice! Choose from [1] to [9]: ";
        cin >> Option;
    }

    if (Option == enQuickWithdrawOptions::eExit)
    {
        return false;
    }

    Amount = GetQuickWithdrawAmount(Option);

    if (Client.AccountBalance < Amount)
    {
        cout << "\nAmount Exceeds the balance, you can Withdraw up to: "
            << Client.AccountBalance << endl;

        return false;
    }

    char Answer = 'n';

    cout << "\nAre you sure you want perform this transaction? (y/n): ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Client.AccountBalance -= Amount;

        cout << "\n\nDone Successfully. New balance = "
            << Client.AccountBalance << endl;

        return true;
    }

    cout << "\n\nWithdraw Operation Cancelled.\n";

    return false;
}

bool NormalWithdrawBalance(sClient& Client)
{
    ShowNameScreen("Normal Withdraw");

    int Amount = 0;

    cout << "Enter an amount multiple of 5 to Withdraw: ";
    cin >> Amount;

    while (Amount <= 0 || Amount % 5 != 0)
    {
        cout << "Invalid amount! Enter a positive amount divisible by 5: ";
        cin >> Amount;
    }

    if (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can Withdraw up to: "
            << Client.AccountBalance << endl;

        return false;
    }

    char Answer = 'n';

    cout << "\nAre you sure you want to perform this transaction? (y/n): ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Client.AccountBalance -= Amount;

        cout << "\n\nDone Successfully. New balance = "
            << Client.AccountBalance << endl;

        return true;
    }

    cout << "\n\nWithdraw Operation Cancelled.\n";

    return false;
}

bool DepositBalance(sClient& Client)
{
    ShowNameScreen("Deposit");

    int Deposit = 0;

    cout << "Please enter a positive deposit amount? ";
    cin >> Deposit;

    while (Deposit <= 0)
    {
        cout << "You cannot enter negative or zero deposit!\n";
        cout << "Please enter a positive deposit amount? ";
        cin >> Deposit;
    }

    char Answer = 'n';

    cout << "\nAre you sure you want perform this transaction? (y/n): ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Client.AccountBalance += Deposit;

        cout << "\n\nDone Successfully. New balance = "
            << Client.AccountBalance << endl;

        return true;
    }
    else
    {
        cout << "\n\nDeposit Operation Cancelled.\n";

        return false;
    }
}

void ShowCheckBalance(int Balance)
{
    ShowNameScreen("Check Balance");

    cout << "Your Balance is " << Balance << endl;
}

void AtmOptions(vector<sClient>& vClients, int Index)
{
    short Option = 0;
    bool Work = true;

    while (Work)
    {
        ShowAtmMainMenu();

        cin >> Option;

        switch (Option)
        {
        case enAtmMainMenuOptions::eQuickWithdraw:

            if (QuickWithdrawBalance(vClients[Index]))
            {
                SaveClientsDataToFile(ClientsFileName, vClients);
            }

            GoBackToMainMenu();
            break;

        case enAtmMainMenuOptions::eNormalWithdraw:


            if (NormalWithdrawBalance(vClients[Index]))
            {
                SaveClientsDataToFile(ClientsFileName, vClients);
            }

            GoBackToMainMenu();
            break;

        case enAtmMainMenuOptions::eDeposit:


            if (DepositBalance(vClients[Index]))
            {
                SaveClientsDataToFile(ClientsFileName, vClients);
            }

            GoBackToMainMenu();
            break;

        case enAtmMainMenuOptions::eCheckBalance:

            ShowCheckBalance(vClients[Index].AccountBalance);

            GoBackToMainMenu();
            break;

        case enAtmMainMenuOptions::eLogout:

            SaveClientsDataToFile(ClientsFileName, vClients);

            Work = false;
            break;
        }
    }
}

int CheckUserNameAndPinCode(const vector<sClient>& vClients)
{
    string AccountNumber = "";
    string PinCode = "";

    bool LoginFailed = false;

    while (true)
    {
        ShowNameScreen("Login");

        if (LoginFailed)
        {
            cout << "Invalid AccountNumber/PinCode!\n";
        }

        cout << "Enter AccountNumber? ";
        cin >> AccountNumber;

        cout << "Enter PinCode? ";
        cin >> PinCode;

        for (int i = 0; i < vClients.size(); i++)
        {
            if (vClients[i].AccountNumber == AccountNumber &&
                vClients[i].PinCode == PinCode)
            {
                return i;
            }
        }

        LoginFailed = true;
    }
}

void LogIn()
{
    while (true)
    {
        vector<sClient> vClients =
            LoadDataFromFile(ClientsFileName);

        int Index = CheckUserNameAndPinCode(vClients);

        if (Index >= 0)
        {
            AtmOptions(vClients, Index);
        }
    }
}

int main()
{
    LogIn();

    return 0;
}