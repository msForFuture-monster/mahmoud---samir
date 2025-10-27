#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string ClientFileName = "Client.text";

const string UserFileName = "User.text";

void MainMenueScreen();

void GoBackToMenue();

void GoBackToTransactionMenue();

void GoBackToManageUserMenue();

void Login();

enum enClientServent
{
	Show = 1,
	Add = 2,
	Delete = 3,
	Update = 4,
	Find = 5,
	Transaction = 6,
	ManageUser = 7,
	Loguot = 8
};

enum enTrnasaction
{
	Deposit = 1,
	withdraw = 2,
	TotalBalance = 3,
	MainMenue = 4
};

enum enManageUser
{
	ShowListOfUser = 1,
	AddNewUsers = 2,
	DeleteUser = 3,
	UpdateUser = 4,
	FindUser = 5,
	GoMainMenue = 6
};

enum enMainMenuePermission
{
	eAll = -1,
	pListClients = 1,
	pAddNewClient = 2,
	pDeleteClient = 4,
	pUpdatClient = 8,
	pFinCliet = 16,
	pTransaction = 32,
	pManageUser = 64
};

struct stClient
{
	string Name;
	string AccountNumber;
	string Phone;
	string PinCode;
	double AccountBalance;
	bool MarkForDelete = false;
};

struct stUser
{
	string UserName;
	short Password;
	short Permission ;
	bool MarkForDelete = false;

};

stUser CurrentUser;

string ReadStringForAccountNumber()
{
	string AccountNumber;
	cout << "enter AccountNumber ? ";
	cin >> AccountNumber;
	return AccountNumber;
}

string RaedStringForUserName()
{
	string UserName;
	cout << "enter User Name?\n";
	cin >> UserName;
	return UserName;
}

int ReadNumber(string Massege)
{
	int Number;
	cout << endl << Massege << endl;
	cin >> Number;
	return Number;
}

stClient ReadNewClient()
{
	stClient Client;
	cout << "enter name? ";
	getline(cin >> ws, Client.Name);
	cout << "enter AcountNumber? ";
	getline(cin, Client.AccountNumber);
	cout << "enter phone? ";
	getline(cin, Client.Phone);
	cout << "enter pincode? ";
	getline(cin, Client.PinCode);
	cout << "enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

short ReadClientServent(string massege)
{
	short Servent = 0;
	cout << massege;
	cin >> Servent;
	return Servent;
}

vector<string> SplitString(string S1, string Delim)
{
	vector <string> vString;

	short pos = 0;

	string sword;

	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sword = S1.substr(0, pos);
		if (sword != "")
		{
			vString.push_back(sword);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}

stClient ConverLinToRecord(string Line, string Speretor = "#//#")
{
	stClient Client;
	vector <string>vClientData;
	vClientData = SplitString(Line, Speretor);
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;

}

stUser ConverLinToRecordUser(string Line, string Speretor = "#//#")
{
	stUser User;
	vector <string>vUserData;
	vUserData = SplitString(Line, Speretor);
	User.UserName = vUserData[0];
	User.Password = stoi(vUserData[1]);

	return User;
}

void PrintClientsRecord(stClient Client)
{
	cout << "\n| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintUsersFirstRecord(stUser User)
{
	cout << "\n| " << setw(20) << left << User.UserName;
	cout << "| " << setw(20) << left << User.Password;
	cout << "| " << setw(20) << left << User.Permission;
}

void PrintAllClientsData(vector <stClient>& vClient)
{
	cout << "\n\t\t\t\t\tClient list (" << vClient.size() << ") Client(s).";
	cout << "\n_____________________________________________________________________________________________";
	cout << "____________________\n\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "pin code";
	cout << "| " << left << setw(40) << "client name";
	cout << "| " << left << setw(12) << "phone";
	cout << "| " << left << setw(12) << "Account balance";
	cout << "\n_____________________________________________________________________________________________";
	cout << "____________________\n\n";
	if (vClient.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (stClient& Client : vClient)
		{
			PrintClientsRecord(Client);
			cout << endl;
		}
	cout << "\n_____________________________________________________________________________________________";
	cout << "____________________\n\n";
}

void PrintAllUsersData(vector <stUser>& vUser)
{
	cout << "\n\t\t\t\t\tClient list (" << vUser.size() << ") Client(s).";
	cout << "\n_____________________________________________________________________________________________";
	cout << "____________________\n\n";
	cout << "| " << left << setw(15) << "Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permission";
	cout << "\n_____________________________________________________________________________________________";
	cout << "____________________\n\n";
	if (vUser.size() == 0)
		cout << "\t\t\t\tNo Users Available In the System!";
	else
		for (stUser& User : vUser)
		{
			PrintUsersFirstRecord(User);
			cout << endl;
		}
	cout << "\n_____________________________________________________________________________________________";
	cout << "____________________\n\n";
}

string ConverRecordToLine(stClient Client, string Speretor = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Speretor;
	stClientRecord += Client.PinCode + Speretor;
	stClientRecord += Client.Name + Speretor;
	stClientRecord += Client.Phone + Speretor;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

string ConverRecordToLine(stUser User, string Speretor = "#//#")
{
	string stClientRecord = "";
	stClientRecord += User.UserName + Speretor;
	stClientRecord += to_string(User.Password) + Speretor;
	stClientRecord += to_string(User.Permission) + Speretor;

	return stClientRecord;
}

vector<stClient>LoadClientDataFromFileToVectro(string FileName)
{
	vector <stClient>vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		stClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConverLinToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

vector<stUser>LoadUserDataFromFileToVectro(string FileName)
{
	vector <stUser>vUser;
	fstream UserFile;
	UserFile.open(FileName, ios::in);
	if (UserFile.is_open())
	{
		string Line;
		stUser User;
		while (getline(UserFile, Line))
		{
			User = ConverLinToRecordUser(Line);
			vUser.push_back(User);
		}
		UserFile.close();
	}
	return vUser;
}

bool FindUsersDataFromFile(stClient& Client, string AccountNumber, vector <stClient>& vClients)
{

	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool FindUsersDataFromFile(stUser& User, string UserName, vector <stUser>& vUser)
{

	for (stUser& C : vUser)
	{
		if (C.UserName == UserName)
		{
			User = C;
			return true;
		}
	}
	return false;
}

stClient ChangeClientRecord(string AccountNumber)
{
	stClient Client;
	cout << "enter name? ";
	getline(cin >> ws, Client.Name);
	Client.AccountNumber = AccountNumber;
	cout << "enter phone? ";
	getline(cin, Client.Phone);
	cout << "enter pincode? ";
	getline(cin, Client.PinCode);
	cout << "enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

stUser ChangeUserRecord(string UserName)
{
	stUser User;

	User.UserName = UserName;
	cout << "enter your Passorwd\n";
	cin >> User.Password;
	return User;
}

void AddDataLineToFile(string FileName, string sDataLine)
{
	fstream newFile;
	newFile.open(FileName, ios::out | ios::app);
	if (newFile.is_open())
	{
		newFile << sDataLine << endl;
		newFile.close();
	}
}

int ReadPermiisionToSet()
{
	int Permission = 0;
	char Answer = 'n';
	cout << "\nDo you want to give full acess ? y/n\n";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		return -1;
	}
	cout << "\nDo you want to give access to : \n";
	cout << "\nShow Client Listy/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		Permission += enMainMenuePermission::pListClients;
	}
	cout << "\nAdd New Client Listy/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		Permission += enMainMenuePermission::pAddNewClient;
	}
	cout << "\n Delete Client Listy/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		Permission += enMainMenuePermission::pDeleteClient;
	}
	cout << "\nUpdate Client Listy/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		Permission += enMainMenuePermission::pUpdatClient;
	}
	cout << "\nFind Client Listy/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		Permission += enMainMenuePermission::pFinCliet;
	}
	cout << "\nTransaction Client Listy/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		Permission += enMainMenuePermission::pTransaction;
	}
	cout << "\nManage User Client Listy/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		Permission += enMainMenuePermission::pManageUser;
	}
	return Permission;
}

stUser ReadNewUser()
{
	vector <stUser>vUser = LoadUserDataFromFileToVectro(UserFileName);
	stUser User;
	cout << "enter Name\n";
	getline(cin >> ws, User.UserName);
	while (FindUsersDataFromFile(User, User.UserName, vUser))
	{
		cout << "Client With [" <<User.UserName << "] Aleardy exists , enter another User Name ? ";
		getline(cin >> ws,User.UserName);
	}
	cout << "enter Password\n";
	cin >> User.Password;
	User.Permission = ReadPermiisionToSet();
	return User;
}

void AddNewClient()
{
	vector <stClient>vClient = LoadClientDataFromFileToVectro(ClientFileName);
	stClient Client;
	string AccountNumber = ReadStringForAccountNumber();
	while (FindUsersDataFromFile(Client, AccountNumber, vClient))
	{
		cout << "Client With [" << AccountNumber << "] Aleardy exists , enter another Account Number? ";
		getline(cin >> ws, AccountNumber);
	}
	Client = ChangeClientRecord(AccountNumber);
	AddDataLineToFile(ClientFileName, ConverRecordToLine(Client));
}

void AddNewUser()
{
	vector <stUser>vUser = LoadUserDataFromFileToVectro(UserFileName);
	stUser User = ReadNewUser();
	AddDataLineToFile(UserFileName, ConverRecordToLine(User));
}

void AddClients()
{
	char ReadMore = 'y';
	do
	{
		system("cls");
		AddNewClient();
		cout << "\nclient added successfuly,do you want to add more? ";
		cin >> ReadMore;
	} while (tolower(ReadMore) == 'y');
}

void AddUser()
{
	char ReadMore = 'y';
	do
	{
		system("cls");
		AddNewUser();
		cout << "\nUser added successfuly,do you want to add more? ";
		cin >> ReadMore;
	} while (tolower(ReadMore) == 'y');
}

void PrintClientRecord(stClient Client)
{
	cout << "Account number    : " << Client.AccountNumber << endl;
	cout << "pin cod           : " << Client.PinCode << endl;
	cout << "Name              : " << Client.Name << endl;
	cout << "phone             : " << Client.Phone << endl;
	cout << "Account Balance   : " << Client.AccountBalance << endl;
}

void ShowUserRecord(stUser User)
{
	cout << "User Name         : " << User.UserName << endl;
	cout << "Password          : " << User.Password << endl;
	cout << "Permission        : " << User.Permission << endl;
}

bool FindUsersDataFromFile(stClient& Client, string AccountNumber)
{
	vector <stClient>vClients = LoadClientDataFromFileToVectro(ClientFileName);
	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool FindUsersDataFromFile(stUser& User, string UserName)
{
	vector <stUser>vUsers = LoadUserDataFromFileToVectro(UserFileName);
	for (stUser& C : vUsers)
	{
		if (C.UserName == UserName)
		{
			User = C;
			return true;
		}
	}
	return false;
}

bool FindUserByUserNameAndPassword(stUser& User, string UserName, short Password)
{
	vector <stUser>vUsers = LoadUserDataFromFileToVectro(UserFileName);
	for (stUser& C : vUsers)
	{
		if (C.UserName == UserName && C.Password == Password)
		{
			User = C;
			return true;
		}
	}
	return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

bool MarkUserForDeleteByAccountNumber(string UserName, vector <stUser>& vUser)
{
	for (stUser& C : vUser)
	{
		if (C.UserName == UserName)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector <stClient>SaveClientDataToFile(string FileName, vector <stClient>vClients)
{
	fstream MyFile;
	string DeleteLine;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		for (stClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DeleteLine = ConverRecordToLine(C);
				MyFile << DeleteLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

vector <stUser>SaveUserDataToFile(string FileName, vector <stUser>vUser)
{
	fstream MyFile;
	string DeleteLine;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		for (stUser C : vUser)
		{
			if (C.MarkForDelete == false)
			{
				DeleteLine = ConverRecordToLine(C);
				MyFile << DeleteLine << endl;
			}
		}
		MyFile.close();
	}
	return vUser;
}

void DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'n';
	if (FindUsersDataFromFile(Client, AccountNumber, vClients))
	{
		PrintClientRecord(Client);
		cout << "\n\nAreyou sure you want delete this client ? y/n";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientDataToFile(ClientFileName, vClients);
			vClients = LoadClientDataFromFileToVectro(ClientFileName);
			cout << "\n\nClient deleted successfuly.\n";

		}

	}
	else
	{
		cout << "\nclient with account number <" << AccountNumber << ") is not founded!";

	}
}

void DeleteUserByAccountNumber(string UserName, vector <stUser>& vUser)
{
	stUser User;
	char Answer = 'n';
	if (FindUsersDataFromFile(User, UserName, vUser))
	{
		ShowUserRecord(User);
		cout << "\n\nAreyou sure you want delete this client ? y/n";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			MarkUserForDeleteByAccountNumber(UserName, vUser);
			SaveUserDataToFile(UserFileName, vUser);
			vUser = LoadUserDataFromFileToVectro(UserFileName);
			cout << "\n\nClient deleted successfuly.\n";

		}

	}
	else
	{
		cout << "\nclient with account number <" << UserName << ") is not founded!";

	}
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'n';
	if (FindUsersDataFromFile(Client, AccountNumber, vClients))
	{
		PrintClientRecord(Client);
		cout << "\n\nAre you sure you want  update this client ? y/n";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{

			for (stClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveClientDataToFile(ClientFileName, vClients);
			cout << "\n\nClient update successfuly.";
			return true;
		}
	}
	else
	{
		cout << "\nclient with account number (" << AccountNumber << ") is not founded!";
		return false;
	}
	return false;
}

bool UpdateUserByAccountNumber(string UserName, vector <stUser>& vUser)
{
	stUser User;
	char Answer = 'n';
	if (FindUsersDataFromFile(User, UserName, vUser))
	{
		ShowUserRecord(User);
		cout << "\n\nAre you sure you want  update this client ? y/n";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{

			for (stUser& C : vUser)
			{
				if (C.UserName == UserName)
				{
					C = ChangeUserRecord(UserName);
					break;
				}
			}

			SaveUserDataToFile(UserFileName, vUser);
			cout << "\n\nClient update successfuly.";
			return true;
		}
	}
	else
	{
		cout << "\nclient with account number (" << UserName << ") is not founded!";
		return false;
	}
	return false;
}

bool CheckAcessPermission(enMainMenuePermission Permission)
{
	if (CurrentUser.Permission == enMainMenuePermission::eAll)
		return true;

	if ((Permission & CurrentUser.Permission) == Permission)
		return true;
	else
		return false;
}

void ShowAcessDeniedMassege()
{
	cout << "\n---------------------------------------\n";
	cout << "Acess Denied ,\n you dont Have Permission to do this\n please contact with your admin!\n";
	cout << "\n---------------------------------------\n";
}

void ScreenOfShowClinetList()
{
	if (!CheckAcessPermission(enMainMenuePermission::pListClients))
	{
		ShowAcessDeniedMassege();
		return;
	}
	cout << "-------------------------------------------------------------\n";
	cout << "\t" << "Show clients inf screen\n";
	cout << "-------------------------------------------------------------\n\n";
	vector <stClient> Client = LoadClientDataFromFileToVectro(ClientFileName);
	PrintAllClientsData(Client);
}

void ScreenOfShowUserList()
{
	cout << "-------------------------------------------------------------\n";
	cout << "\t" << "Show clients inf screen\n";
	cout << "-------------------------------------------------------------\n\n";
	vector <stUser> User = LoadUserDataFromFileToVectro(UserFileName);
	PrintAllUsersData(User);
}

void ScreenOfAddNewClient()
{
	if (!CheckAcessPermission(enMainMenuePermission::pAddNewClient))
	{
		ShowAcessDeniedMassege();
		return;
	}
	cout << "-------------------------------------------------------------\n";
	cout << "\t" << "Add new client screen\n";
	cout << "-------------------------------------------------------------\n\n";
	AddClients();
}

void ScreenOfAddNewUser()
{
	cout << "-------------------------------------------------------------\n";
	cout << "\t" << "Add new client screen\n";
	cout << "-------------------------------------------------------------\n\n";
	AddUser();
}

void ScreenOfDeleteClient()
{
	if (!CheckAcessPermission(enMainMenuePermission::pDeleteClient))
	{
		ShowAcessDeniedMassege();
		return;
	}
	cout << "-------------------------------------------------------------\n";
	cout << "\t" << "Delete client screen\n";
	cout << "-------------------------------------------------------------\n\n";
	vector<stClient>vClient = LoadClientDataFromFileToVectro(ClientFileName);
	string AccountNumber = ReadStringForAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClient);
}

void ScreenOfDeleteUser()
{
	cout << "-------------------------------------------------------------\n";
	cout << "\t" << "Delete client screen\n";
	cout << "-------------------------------------------------------------\n\n";
	vector<stUser>vUser = LoadUserDataFromFileToVectro(UserFileName);
	string UserName = RaedStringForUserName();
	DeleteUserByAccountNumber(UserName, vUser);
}

void ScreenOfUpdateClientInfo()
{
	if (!CheckAcessPermission(enMainMenuePermission::pUpdatClient))
	{
		ShowAcessDeniedMassege();
		return;
	}
	cout << "-------------------------------------------------------------\n";
	cout << "\t" << "Update client inf screen\n";
	cout << "-------------------------------------------------------------\n\n";
	vector<stClient>vClient = LoadClientDataFromFileToVectro(ClientFileName);
	string AccountNumber = ReadStringForAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClient);
}

void ScreenOfUpdateUserInfo()
{
	cout << "-------------------------------------------------------------\n";
	cout << "\t" << "Update client inf screen\n";
	cout << "-------------------------------------------------------------\n\n";
	vector<stUser>vUser = LoadUserDataFromFileToVectro(UserFileName);
	string UserName = RaedStringForUserName();
	UpdateUserByAccountNumber(UserName, vUser);
}

void ScreenOfFindClient()
{
	if (!CheckAcessPermission(enMainMenuePermission::pFinCliet))
	{
		ShowAcessDeniedMassege();
		return;
	}
	cout << "-------------------------------------------------------------\n";
	cout << "\t" << "find client inf screen\n";
	cout << "-------------------------------------------------------------\n\n";
	stClient Client;
	string AccountNumber = ReadStringForAccountNumber();

	if (FindUsersDataFromFile(Client, AccountNumber))
	{
		PrintClientRecord(Client);
	}
	else
	{
		cout << "Client with Account Number (" << AccountNumber << ")not founded\n";
	}
}

void ScreenOfFindUser()
{
	cout << "-------------------------------------------------------------\n";
	cout << "\t" << "find User inf screen\n";
	cout << "-------------------------------------------------------------\n\n";
	stUser User;
	string UserName = RaedStringForUserName();
	if (FindUsersDataFromFile(User, UserName))
	{
		ShowUserRecord(User);
	}
	else
	{
		cout << "Client with Account Number (" << UserName << ")not founded\n";
	}
}

bool DoTransaction()
{
	char DoIt = 'y';
	cout << "\nAre you sure want perform this Transaction? y/n ? ";
	cin >> DoIt;
	return (tolower(DoIt) == 'y') ? true : false;
}

void ScreenOfDeposit()
{

	cout << "-------------------------------------------------------------\n";
	cout << "\t" << "Deposit screen\n";
	cout << "-------------------------------------------------------------\n\n";
	vector<stClient>vClient = LoadClientDataFromFileToVectro(ClientFileName);
	stClient Client;
	string AccountNumber = ReadStringForAccountNumber();
	int DepositAmount;
	while (!FindUsersDataFromFile(Client, AccountNumber, vClient))
	{
		cout << "Client with Account Number (" << AccountNumber << ")not founded\n";
		AccountNumber = ReadStringForAccountNumber();
	}
	PrintClientRecord(Client);
	DepositAmount = ReadNumber("Please enter deposit amount?");
	if (DoTransaction())
	{
		for (stClient& C : vClient)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += DepositAmount;
				cout << "Add successfuly " << C.AccountBalance << endl;
				break;
			}
		}

		SaveClientDataToFile(ClientFileName, vClient);
	}


}

void ScreenOfWithdrew()
{

	cout << "-------------------------------------------------------------\n";
	cout << "\t" << "Withdraw screen\n";
	cout << "-------------------------------------------------------------\n\n";
	vector<stClient>vClient = LoadClientDataFromFileToVectro(ClientFileName);
	stClient Client;
	string AccountNumber = ReadStringForAccountNumber();
	int WithdrawAmount;
	while (!FindUsersDataFromFile(Client, AccountNumber, vClient))
	{
		cout << "Client with Account Number (" << AccountNumber << ")not founded\n";
		AccountNumber = ReadStringForAccountNumber();
	}
	PrintClientRecord(Client);
	WithdrawAmount = ReadNumber("Please enter deposit amount?");
	while (Client.AccountBalance < WithdrawAmount)
	{
		cout << "Amount Exceeds the balance , you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "Please enter deposit amount? ";
		cin >> WithdrawAmount;
	}
	if (DoTransaction())
	{
		for (stClient& C : vClient)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance -= WithdrawAmount;
				break;
			}
		}
		SaveClientDataToFile(ClientFileName, vClient);
		cout << "Withdraw successfuly ";
	}

}

void PrintBalanceFormat(stClient Client)
{
	cout << "\n| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ScreenOfTotalBalance()
{
	vector <stClient> Client = LoadClientDataFromFileToVectro(ClientFileName);
	int TotalBalance = 0;
	cout << "\n\t\t\t\t\tBalance list (" << Client.size() << ") Client(s).";
	cout << "\n_____________________________________________________________________________________________";
	cout << "____________________\n\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "client name";
	cout << "| " << left << setw(12) << "Account balance";
	cout << "\n_____________________________________________________________________________________________";
	cout << "____________________\n\n";
	if (Client.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
	{
		for (stClient& Client : Client)
		{
			PrintBalanceFormat(Client);
			cout << endl;
			TotalBalance += Client.AccountBalance;
		}
	}
	cout << "\n_____________________________________________________________________________________________";
	cout << "____________________\n\n";
	cout << "\t\t\t\t\ttotal Balances = " << TotalBalance << endl;
}

void ClearScreen()
{
	system("cls");
}

void PerformTransaction(enTrnasaction Transaction)
{
	switch (Transaction)
	{
	case enTrnasaction::Deposit:
	{
		ClearScreen();
		ScreenOfDeposit();
		GoBackToTransactionMenue();
		break;
	}
	case enTrnasaction::withdraw:
	{
		ClearScreen();
		ScreenOfWithdrew();
		GoBackToTransactionMenue();
		break;
	}
	case enTrnasaction::TotalBalance:
	{
		ClearScreen();
		ScreenOfTotalBalance();
		GoBackToTransactionMenue();
		break;
	}
	case enTrnasaction::MainMenue:
	{
		ClearScreen();
		MainMenueScreen();
		break;
	}
	}
}

void PerformManageUsers(enManageUser ManageUser)
{
	switch (ManageUser)
	{
	case enManageUser::ShowListOfUser:
	{
		ClearScreen();
		ScreenOfShowUserList();
		GoBackToManageUserMenue();
		break;
	}
	case enManageUser::AddNewUsers:
	{
		ClearScreen();
		ScreenOfAddNewUser();
		GoBackToManageUserMenue();
		break;
	}
	case enManageUser::DeleteUser:
	{
		ClearScreen();
		ScreenOfDeleteUser();
		GoBackToManageUserMenue();
		break;
	}
	case enManageUser::UpdateUser:
	{
		ClearScreen();
		ScreenOfUpdateUserInfo();
		GoBackToManageUserMenue();
		break;
	}
	case enManageUser::FindUser:
	{
		ClearScreen();
		ScreenOfFindUser();
		GoBackToManageUserMenue();
		break;
	}
	case enManageUser::GoMainMenue:
	{
		ClearScreen();
		MainMenueScreen();
		break;
	}
	}
}

void TransactionMenueScreen()
{
	if (!CheckAcessPermission(enMainMenuePermission::pTransaction))
	{
		ShowAcessDeniedMassege();
		void GoBackToMenue();
		return;
	}
	cout << "===================================================================================\n";
	cout << "	" << "Transaction Menue Screen\n";
	cout << "===================================================================================\n";
	cout << "	" << "[1] Deposit.\n";
	cout << "	" << "[2] Withdraw.\n";
	cout << "	" << "[3] Total Balance.\n";
	cout << "	" << "[4] Main Menue.\n";
	cout << "===================================================================================\n";
	enTrnasaction Transaction = (enTrnasaction)ReadClientServent("Choose what do you want to do ? [1 to 4]? ");
	PerformTransaction(Transaction);
}

void ManageUsersMenueScreen()
{
	if (!CheckAcessPermission(enMainMenuePermission::pManageUser))
	{
		ShowAcessDeniedMassege();
		GoBackToMenue();
		return;
	}
	cout << "===================================================================================\n";
	cout << "	" << "Manage Usres Menue Screen\n";
	cout << "===================================================================================\n";
	cout << "	" << "[1] List Users.\n";
	cout << "	" << "[2] Add New User.\n";
	cout << "	" << "[3] Delete User.\n";
	cout << "	" << "[4] Update User.\n";
	cout << "	" << "[5] Find User.\n";
	cout << "	" << "[6] Main Menue.\n";
	cout << "===================================================================================\n";
	enManageUser ManageUser = (enManageUser)ReadClientServent("Choose what do you want to do ? [1 to 6]?");
	PerformManageUsers(ManageUser);

}

void GoBackToTransactionMenue()
{
	cout << "\n\npress any kay to go back to main menue...";
	system("pause>0");
	ClearScreen();
	TransactionMenueScreen();
}

void GoBackToManageUserMenue()
{
	cout << "\n\npress any kay to go back to main menue...";
	system("pause>0");
	ClearScreen();
	ManageUsersMenueScreen();
}

void ScreenOfLoguot()
{
	cout << "-----------------------------------------------------------------------------------------------------------\n";
	cout << "\t" << "end of program!\n";
	cout << "-----------------------------------------------------------------------------------------------------------\n";
}

void GoBackToMenue()
{
	cout << "\n\npress any kay to go back to main menue...";
	system("pause>0");
	ClearScreen();
	MainMenueScreen();
}

void PerformMainMenueOption(enClientServent ClientServent)
{
	switch (ClientServent)
	{
	case enClientServent::Add:
	{
		ClearScreen();
		ScreenOfAddNewClient();
		GoBackToMenue();
		break;
	}
	case enClientServent::Delete:
	{
		ClearScreen();
		ScreenOfDeleteClient();
		GoBackToMenue();
		break;
	}
	case enClientServent::Update:
	{
		ClearScreen();
		ScreenOfUpdateClientInfo();
		GoBackToMenue;
		break;
	}
	case enClientServent::Show:
	{
		ClearScreen();
		ScreenOfShowClinetList();
		GoBackToMenue();
		break;
	}
	case enClientServent::Find:
	{
		ClearScreen();
		ScreenOfFindClient();
		GoBackToMenue();
		break;
	}
	case enClientServent::Transaction:
	{
		ClearScreen();
		TransactionMenueScreen();
		break;
	}
	case enClientServent::ManageUser:
	{
		ClearScreen();
		ManageUsersMenueScreen();
	}
	case enClientServent::Loguot:
	{
		ClearScreen();
		/*ScreenOfLoguot();*/
		Login();
		break;
	}

	}
}

void MainMenueScreen()
{
	cout << "===================================================================================\n";
	cout << "	" << "Main Menue Screen\n";
	cout << "===================================================================================\n";
	cout << "	" << "[1] Show Client List.\n";
	cout << "	" << "[2] Add New Client.\n";
	cout << "	" << "[3] Delete Client.\n";
	cout << "	" << "[4] Update Client Info.\n";
	cout << "	" << "[5] Find Client.\n";
	cout << "	" << "[6] Transaction\n";
	cout << "	" << "[7] Manage Usersn\n";
	cout << "	" << "[8] Logut.\n";
	cout << "===================================================================================\n";
	enClientServent ClientServent = (enClientServent)ReadClientServent("Choose what do you want to do ? [1 to 8]? ");
	PerformMainMenueOption(ClientServent);
}

void LoginScreen()
{
	cout << "\n--------------------------------------------------------------------------------------\n";
	cout << "				Login Screen \n";
	cout << "\n--------------------------------------------------------------------------------------\n";

}

void Login()
{
	LoginScreen();
	string UserName = RaedStringForUserName();
	short Password = ReadNumber("enter Password!");
	while (!FindUserByUserNameAndPassword(CurrentUser, UserName, Password))
	{
		ClearScreen();
		LoginScreen();
		cout << "Invliad UserName / Password!\n";
		UserName = RaedStringForUserName();
		Password = ReadNumber("enter Password!");
	}
	ClearScreen();
	MainMenueScreen();
}

int main()
{
	Login();
	return 0;
}
