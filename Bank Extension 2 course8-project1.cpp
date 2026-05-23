
#include <iostream>
#include<string >
#include<vector>
#include<iomanip>
#include<fstream>

using namespace std;
struct stClient {

	string AccountNumber = "";
	string PinCode = "";
	string ClientName = "";
	string Phone = "";
	double Balance = 0;
	bool MarkForDelete = false;
};
struct stUser {
	string Name;
	string Password;
	int Permission;
	bool MarkForDelete = false;
};
enum enMainMenuOption
{
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eTarnsactionsList = 6,
	eManageUser = 7, eLogOut = 8

};
enum enTransactions {
	eDeposit = 1, eWithdraw = 2,
	eTotalBalance = 3, eMainMenue = 4
};
enum enManageUsersMenue
{
	eListUsers = 1, eAddNewUser = 2,
	eDeleteUser = 3, eUpdateUser = 4,
	eFindUser = 5, eMainMenueScreen = 6
};
enum enMainMenuePermissions {
	eAll = -1, pListClients = 1, pAddNewClient = 2,
	pDeleteClient = 4, pUpdateClients = 8,
	pFindClient = 16, pTranactions = 32,
	pManageUsers = 64
};

void ShowMainMenue();
void ShowTrasactionsScreen();
void ShowManageUserScreen();
bool CheckAccessPermissions(enMainMenuePermissions Permissions);
void Login();

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
stUser CurrentUser;



//Functions For Client Data
//load, save, split, converting  ,string ,files,search

vector<string> SplitString(string S1, string Delim = "#//#") {
	string Word;
	size_t Pos;
	vector<string>vDataString;
	while ((Pos = S1.find(Delim)) != string::npos) {
		Word = S1.substr(0, Pos);
		if (Word != "") {
			vDataString.push_back(Word);
		}

		S1.erase(0, Pos + Delim.length());

	}
	if (S1 != "") {
		vDataString.push_back(S1);
	}
	return vDataString;


}
stClient ConvertFromLineToRecord(const string& DataLine) {
	stClient Client;
	vector<string> DataSplited = SplitString(DataLine, "#//#");
	if (DataSplited.size() == 5) {
		Client.AccountNumber = DataSplited[0];
		Client.PinCode = DataSplited[1];
		Client.ClientName = DataSplited[2];
		Client.Phone = DataSplited[3];
		Client.Balance = stod(DataSplited[4]);

	}return Client;

}
string ConvertFromClientRecordToLine(const stClient& Client, string  Delim = "#//#") {
	string Line = Client.AccountNumber + Delim;
	Line += Client.PinCode + Delim;
	Line += Client.ClientName + Delim;
	Line += Client.Phone + Delim;
	Line += std::to_string(Client.Balance) + Delim;
	return Line;
}
vector <stClient> LoadClientsDataFromFile(const string& ClientsFileName) {
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::in);
	vector<stClient> vClients;
	if (MyFile.is_open()) {
		string DataLine;

		stClient Client;
		while (getline(MyFile, DataLine))
		{
			Client = ConvertFromLineToRecord(DataLine);
			if (Client.AccountNumber != "")
				vClients.push_back(Client);

		}
		MyFile.close();
	}

	return vClients;

}
void SaveClientsDataToFile(const string& ClientsFileName, const vector<stClient>& vClients) {

	fstream MyFile;
	MyFile.open(ClientsFileName, ios::out);

	if (MyFile.is_open()) {
		string DataLine;
		for (const stClient& C : vClients) {
			if (C.MarkForDelete == false) {
				DataLine = ConvertFromClientRecordToLine(C);
				MyFile << DataLine << endl;
			}

		}

		MyFile.close();
	}
	else {

		cout << "\aFile ( " << ClientsFileName << " ) Can Not Open !";
	}

}
bool FindClientByAccountNumber(const string& AccountNumber, const vector<stClient>& vClients, stClient& Client) {
	for (const stClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;
		}
	}
	return false;
}
bool ClientExistsByAccountNumber(const string& AccountNumber, string  ClientsFileName) {
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::in);
	if (MyFile.is_open()) {
		string DataLine;

		stClient Client;
		while (getline(MyFile, DataLine))
		{
			Client = ConvertFromLineToRecord(DataLine);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();

				return true;
			}
		}
	}
	MyFile.close();

	return false;
}


//Go Back
void GoBackToMainMenu() {
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}
void GoBackToTransactionsMenu() {

	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	ShowTrasactionsScreen();
}
void GoBackToManageUserMenue() {
	cout << "\n\nPress any key to go back to Manage User Menue...";
	system("pause>0");
	ShowManageUserScreen();
}
//permissions 
bool CheckAccessPermissions(enMainMenuePermissions Permissions) {
	return  ((CurrentUser.Permission & Permissions) == Permissions);
}
int ReadPermissionsToSet() {
	char Answer;
	int Permissions = 0;
	cout << "\nDo You want to give full access? Y/N?";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{

		return -1;

	}



	cout << "\nDo You want to give  access to : \n";

	cout << "Show Client List ? Y/N?";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermissions::pListClients;
	}

	cout << "\nAdd New Client  ? Y/N?";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermissions::pAddNewClient;
	}

	cout << "\nDelete Client  ? Y/N?";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermissions::pDeleteClient;
	}

	cout << "\nUpdate Client  ? Y/N?";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermissions::pUpdateClients;
	}

	cout << "\nFind Client  ? Y/N?";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermissions::pFindClient;
	}

	cout << "\nTransactions? Y/N?";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermissions::pTranactions;
	}

	cout << "\nManage Users  ? Y/N?";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermissions::pManageUsers;
	}

	return Permissions;
}
void ShowAccessDeniedMessage() {
	cout << "--------------------------------------\n";
	cout << "Access Denied,\n";
	cout << "You Don't have premission to do this,\n";
	cout << "Please conact your Admin.\n";
	cout << "--------------------------------------\n";


}
//ShowClientsList

void PrintClientRecordLine(const stClient& Client) {

	cout << "|" << left << setw(12) << Client.AccountNumber;
	cout << "|" << left << setw(8) << Client.PinCode;
	cout << "|" << left << setw(40) << Client.ClientName;
	cout << "|" << left << setw(12) << Client.Phone;
	cout << "|" << left << setw(12) << Client.Balance;

}
void PrintClientCard(const stClient& Client) {

	cout << "\nThis Following is Client Info :\n";
	cout << "__________________________________________\n";
	cout << "Account Number : " << Client.AccountNumber << endl;
	cout << "PinCode : " << Client.PinCode << endl;
	cout << "Client Name : " << Client.ClientName << endl;
	cout << "Phone : " << Client.Phone << endl;
	cout << "Balance : " << Client.Balance << endl;
	cout << "__________________________________________\n";


}
void ShowAllClientsScreen() {
	if (!CheckAccessPermissions(enMainMenuePermissions::pListClients))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}

	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\n\n\t\t\tClients List (" << vClients.size() << ") Client(s).";
	cout << "\n________________________________________________________________________________________\n";
	cout << "|" << left << setw(15) << "Account Number";
	cout << "|" << left << setw(8) << "PinCode";
	cout << "|" << left << setw(40) << "Client Name";
	cout << "|" << left << setw(12) << "Phone";
	cout << "|" << left << setw(12) << "Balance";
	cout << "\n________________________________________________________________________________________\n";
	if (vClients.size() != 0) {
		for (const stClient& C : vClients) {
			PrintClientRecordLine(C);
			cout << endl;
		}
	}
	else {

		cout << "\t\t\t\tNo Clients Available in system!";
	}
	cout << "\n________________________________________________________________________________________\n";


}

//Add New Client Screen

stClient ReadNewClient() {
	stClient Client;

	cout << "Enter Account Number?";
	getline(cin >> ws, Client.AccountNumber);


	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName)) {

		cout << "\n\aClient with [" << Client.AccountNumber << "] already exists, Enter Another Account Number? \a";

		getline(cin >> ws, Client.AccountNumber);

	}
	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);

	cout << "Enter Client Name? ";
	getline(cin, Client.ClientName);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter Balance? ";
	cin >> Client.Balance;

	return Client;

}
string ReadAccountNumber(string Message = "Please Enter Account Number?") {
	string AccountNumber;

	cout << Message;
	getline(cin >> ws, AccountNumber);
	return AccountNumber;

}
void AddDataLineToFile(string ClientsFileName, string DataLine) {
	fstream MyFile(ClientsFileName, ios::out | ios::app);
	if (MyFile.is_open()) {

		MyFile << DataLine << endl;

	}
	else {
		cout << "File Can't open !";

	}

	MyFile.close();


}
void AddNewClient() {
	stClient Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertFromClientRecordToLine(Client));
}
void AddNewClients() {
	char AddMore = 'y';
	do {
		cout << "\n\n\nAdding New Client :\n\n";
		AddNewClient();
		cout << "Client Added successfully .\n";

		cout << "Do you want to add new client ? y/n ?";
		cin >> AddMore;

	} while (tolower(AddMore) == 'y');

}
void ShowAddNewClientsScreen() {
	if (!CheckAccessPermissions(enMainMenuePermissions::pAddNewClient))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";

	AddNewClients();


}

//Delete Client 

void MarkClientForDelete(string AccountNumber, vector<stClient>& vClients) {
	for (stClient& C : vClients)
		if (C.AccountNumber == AccountNumber)
			C.MarkForDelete = true;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClients) {
	char Answer = 'y';
	stClient Client;
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		cout << "Are you sure you want to delete this client ? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			MarkClientForDelete(AccountNumber, vClients);
			SaveClientsDataToFile(ClientsFileName, vClients);
			//Refresh Clients
			vClients = LoadClientsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Succssfully:-)\n";
			return true;
		}
	}
	else {
		cout << "\aClient with [" << AccountNumber << "]  not found \n";
		return false;
	}

}
void ShowDeleteClientScreen() {
	if (!CheckAccessPermissions(enMainMenuePermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}
	cout << "\n=========================================\n";
	cout << "\tDelete Client Screen";
	cout << "\n=========================================\n";
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);

}


//update client 

stClient ChangeClientRecord(string AccountNumber) {
	stClient Client;
	Client.AccountNumber = AccountNumber;

	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Client Name? ";
	getline(cin, Client.ClientName);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter Balance? ";
	cin >> Client.Balance;

	return Client;



}
bool  UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClients) {
	char Answer = 'y';
	stClient Client;



	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		cout << "Are you sure you want update this client ? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			for (stClient& C : vClients) {
				if (C.AccountNumber == AccountNumber) {

					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "\n\nClient updated Succssfully:-)\n";
			return true;
		}
	}
	else {
		cout << "\aClient with [" << AccountNumber << "]  not found \n\a";
		return false;
	}
}
void ShowUpdateClientScreen() {
	if (!CheckAccessPermissions(enMainMenuePermissions::pUpdateClients))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}
	cout << "\n=========================================\n";
	cout << "\tUpdate Client Screen";
	cout << "\n=========================================\n";
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}


//find Client Screen
void ShowFindClientScreen() {
	if (!CheckAccessPermissions(enMainMenuePermissions::pFindClient))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}

	cout << "\n=========================================\n";
	cout << "\tFind Client Screen";
	cout << "\n=========================================\n";
	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	stClient Client;
	Client.AccountNumber = ReadAccountNumber();;
	if (FindClientByAccountNumber(Client.AccountNumber, vClients, Client)) {


		PrintClientCard(Client);

	}
	else {
		cout << "Client with [" << Client.AccountNumber << "]  not found \n";
	}




}

//end Screen
void ShowEndScreen() {
	cout << "\n==================================\n";
	cout << "\n         Program Ends .\n";
	cout << "\n==================================\n";
	system("pause>0");
}




//deposit:
bool DepositBalanceToClientByAccountNumber(const string& AccountNumber, double Amount, vector<stClient>& vClients) {
	char Answer = 'n';
	cout << "Are you sure you want perform this transaction? y/n? ";
	cin >> Answer;
	if (tolower(Answer) == 'y') {
		for (stClient& C : vClients) {
			if (C.AccountNumber == AccountNumber) {

				C.Balance += Amount;
				SaveClientsDataToFile(ClientsFileName, vClients);
				cout << "\nDone Successfully. New Balance is: " << C.Balance << endl;
				return true;

			}
		}
	}
	return false;

}
void ShowDepositScreen() {
	cout << "\n==================================\n";
	cout << "\n         Deposit Screen.\n";
	cout << "\n==================================\n";
	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	stClient Client;
	string AccountNumber = ReadAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "Client with[" << AccountNumber << "]does not exist.\n";
		cout << "Enter Another AccountNumber :\n";
		AccountNumber = ReadAccountNumber();

	}

	PrintClientCard(Client);

	double DepositAmount = 0;
	cout << "Please enter Deposit Amount?";
	cin >> DepositAmount;

	DepositBalanceToClientByAccountNumber(AccountNumber, DepositAmount, vClients);

}

//withdraw:
void ShowWithDrawScreen() {
	cout << "\n==================================\n";
	cout << "\n         WithDraw Screen.\n";
	cout << "\n==================================\n";
	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	stClient Client;
	string AccountNumber = ReadAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "Client with[" << AccountNumber << "] does not exist.\n";
		cout << "Enter Another AccountNumber :\n";
		AccountNumber = ReadAccountNumber();

	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "Please enter withdraw Amount?";
	cin >> Amount;
	while (Amount > Client.Balance) {

		cout << "\nAmount Exceeds the balance, you can withdraw up to : ";
		cout << Client.Balance << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;

	}
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);


}

//total balances screen ,printing:
void PrintClientBalanceLine(stClient Client) {
	cout << "|" << left << setw(14) << Client.AccountNumber;
	cout << "|" << left << setw(40) << Client.ClientName;
	cout << "|" << left << setw(12) << Client.Balance;

}
void ShowTotalBalances() {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\n\n\t\t\t\tBalances List (" << vClients.size() << ") Client(s).\n";
	cout << "\n________________________________________________________________________________________\n";
	cout << "|" << left << setw(12) << "Account Number";
	cout << "|" << left << setw(40) << "Client Name";
	cout << "|" << left << setw(12) << "Balance";
	cout << "\n________________________________________________________________________________________\n";
	double TotalBalances = 0;
	if (vClients.size() != 0) {
		for (const stClient& C : vClients) {
			PrintClientBalanceLine(C);
			cout << endl;
			TotalBalances += C.Balance;
		}
	}
	else {

		cout << "\t\t\t\tNo Clients Available in system!";
	}
	cout << "\n________________________________________________________________________________________\n";
	cout << "\t\t\t\t\t Total Balances = " << TotalBalances;
}
void ShowTotalBalancesScreen()
{
	ShowTotalBalances();
}

//transactions menue functions:
void PerformTranactionsMenuOption(enTransactions TransactionsMenueOption) {
	switch (TransactionsMenueOption) {
	case enTransactions::eDeposit:

		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenu();
		break;
	case enTransactions::eWithdraw:
		system("cls");
		ShowWithDrawScreen();
		GoBackToTransactionsMenu();


		break;
	case enTransactions::eTotalBalance:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionsMenu();

		break;
	case enTransactions::eMainMenue:
		system("cls");


		ShowMainMenue();


		break;
	}
}
short ReadTranactionsMenuOption() {
	short Choice = 0;
	while (Choice <= 0 || Choice > 4) {
		cout << "Choose what do you want to do? [1 to 4]? ";
		cin >> Choice;
	}
	return Choice;

}
void ShowTrasactionsScreen() {
	if (!CheckAccessPermissions(enMainMenuePermissions::pTranactions))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}
	system("cls");
	cout << "\n==================================\n";
	cout << "\n         Trasaction Screen .\n";
	cout << "\n==================================\n";
	cout << "\n      [1] Deposit.\n";
	cout << "\n      [2] Withdraw.\n";
	cout << "\n      [3] Total Balance.\n";
	cout << "\n      [4] Main Menue.\n";
	cout << "\n==================================\n";

	PerformTranactionsMenuOption(enTransactions(ReadTranactionsMenuOption()));
}



//Main menue functions:


void PerformMainMenuOption(enMainMenuOption MainMenuOption) {
	
	switch (MainMenuOption) {
	case enMainMenuOption::eListClients:
		
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOption::eAddNewClient:
		
		system("cls");
	    ShowAddNewClientsScreen();
	    GoBackToMainMenu();
		break;

	case enMainMenuOption::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOption::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOption::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOption::eTarnsactionsList:
		system("cls");
		ShowTrasactionsScreen();
		GoBackToTransactionsMenu();
		break;


	case enMainMenuOption::eManageUser:
		system("cls");
		ShowManageUserScreen();
		GoBackToManageUserMenue();
		break;

	case enMainMenuOption::eLogOut:
		system("cls");
		Login();
		break;

	}

}
short ReadMainMenueOption() {
	short Choice = 0;
	while (Choice <= 0 || Choice > 8) {
		cout << "Choose what do you want to do? [1 to 8]? ";
		cin >> Choice;
	}
	return Choice;

}
void ShowMainMenue( ) {

	system("cls");
	cout << "\n==================================\n";
	cout << "\n      Main Menue Screen.\n";
	cout << "\n==================================\n";
	cout << "\n      [1] Show Clients List.\n";
	cout << "\n      [2] Add New Client.\n";
	cout << "\n      [3] Delete Client.\n";
	cout << "\n      [4] update Client.\n";
	cout << "\n      [5] Find Client.\n";
	cout << "\n      [6] Tarnsactions.\n";
	cout << "\n      [7] Manage Users.\n";
	cout << "\n      [8] Logout.\n";
	cout << "\n================================\n";
	PerformMainMenuOption(enMainMenuOption(ReadMainMenueOption()));


}

//users


//list users
stUser ConvertFromLineToUserRecord(const string& DataLine) {
	stUser User;
	vector<string> DataSplited = SplitString(DataLine, "#//#");
	if (DataSplited.size() == 3) {
		User.Name = DataSplited[0];
		User.Password = DataSplited[1];
		User.Permission = stoi(DataSplited[2]);
		

	}return User;

}
vector <stUser> LoadUsersDataFromFile(const string& UsersFileName) {
	fstream MyFile;
	MyFile.open(UsersFileName, ios::in);
	vector<stUser> vUsers;
	if (MyFile.is_open()) {
		string DataLine;

		stUser User;
		while (getline(MyFile, DataLine))
		{
			User = ConvertFromLineToUserRecord(DataLine);
			if (User.Name != "")
				vUsers.push_back(User);

		}
		MyFile.close();
	}

	return vUsers;

}
void PrintUserRecordLine(const stUser& User) {

	cout << "|" << left << setw(15) << User.Name;
	cout << "|" << left << setw(8) << User.Password;
	cout << "|" << left << setw(40) << User.Permission;
	

}
void PrintUserCard(const stUser& User) {

	cout << "\nThis Following is User Info :\n";
	cout << "__________________________________________\n";
	cout << "Name       : " << User.Name << endl;
	cout << "Password   : " << User.Password << endl;
	cout << "Permission : " << User.Permission << endl;
	cout << "__________________________________________\n";


}
void ShowAllUsersScreen() {
	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

	cout << "\n\n\n\t\t\tUsers List (" << vUsers.size() << ") User(s).";
	cout << "\n________________________________________________________________________________________\n";
	cout << "|" << left << setw(15) << "User Name";
	cout << "|" << left << setw(8) << "Password";
	cout << "|" << left << setw(40) << "Permission";
	
	cout << "\n________________________________________________________________________________________\n";
	if (vUsers.size() != 0) {
		for (const stUser& U : vUsers) {
			PrintUserRecordLine(U);
			cout << endl;
		}
	}
	else {

		cout << "\t\t\t\tNo Users Available in system!";
	}
	cout << "\n________________________________________________________________________________________\n";


}


//functions for user data
string ConvertFromUserRecordToLine(const stUser& User, string  Delim = "#//#") {
	string Line = User.Name + Delim;
	Line += User.Password + Delim;
	Line += to_string(User.Permission) + Delim;

	return Line;
}
void SaveUsersDataToFile(const string& UsersFileName, const vector<stUser>& vUsers) {

	fstream MyFile;
	MyFile.open(UsersFileName, ios::out);

	if (MyFile.is_open()) {
		string DataLine;
		for (const stUser& C : vUsers) {
			if (C.MarkForDelete == false) {
				DataLine = ConvertFromUserRecordToLine(C);
				MyFile << DataLine << endl;
			}

		}

		MyFile.close();
	}
	else {

		cout << "\aFile ( " << UsersFileName << " ) Can Not Open !";
	}

}
bool UserExistsByUserName(const string& UserName, string  UserFileName) {
	fstream MyFile;
	MyFile.open(UserFileName, ios::in);
	if (MyFile.is_open()) {
		string DataLine;

		stUser User;
		while (getline(MyFile, DataLine))
		{
			User = ConvertFromLineToUserRecord(DataLine);
			if (User.Name == UserName)
			{
				MyFile.close();

				return true;
			}
		}
	}
	MyFile.close();

	return false;
}
bool FindUserByUserName(const string& UserName, const vector<stUser>& vUsers, stUser& User) {
	for (const stUser& U : vUsers) {
		if (U.Name == UserName ) {
			User = U;
			return true;
		}
	}
	return false;
}
bool FindUserByUserNameAndPassword(const string& UserName, const string& Password, stUser& User)
{

	const vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	for (const stUser& U : vUsers) {
		if (U.Name == UserName && U.Password == Password) {
			User = U;
			return true;
		}
	}
	return false;
}
void MarkUserForDelete(string UserName, vector<stUser>& vUsers) {

	for (stUser& C : vUsers) {
		if (C.Name == UserName)
		{
			C.MarkForDelete = true;
		}
	}
}


// add users
string ReadUserName(string Message = "Please Enter UserName?") {
	string UserName;

	cout << Message;
	getline(cin >> ws, UserName);
	return UserName;

}
stUser ReadNewUser() {
	stUser User;

	cout << "Enter User Name?";
	getline(cin >> ws, User.Name);


	while (UserExistsByUserName(User.Name, UsersFileName)) {

		cout << "\n\aUser with [" << User.Name << "] already exists, Enter Another User Name? \a";

		getline(cin >> ws,User.Name);

	}
	cout << "Enter Password? ";
	getline(cin, User.Password);

	User.Permission = ReadPermissionsToSet();

	return User;

}
void AddNewUser() {
	stUser User = ReadNewUser();
	AddDataLineToFile(UsersFileName, ConvertFromUserRecordToLine(User));
}
void AddNewUsers() {
	char AddMore = 'y';
	do {
		cout << "\n\n\nAdding New User :\n\n";
		AddNewUser();
		cout << "\nUser Added successfully .\n";

		cout << "\nDo you want to add new User ? y/n ?";
		cin >> AddMore;

	} while (tolower(AddMore) == 'y');

}
void ShowAddNewUserScreen() {

	cout << "\n-----------------------------------\n";
	cout << "\tAdd New User Screen";
	cout << "\n-----------------------------------\n";

	AddNewUsers();


}

//delete users

bool DeleteUserByUserName(string UserName, vector<stUser>& vUser) {
	
	if (UserName == "Admin")
	{
		cout << "\n\nYou cannot Delete This User.";
		return false;
	}

	char Answer = 'y';
	stUser User;

	if (FindUserByUserName(UserName, vUser, User)) {

		PrintUserCard(User);

		cout << "Are you sure you want to delete this User ? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			MarkUserForDelete(UserName, vUser);
			SaveUsersDataToFile(UsersFileName, vUser);

			//Refresh Clients
			vUser = LoadUsersDataFromFile(UsersFileName);
			cout << "\n\nUser Deleted Succssfully:-)\n";

			return true;
		}
	}
	else {

		cout << "\aUser with [" << UserName << "]  not found \n";
		return false;

	}

}
void ShowDeleteUserScreen() {
	cout << "\n=========================================\n";
	cout << "\tDelete User Screen";
	cout << "\n=========================================\n";
	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();
	DeleteUserByUserName(UserName, vUsers);

}

//update user 
stUser ChangeUserRecord(string UserName) {
	stUser User;
	User.Name = UserName;

	cout << "Enter password? ";
	getline(cin >> ws, User.Password);

	User.Permission = ReadPermissionsToSet();

	return User;



}
bool  UpdateUserByUserName(string UserName, vector<stUser>& vUsers) {
	char Answer = 'y';
	stUser User;
	if (FindUserByUserName(UserName, vUsers, User)) {
		PrintUserCard(User);
		cout << "Are you sure you want update this user ? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {
			for (stUser& U : vUsers) {
				if (U.Name ==UserName) {

					U = ChangeUserRecord(UserName);
					break;
				}
			}
			SaveUsersDataToFile(UsersFileName, vUsers);

			cout << "\n\User updated Succssfully:-)\n";
			return true;
		}
	}
	else {
		cout << "\User with [" << UserName << "]  not found \n\a";
		return false;
	}
}
void ShowUpdateUserScreen() {
	cout << "\n=========================================\n";
	cout << "\tUpdate User Screen";
	cout << "\n=========================================\n";
	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();
	UpdateUserByUserName(UserName, vUsers);
}

//find user Screen
void ShowFindUserScreen() {
	cout << "\n=========================================\n";
	cout << "\tFind User Screen";
	cout << "\n=========================================\n";
	vector<stUser>vUsers = LoadUsersDataFromFile(UsersFileName);
	stUser User;
	User.Name = ReadUserName();;
	if (FindUserByUserName(User.Name, vUsers, User)) {


		PrintUserCard(User);

	}
	else {
		cout << "User with [" << User.Name << "]  not found \n";
	}




}


//show manage users screen 
void PerformManageUserScreenOption(enManageUsersMenue ManageUsersMenue) {
	switch (ManageUsersMenue) {
	case enManageUsersMenue::eListUsers:
		system("cls");
		ShowAllUsersScreen();
		GoBackToManageUserMenue();
		break;
	case enManageUsersMenue::eAddNewUser:
		system("cls");
		ShowAddNewUserScreen();
		GoBackToManageUserMenue();

		break;
	case enManageUsersMenue::eDeleteUser:
		system("cls");
		ShowDeleteUserScreen();
		GoBackToManageUserMenue();
		break;
	case enManageUsersMenue::eUpdateUser:
		system("cls");

		ShowUpdateUserScreen();
		GoBackToManageUserMenue();

		break;
	case enManageUsersMenue::eFindUser:
		system("cls");

		ShowFindUserScreen();
		GoBackToManageUserMenue();
		break;
	case enManageUsersMenue::eMainMenueScreen:
		system("cls");
		ShowMainMenue();
		break;


	}

}
short ReadManageUserScreenOption() {
	short Choice = 0;
	while (Choice <= 0 || Choice > 6) {
		cout << "Choose what do you want to do? [1 to 6]? ";
		cin >> Choice;
	}
	return Choice;

}
void ShowManageUserScreen() {
	if (!CheckAccessPermissions(enMainMenuePermissions::pManageUsers))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}
	system("cls");
	cout << "\n==================================\n";
	cout << "\n      Manage User Menue Screen.\n";
	cout << "\n==================================\n";
	cout << "\n      [1] Show Users List.\n";
	cout << "\n      [2] Add New User.\n";
	cout << "\n      [3] Delete User.\n";
	cout << "\n      [4] Update User.\n";
	cout << "\n      [5] Find User.\n";
	cout << "\n      [6] Main Menue.\n";
	cout << "\n================================\n";
	PerformManageUserScreenOption(enManageUsersMenue(ReadManageUserScreenOption()));


}


//login 
bool LoadUserInfo(const string& UserName, const string& Password) {

	return FindUserByUserNameAndPassword(UserName, Password, CurrentUser);

}
void Login() {
	
	bool LoginFaild = false;
	string UserName, Password;

	do {
		system("cls");
		cout << "\n---------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n---------------------------------\n";

		if (LoginFaild) {
			cout << "\n\aInvlaid Username/Password!\n\n";
		}

		cout << "Please enter UserName ?\n";
		getline(cin >> ws , UserName );
		cout << "Please enter User Password?\n";
		getline(cin >> ws, Password);
		

		LoginFaild = !LoadUserInfo(UserName, Password);
	} while (LoginFaild);
	
	ShowMainMenue();
	
}


int main() 
{
	Login();

    return 0;
	system("puase>0");
}