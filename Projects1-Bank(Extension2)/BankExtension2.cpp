#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <limits>
#include <string>

using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";



enum enMainMenuOptions {
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eShowTransactions = 6,
    eShowManageUsers = 7,
    eLogout = 8
};

enum enTransactionsOptions {
    eDeposit = 1,
    eWithdraw = 2,
    eTotalBalance = 3,
    eTransMainMenu = 4
};

enum enManageUsersOptions {
    eListUsers = 1,
    eAddUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eUsersMainMenu = 6
};

enum enMainMenuPermissions {
    eAll = -1,
    pListClients = 1,
    pAddNewClient = 2,
    pDeleteClient = 4,
    pUpdateClients = 8,
    pFindClient = 16,
    pTransactions = 32,
    pManageUsers = 64
};

struct sClient {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

struct sUser {
    string UserName;
    string Password;
    int Permission = 0;
    bool MarkForDelete = false;
};


vector<string> SplitString(string Line, string Seperator = "#//#") {
    string sWord = "";
    short Pos = 0;
    vector<string> vTokens;
    while ((Pos = Line.find(Seperator)) != string::npos) {
        sWord = Line.substr(0, Pos);
        if (sWord != "") {
            vTokens.push_back(sWord);
        }
        Line = Line.erase(0, Pos + Seperator.length());
    }
    if (Line != "") {
        vTokens.push_back(Line);
    }
    return vTokens;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
    return Client.AccountNumber + Seperator +
           Client.PinCode + Seperator +
           Client.Name + Seperator +
           Client.Phone + Seperator +
           to_string(Client.AccountBalance);
}

string ConvertRecordToLineUser(sUser User, string Seperator = "#//#") {
    return User.UserName + Seperator +
           User.Password + Seperator +
           to_string(User.Permission);
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


sUser ConvertLineToRecordUser(string Line, string Seperator = "#//#") {
    vector<string> vUser = SplitString(Line, Seperator);
    sUser User;

        User.UserName = vUser[0];
        User.Password = vUser[1];
        User.Permission = stoi(vUser[2]);

    return User;
}



vector<sClient> LoadDataFromFile(string FileName) {
    vector<sClient> vClients;
    fstream MyFile(FileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        while (getline(MyFile, Line)) {
            if (Line != "") {
                vClients.push_back(ConvertLineToRecord(Line));
            }
        }
        MyFile.close();
    }
    return vClients;
}

vector<sUser> LoadDataFromFileUser(string FileName) {
    vector<sUser> vUsers;
    fstream MyFile(FileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        while (getline(MyFile, Line)) {
            if (Line != "") {
                vUsers.push_back(ConvertLineToRecordUser(Line));
            }
        }
        MyFile.close();
    }
    return vUsers;
}

void SaveClientsDataToFile(string FileName, const vector<sClient>& ClientList) {
    fstream MyFile(FileName, ios::out);
    if (MyFile.is_open()) {
        for (const sClient& C : ClientList) {
            if (!C.MarkForDelete) {
                MyFile << ConvertRecordToLine(C) << endl;
            }
        }
        MyFile.close();
    }
}

void SaveUserDataToFile(string FileName, const vector<sUser>& UserList) {
    fstream MyFile(FileName, ios::out);
    if (MyFile.is_open()) {
        for (const sUser& U : UserList) {
            if (!U.MarkForDelete) {
                MyFile << ConvertRecordToLineUser(U) << endl;
            }
        }
        MyFile.close();
    }
}



bool ExistsAccountNumber(const vector<sClient>& vClients, string AccountNumber) {
    for (const sClient& Client : vClients) {
        if (Client.AccountNumber == AccountNumber) return true;
    }
    return false;
}

bool ExistsUserName(const vector<sUser>& vUsers, string UserName) {
    for (const sUser& User : vUsers) {
        if (User.UserName == UserName) return true;
    }
    return false;
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

bool FindUserByUserName(const vector<sUser>& vUsers, sUser& User, string UserName) {
    for (const sUser& U : vUsers) {
        if (U.UserName == UserName) {
            User = U;
            return true;
        }
    }
    return false;
}

int FindClientIndex(const vector<sClient>& vClients, string AccountNumber) {
    for (int i = 0; i < vClients.size(); i++) {
        if (vClients[i].AccountNumber == AccountNumber) return i;
    }
    return -1;
}

int FindUserIndex(const vector<sUser>& vUsers, string UserName) {
    for (int i = 0; i < vUsers.size(); i++) {
        if (vUsers[i].UserName == UserName) return i;
    }
    return -1;
}


void GoBackToMainMenu() {
    cout << "\n\nPress Enter to go back...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void ShowNameScreen(const string& NameScreen) {
    system("cls");
    cout << "\n-----------------------------------\n";
    cout << "\t" << NameScreen << " Screen";
    cout << "\n-----------------------------------\n";
}

void PrintAccessDenied() {
    system("cls");
    cout << "\n__________________________________\n";
    cout << "Access Denied,\n"
         << "You don't have permission to do this,\n"
         << "Please contact your Admin.\n";
    cout << "__________________________________\n";
}

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

void ShowUserCard(const sUser& User) {
    cout << "\nThe following are the user details:\n";
    cout << "______________________________________\n";
    cout << "User name : " << User.UserName << endl;
    cout << "Password  : " << User.Password << endl;
    cout << "Permission: " << User.Permission << endl;
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

void ShowUserList(const vector<sUser>& UserList) {
    system("cls");
    cout << "\n\t\t\t\t\tUser List (" << UserList.size() << ") User(s).\n";
    cout << "___________________________________________________________________________________\n";
    cout << "| " << setw(15) << left << "Username"
         << "| " << setw(10) << left << "Password"
         << "| " << setw(20) << left << "Permission" << "|\n";
    cout << "___________________________________________________________________________________\n";

    for (const sUser& User : UserList) {
        cout << "| " << setw(15) << left << User.UserName
             << "| " << setw(10) << left << User.Password
             << "| " << setw(20) << left << User.Permission << "|\n";
    }
    cout << "___________________________________________________________________________________\n";
}


string ReadClientAccountNumber() {
    string AccountNumber = "";
    cout << "\nPlease enter Account Number? ";
    cin >> AccountNumber;
    return AccountNumber;
}

string ReadUserName() {
    string UserName = "";
    cout << "\nPlease enter Username? ";
    getline(cin >> ws, UserName);
    return UserName;
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

string ReadUserNameNotExists(const vector<sUser>& vUsers) {
    string UserName = "";
    cout << "\nPlease enter UserName: ";
    getline(cin >> ws, UserName);
    while (ExistsUserName(vUsers, UserName)) {
        cout << "\nUser With [" << UserName << "] already Exists! Enter another UserName: ";
        getline(cin >> ws, UserName);
    }
    return UserName;
}

sClient ChangeClientRecord(string AccountNumber) {
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

int ReadPermission() {
    int Permission = 0;
    char Answer = 'n';

    cout << "\nDo you want to give full access? (Y/N): ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        return enMainMenuPermissions::eAll;
    }

    cout << "\nDo you want to give access to :\n";

    cout << "\n[1] Show Client List? (Y/N): ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') Permission |= enMainMenuPermissions::pListClients;

    cout << "\n[2] Add New Client? (Y/N): ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') Permission |= enMainMenuPermissions::pAddNewClient;

    cout << "\n[3] Delete Client? (Y/N): ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') Permission |= enMainMenuPermissions::pDeleteClient;

    cout << "\n[4] Update Client? (Y/N): ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') Permission |= enMainMenuPermissions::pUpdateClients;

    cout << "\n[5] Find Client? (Y/N): ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') Permission |= enMainMenuPermissions::pFindClient;

    cout << "\n[6] Transactions? (Y/N): ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') Permission |= enMainMenuPermissions::pTransactions;

    cout << "\n[7] Manage Users? (Y/N): ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') Permission |= enMainMenuPermissions::pManageUsers;

    return Permission;
}

sUser ChangeUserRecord(string UserName) {
    sUser User;
    User.UserName = UserName;
    cout << "\nEnter Password? ";
    getline(cin >> ws, User.Password);
    User.Permission = ReadPermission();
    return User;
}



void AddClient(vector<sClient>& vClients) {
    ShowNameScreen("Add Clients");
    char Answer = 'n';
    do {
        string AccountNumber = ReadAccountNumberNotExists(vClients);
        sClient Client = ChangeClientRecord(AccountNumber);
        vClients.push_back(Client);
        cout << "\nClient Added Successfully, Do you want to add more clients? Y/N: ";
        cin >> Answer;
    } while (Answer == 'y' || Answer == 'Y');

    SaveClientsDataToFile(ClientsFileName, vClients);
}

void AddUser(vector<sUser>& vUsers) {
    ShowNameScreen("Add New User");
    char Answer = 'n';
    do {
        string UserName = ReadUserNameNotExists(vUsers);
        sUser User = ChangeUserRecord(UserName);
        vUsers.push_back(User);
        cout << "\nUser Added Successfully, Do you want to add more Users? Y/N: ";
        cin >> Answer;
    } while (Answer == 'y' || Answer == 'Y');

    SaveUserDataToFile(UsersFileName, vUsers);
}

bool DeleteClientByAccountNumber(vector<sClient>& vClients) {
    ShowNameScreen("Delete Clients");
    string AccountNumber = ReadClientAccountNumber();

    short Index = FindClientIndex(vClients, AccountNumber);

    if (Index != -1) {
        ShowClientCard(vClients[Index]);

        char Answer = 'n';
        cout << "\nAre you sure you want to delete this client? (y/n): ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            // 3. تعديل مباشر بدون أي Loop إضافي
            vClients[Index].MarkForDelete = true;
            SaveClientsDataToFile(ClientsFileName, vClients);
            vClients = LoadDataFromFile(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.\n";
            return true;
        }
        cout << "\n\nDelete Operation Cancelled.\n";
        return false;
    }

    cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
    return false;
}

bool DeleteUserByUserName(vector<sUser>& vUsers) {
    ShowNameScreen("Delete Users");
    sUser User;
    string UserName = ReadUserName();

    if (UserName == "Admin" || UserName == "admin") {
        cout << "\nYou cannot delete Admin user.\n";
        return false;
    }

    if (FindUserByUserName(vUsers, User, UserName)) {
        ShowUserCard(User);
        char Answer = 'n';
        cout << "\nAre you sure you want to delete this User? (y/n): ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            short Index = FindUserIndex(vUsers, UserName);
            vUsers[Index].MarkForDelete = true;
            SaveUserDataToFile(UsersFileName, vUsers);
            vUsers = LoadDataFromFileUser(UsersFileName);
            cout << "\n\nUser Deleted Successfully.\n";
            return true;
        }
        cout << "\n\nDelete Operation Cancelled.\n";
        return false;
    }
    cout << "\nUser with Username (" << UserName << ") is Not Found!\n";
    return false;
}

bool UpdateClientByAccountNumber(vector<sClient>& vClients) {
    ShowNameScreen("Update Clients");
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(vClients, Client, AccountNumber)) {
        ShowClientCard(Client);
        char Answer = 'n';
        cout << "\nAre you sure you want to Update this client? (y/n): ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            short Index = FindClientIndex(vClients, AccountNumber);
            vClients[Index] = ChangeClientRecord(AccountNumber);
            SaveClientsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Updated Successfully.\n";
            return true;
        }
        cout << "\n\nUpdate Operation Cancelled.\n";
        return false;
    }
    cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
    return false;
}

bool UpdateUserByUserName(vector<sUser>& vUsers) {
    ShowNameScreen("Update Users");
    sUser User;
    string UserName = ReadUserName();

    if (FindUserByUserName(vUsers, User, UserName)) {
        ShowUserCard(User);
        char Answer = 'n';
        cout << "\nAre you sure you want to Update this User? (y/n): ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            short Index = FindUserIndex(vUsers, UserName);
            vUsers[Index] = ChangeUserRecord(UserName);
            SaveUserDataToFile(UsersFileName, vUsers);
            cout << "\n\nUser Updated Successfully.\n";
            return true;
        }
        cout << "\n\nUpdate Operation Cancelled.\n";
        return false;
    }
    cout << "\nUser with Username (" << UserName << ") is Not Found!\n";
    return false;
}

void FindClient(const vector<sClient>& vClients) {
    ShowNameScreen("Find Clients");
    string AccountNumber = ReadClientAccountNumber();
    short Index = FindClientIndex(vClients, AccountNumber);
    if (Index != -1) {
        ShowClientCard(vClients[Index]);
    } else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
    }
}

void FindUser(const vector<sUser>& vUsers) {
    ShowNameScreen("Find Users");
    string UserName = ReadUserName();
    short Index = FindUserIndex(vUsers, UserName);
    if (Index != -1) {
        ShowUserCard(vUsers[Index]);
    } else {
        cout << "\nUser with Username (" << UserName << ") is Not Found!\n";
    }
}

bool DepositBalanceToClientByAccountNumber(vector<sClient>& vClients) {
    ShowNameScreen("Deposit Clients");
    string AccountNumber = ReadClientAccountNumber();
    short Index = FindClientIndex(vClients, AccountNumber);

    if (Index != -1) {
        ShowClientCard(vClients[Index]);
        double Deposit = 0;
        cout << "Please enter deposit amount? ";
        cin >> Deposit;

        char Answer = 'n';
        cout << "Are you sure you want perform this transaction? (y/n): ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            vClients[Index].AccountBalance += Deposit;
            SaveClientsDataToFile(ClientsFileName, vClients);
            cout << "\n\nDone Successfully. New balance = " << vClients[Index].AccountBalance << endl;
            return true;
        }
        cout << "\n\nDeposit Operation Cancelled.\n";
        return false;
    }
    cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
    return false;
}

bool WithdrawBalanceToClientByAccountNumber(vector<sClient>& vClients) {
    ShowNameScreen("Withdraw Clients");
    string AccountNumber = ReadClientAccountNumber();
    short Index = FindClientIndex(vClients, AccountNumber);

    if (Index != -1) {
        ShowClientCard(vClients[Index]);
        double Amount = 0;
        cout << "Please enter withdraw amount? ";
        cin >> Amount;

        while (vClients[Index].AccountBalance < Amount) {
            cout << "Amount Exceeds the balance, you can Withdraw up to: " << vClients[Index].AccountBalance << endl;
            cout << "Please enter another amount? ";
            cin >> Amount;
        }

        char Answer = 'n';
        cout << "Are you sure you want perform this transaction? (y/n): ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            vClients[Index].AccountBalance -= Amount;
            SaveClientsDataToFile(ClientsFileName, vClients);
            cout << "\n\nDone Successfully. New balance = " << vClients[Index].AccountBalance << endl;
            return true;
        }
        cout << "\n\nWithdraw Operation Cancelled.\n";
        return false;
    }
    cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
    return false;
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

void TransactionsOptions(vector<sClient>& vClients) {
    short Option = 0;
    bool Work = true;
    while (Work) {
        ShowTransactionsMenu();
        cin >> Option;
        switch (Option) {
            case enTransactionsOptions::eDeposit:
                DepositBalanceToClientByAccountNumber(vClients);
                GoBackToMainMenu();
                break;
            case enTransactionsOptions::eWithdraw:
                WithdrawBalanceToClientByAccountNumber(vClients);
                GoBackToMainMenu();
                break;
            case enTransactionsOptions::eTotalBalance:
                ShowTotalBalancesMenu(vClients);
                GoBackToMainMenu();
                break;
            case enTransactionsOptions::eTransMainMenu:
                Work = false;
                break;
        }
    }
}

void ShowManageUsersMenu() {
    system("cls");
    cout << "=================================================\n";
    cout << "\t\tManage Users Menu Screen\n";
    cout << "=================================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";
    cout << "=================================================\n";
    cout << "Choose what do you want to do? [1 to 6]? ";
}

void ManageUsersOptions() {
    vector<sUser> vUsers = LoadDataFromFileUser(UsersFileName);
    short Option = 0;
    bool Work = true;
    while (Work) {
        ShowManageUsersMenu();
        cin >> Option;
        switch (Option) {
            case enManageUsersOptions::eListUsers:
                ShowUserList(vUsers);
                GoBackToMainMenu();
                break;
            case enManageUsersOptions::eAddUser:
                AddUser(vUsers);
                GoBackToMainMenu();
                break;
            case enManageUsersOptions::eDeleteUser:
                DeleteUserByUserName(vUsers);
                GoBackToMainMenu();
                break;
            case enManageUsersOptions::eUpdateUser:
                UpdateUserByUserName(vUsers);
                GoBackToMainMenu();
                break;
            case enManageUsersOptions::eFindUser:
                FindUser(vUsers);
                GoBackToMainMenu();
                break;
            case enManageUsersOptions::eUsersMainMenu:
                Work = false;
                break;
        }
    }
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
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "=================================================\n";
    cout << "Choose what do you want to do? [1 to 8]? ";
}

void StartApplication(sUser& User) {
    vector<sClient> vClients = LoadDataFromFile(ClientsFileName);
    short Option = 0;
    bool Work = true;
    while (Work) {
        ShowMainMenu();
        cin >> Option;
        switch (Option) {
            case enMainMenuOptions::eListClients:
                if (User.Permission & enMainMenuPermissions::pListClients) {
                    ShowClientList(vClients);
                } else {
                    PrintAccessDenied();
                }
                GoBackToMainMenu();
                break;

            case enMainMenuOptions::eAddNewClient:
                if (User.Permission & enMainMenuPermissions::pAddNewClient) {
                    AddClient(vClients);
                } else {
                    PrintAccessDenied();
                }
                GoBackToMainMenu();
                break;

            case enMainMenuOptions::eDeleteClient:
                if (User.Permission & enMainMenuPermissions::pDeleteClient) {
                    DeleteClientByAccountNumber(vClients);
                } else {
                    PrintAccessDenied();
                }
                GoBackToMainMenu();
                break;

            case enMainMenuOptions::eUpdateClient:
                if (User.Permission & enMainMenuPermissions::pUpdateClients) {
                    UpdateClientByAccountNumber(vClients);
                } else {
                    PrintAccessDenied();
                }
                GoBackToMainMenu();
                break;

            case enMainMenuOptions::eFindClient:
                if (User.Permission & enMainMenuPermissions::pFindClient) {
                    FindClient(vClients);
                } else {
                    PrintAccessDenied();
                }
                GoBackToMainMenu();
                break;

            case enMainMenuOptions::eShowTransactions:
                if (User.Permission & enMainMenuPermissions::pTransactions) {
                    TransactionsOptions(vClients);
                } else {
                    PrintAccessDenied();
                    GoBackToMainMenu();
                }
                break;

            case enMainMenuOptions::eShowManageUsers:
                if (User.Permission & enMainMenuPermissions::pManageUsers) {
                    ManageUsersOptions();
                } else {
                    PrintAccessDenied();
                    GoBackToMainMenu();
                }
                break;

            case enMainMenuOptions::eLogout:
                Work = false;
                break;
        }
    }
}



bool CheckUserNameAndPassword(const vector<sUser>& vUsers, sUser& User) {
    string UserName = "";
    string UserPassword = "";
    bool LoginFailed = false;

    while (true) {
        ShowNameScreen("Login");
        if (LoginFailed) {
            cout << "Invalid Username/Password!\n";
        }
        cout << "Enter Username? \n";
        cin >> UserName;
        cout << "Enter Password? ";
        cin >> UserPassword;

        for (const sUser& U : vUsers) {
            if (U.UserName == UserName && U.Password == UserPassword) {
                User = U;
                return true;
            }
        }
        LoginFailed = true;
    }
}


void LogIn() {
    while (true) {
        vector<sUser> vUsers = LoadDataFromFileUser(UsersFileName);
        sUser CurrentUser;

        if (CheckUserNameAndPassword(vUsers, CurrentUser)) {
            StartApplication(CurrentUser);
        }
    }
}

int main() {
    LogIn();
    return 0;
}