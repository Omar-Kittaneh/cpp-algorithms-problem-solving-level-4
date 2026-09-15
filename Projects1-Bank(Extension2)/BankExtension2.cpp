#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <limits>
using namespace std;

const string ClientsFileName = "Clients.txt";
enum enClient { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Transactions = 6 ,Exit = 7 };
enum enTransactions{Deposit = 1 , Withdraw = 2, TotalBalance = 3, MainMenu = 4 };

struct sClient {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

void ShowClientCard(const sClient& Client) {
    cout << "\nThe following are the client details:\n";
    cout << "______________________________________\n";
    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "Pin Code       : " << Client.PinCode << endl;
    cout << "Name           : " << Client.Name << endl;
    cout << "Phone          : " << Client.Phone << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
    cout << "______________________________________\n";
}

void ShowClientList(const vector<sClient>& ClientList) {
    system("cls");
    cout << "\n\t\t\t\t\tClients List (" << ClientList.size() << ") Client(s).\n";
    cout << "___________________________________________________________________________________\n";
    cout << "| " << setw(15) << left << "Account Number"
         << "| " << setw(10) << left << "Pin Code"
         << "| " << setw(20) << left << "Client Name"
         << "| " << setw(15) << left << "Phone"
         << "| " << setw(10) << left << "Balance" << "|\n";
    cout << "___________________________________________________________________________________\n";

    if (ClientList.empty()) {
        cout << "\t\t\t\tNo Clients Available In the System!\n";
    } else {
        for (const sClient& Client : ClientList) {
            cout << "| " << setw(15) << left << Client.AccountNumber
                 << "| " << setw(10) << left << Client.PinCode
                 << "| " << setw(20) << left << Client.Name
                 << "| " << setw(15) << left << Client.Phone
                 << "| " << setw(10) << left << Client.AccountBalance << "|\n";
        }
    }
    cout << "___________________________________________________________________________________\n";
}

void ShowMainMenu() {
    system("cls");

    cout << "=================================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "=================================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "=================================================\n";
    cout << "Choose what do you want to do? [1 to 7]? ";
}

void PrintExit() {
    system("cls");
    cout << "\n__________________________________\n";
    cout << "           Program Ends :-)";
    cout << "\n__________________________________\n";
}

void GoBackToMainMenu() {

    cout << "\n\nPress Enter to go back to Main Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void ShowNameClientScreen(const string& NameScreen) {
    system("cls");
    cout << "\n-----------------------------------\n";
    cout << "\t"<<NameScreen<< " Client Screen";
    cout << "\n-----------------------------------\n";
}

void ShowTransactionsMenu() {
      system("cls");

    cout << "=================================================\n";
    cout << "\t\tTransactions Menu Screen\n";
    cout << "=================================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menu.\n";
    cout << "=================================================\n";
    cout << "Choose what do you want to do? [1 to 4]? ";
}

void ShowTotalBalancesMenu(const vector<sClient>& ClientList) {
    system("cls");
    double TotalBalances = 0;
    cout << "\n\t\t\t\t\tClients List (" << ClientList.size() << ") Client(s).\n";
    cout << "___________________________________________________________________________________\n";
    cout << "| " << setw(15) << left << "Account Number"
         << "| " << setw(40) << left << "Client Name"
         << "| " << setw(10) << left << "Balance" << endl;
    cout << "___________________________________________________________________________________\n";

    if (ClientList.empty()) {
        cout << "\t\t\t\tNo Clients Available In the System!\n";
    } else {
        for (const sClient& Client : ClientList) {
            TotalBalances += Client.AccountBalance;
            cout << "| " << setw(15) << left << Client.AccountNumber
                 << "| " << setw(40) << left << Client.Name
                 << "| " << setw(10) << left << Client.AccountBalance << endl;
        }
    }
    cout << "___________________________________________________________________________________\n";
    cout << "\t\t\t\tTotal Balances = " << TotalBalances << endl;
}

string ReadClientAccountNumber() {
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

sClient ChangeClienRecord(string AccountNumber) {
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

bool ExistsAccountNumber(const vector<sClient>& vClients, string AccountNumber) {
    for (const sClient& Client : vClients) {
        if (Client.AccountNumber == AccountNumber) {
            return true;
        }
    }
    return false;
}

string ReadAccountNumberNotExists(const vector<sClient>& vClients) {
    string AccountNumber = "";
    cout << "\nPlease enter account number: ";
    cin >> AccountNumber;
    while (ExistsAccountNumber(vClients, AccountNumber)) {
        cout << "\nClient With [" << AccountNumber << "] already Exists! Enter another account number: ";
        cin >> AccountNumber;
    }
    return AccountNumber;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

vector<string> SplitString(string Line, string Seperator) {
    string sWord = "";
    short Pos = 0;
    vector<string> vClient;
    while ((Pos = Line.find(Seperator)) != string::npos) {
        sWord = Line.substr(0, Pos);
        if (sWord != "") {
            vClient.push_back(sWord);
        }
        Line = Line.erase(0, Pos + Seperator.length());
    }
    if (Line != "") {
        vClient.push_back(Line);
    }
    return vClient;
}

sClient ConvertLineToRecord(string Line, string Seperator = "#//#") {
    vector<string> vClient = SplitString(Line, Seperator);
    sClient Client;
    Client.AccountNumber = vClient[0];
    Client.PinCode = vClient[1];
    Client.Name = vClient[2];
    Client.Phone = vClient[3];
    Client.AccountBalance = stod(vClient[4]);
    return Client;
}

vector<sClient> LoadDataFromFile(string FileName) {
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        while (getline(MyFile, Line)) {
            if (Line != "") {
                sClient Client = ConvertLineToRecord(Line);
                vClients.push_back(Client);
            }
        }
        MyFile.close();
    }
    return vClients;
}

void SaveCleintsDataToFile(string FileName, vector<sClient>& ClientList, bool Delete = false) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open()) {
        for (sClient& C : ClientList) {
            if (Delete) {
                if (!C.MarkForDelete) {
                    MyFile << ConvertRecordToLine(C) << endl;
                }
            } else {
                MyFile << ConvertRecordToLine(C) << endl;
            }
        }
        MyFile.close();
    }
}

bool FindClientByAccountNumber(const vector<sClient>& vClients, sClient& Client, string AccountNumber) {
    for (const sClient& C : vClients) {
        if (C.AccountNumber == AccountNumber) {
            Client = C;
            return true;
        }
    }
    return false;
}

short FindClientIndex(const vector<sClient>& vClients, string AccountNumber) {
    short Index = 0;
    for (const sClient& C : vClients) {
        if (C.AccountNumber == AccountNumber) {
            return  Index;
        }
        Index++;
    }
    return -1;
}

bool MarkForDelete(vector<sClient>& vClients, string AccountNumber) {
    for (sClient& C : vClients) {
        if (C.AccountNumber == AccountNumber) {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

void AddClient(vector<sClient>& vClients) {
    ShowNameClientScreen("Add");
    char Answer = 'n';
    do {
        string AccountNumber = ReadAccountNumberNotExists(vClients);
        sClient Client = ChangeClienRecord(AccountNumber);
        vClients.push_back(Client);
        cout << "\nClient Added Successfully, Do you want to add more clients? Y/N: ";
        cin >> Answer;
    } while (Answer == 'y' || Answer == 'Y');

    SaveCleintsDataToFile(ClientsFileName, vClients);
}

bool DeleteClientByAccountNumber(vector<sClient>& vClients) {
    ShowNameClientScreen("Delete");
    char Answer = 'n';
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(vClients, Client, AccountNumber)) {
        ShowClientCard(Client);
        cout << "\nAre you sure you want to delete this client? (y/n): ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            MarkForDelete(vClients, AccountNumber);
            SaveCleintsDataToFile(ClientsFileName, vClients, true);
            vClients = LoadDataFromFile(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.\n";
            return true;
        } else {
            cout << "\n\nDelete Operation Cancelled.\n";
            return false;
        }
    } else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
        return false;
    }
}

bool UpdateClientByAccountNumber(vector<sClient>& vClients) {
    ShowNameClientScreen("Update");
    char Answer = 'n';
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(vClients, Client, AccountNumber)) {
        ShowClientCard(Client);
        cout << "\nAre you sure you want to Update this client? (y/n): ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            for (sClient& C : vClients) {
                if (C.AccountNumber == AccountNumber) {
                    C = ChangeClienRecord(C.AccountNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Updated Successfully.\n";
            return true;
        } else {
            cout << "\n\nUpdate Operation Cancelled.\n";
            return false;
        }
    } else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
        return false;
    }
}

void FindClient(const vector<sClient>& vClients) {
    ShowNameClientScreen("Find");
    string AccountNumber = ReadClientAccountNumber();
    short Index = FindClientIndex(vClients, AccountNumber);
    if (Index != -1) {
        ShowClientCard(vClients[Index]);
    } else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
    }
}

bool DepositBalanceToClientByAccountNumber(vector<sClient>& vClients) {
    ShowNameClientScreen("Deposit");
    char Answer = 'n';
    double Deposit = 0;
    string AccountNumber = ReadClientAccountNumber();
    short Index = FindClientIndex(vClients, AccountNumber);
    if (Index != -1) {
        ShowClientCard(vClients[Index]);
        cout << "Please enter deposit amount?\n";
        cin >> Deposit;
        cout << "Are you sure you want perform this transactions? (y/n): \n";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            vClients[Index].AccountBalance += Deposit;
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nDone Successfully new balance = " << vClients[Index].AccountBalance << endl;
            return true;
        }
        else {
            cout << "\n\nDeposit Operation Cancelled.\n";
            return false;
        }
    }
    else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
        return false;
    }

}

bool WithdrawBalanceToClientByAccountNumber(vector<sClient>& vClients) {
    ShowNameClientScreen("Withdraw");
    char Answer = 'n';
    double Deposit = 0;
    string AccountNumber = ReadClientAccountNumber();
    short Index = FindClientIndex(vClients, AccountNumber);
    if (Index != -1) {
        ShowClientCard(vClients[Index]);
        cout << "Please enter withdraw amount?\n";
        cin >> Deposit;
        while (vClients[Index].AccountBalance < Deposit) {
            cout << "Amount Exceeds the balance, you can Withdraw up to : ";
            cout << vClients[Index].AccountBalance << endl;
            cout<< "Please enter another amount?\n";
            cin >> Deposit;
        }
        cout << "Are you sure you want perform this transactions(y/n): \n";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            vClients[Index].AccountBalance -= Deposit;
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nDone Successfully new balance = " << vClients[Index].AccountBalance << endl;
            return true;
        }
        else {
            cout << "\n\nWithdraw Operation Cancelled.\n";
            return false;
        }
    }
    else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
        return false;
    }
}

void TransactionsOpitons(vector<sClient>& vClients) {
      short Option = 0;
      bool Work = true;
      while (Work) {
          ShowTransactionsMenu();
          cin >> Option;
          switch (Option) {

              case enTransactions::Deposit: {
                  DepositBalanceToClientByAccountNumber(vClients);
                  GoBackToMainMenu();
                  break;
                }
              case enTransactions::Withdraw: {
                  WithdrawBalanceToClientByAccountNumber(vClients);
                  GoBackToMainMenu();
                  break;
              }
              case enTransactions::TotalBalance: {
                  ShowTotalBalancesMenu(vClients);
                  GoBackToMainMenu();
                  break;
              }
              case enTransactions::MainMenu: {
                  Work = false;
                  break;
              }

          }
      }
}

void StartApplication(vector<sClient>& vClients) {
    short option = 0;
    bool Work = true;
    while (Work) {
        ShowMainMenu();
        cin >> option;
        switch (option) {
            case enClient::Show:
                ShowClientList(vClients);
                GoBackToMainMenu();
                break;

            case enClient::Add:
                AddClient(vClients);
                GoBackToMainMenu();
                break;

            case enClient::Delete:
                DeleteClientByAccountNumber(vClients);
                GoBackToMainMenu();
                break;

            case enClient::Update:
                UpdateClientByAccountNumber(vClients);
                GoBackToMainMenu();
                break;

            case enClient::Find:
                FindClient(vClients);
                GoBackToMainMenu();
                break;

            case enClient::Transactions:
                TransactionsOpitons(vClients);
                break;

            case enClient::Exit:
                Work = false;
                PrintExit();
                break;
        }
    }
}

int main() {
    vector<sClient> ClientList = LoadDataFromFile(ClientsFileName);
    StartApplication(ClientList);
    return 0;
}