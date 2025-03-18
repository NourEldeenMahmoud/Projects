#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>
using namespace std;
struct stClientData
{
	string AccountNumber = "1";
	string PinCode;
	string Name = "unkown";
	string Phone = "012345678";
	int AccountBalance = 0000000;
	bool MarkForDelete = false;
};

struct stUserData
{
	string UserName = " ";
	string Passsword = " ";
	int Premission = 0;
	bool MarkForDelete = false;
};

stUserData CurrentUser;

const string ClientsFileName = "Bank Clients.txt";

const string UsersFileName = "Users.txt";

enum enMainMenuOptions { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Transactions = 6,ManageUsers=7 ,Logout=8}; 

enum enTransactionOptions{Deposit=1,Withdraw=2,TotalBalance=3,MainMenu =4};

enum enManageUserOptions { ListUser = 1, AddUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, MainMenuUser = 6};

enum enUserPermissions { All=-1,ShowPermission = 1, AddPermission = 2, DeletePermission = 4, UpdatePermission = 8, FindPermission = 16, TransactionsPermission = 32, ManageUsersPermission = 64 };

void ShowMainMenu();
void ShowTransactionScreen();
void ShowManageUsersScreen();
void ShowLoginScren();
void ShowAccessDeniedMassage();
bool CheckAccessPermission(enUserPermissions Permission);

void BackToMenu()
{
	cout << "\n\nPress Any Key To Go Back ... ";
	system("pause>0");
	ShowMainMenu();
}
void BackToTransctionsMenu()
{
	cout << "\n\nPress Any Key To Go Back ... ";
	system("pause>0");
	ShowTransactionScreen();
}
void BackToManageUsersScreen()
{
	cout << "\n\nPress Any Key To Go Back ... ";
	system("pause>0");
	ShowManageUsersScreen();
}



short ReadMenuOptions()
{
	short Option;
	cout << "\nChoose What Do You Want To Do : [1 - 8]\n";
	cin >> Option;
	return Option;
}
short ReadTransactionMenuOptions()
{
	short Option;
	cout << "\nChoose What Do You Want To Do : [1 - 4]\n";
	cin >> Option;
	return Option;
}
short ReadUserOptions()
{
	short Option;
	cout << "\nChoose What Do You Want To Do : [1 - 6]\n";
	cin >> Option;
	return Option;
}

string ReadAccountNumber()
{
	string AccountNumber;
	cout << "Enter Account Number\n";
	cin >> AccountNumber;
	return AccountNumber;
}
string ReadUserName()
{
	string UserName;
	cout << "Enter UserName\n";
	cin >> UserName;
	return UserName;
}
string ReadPassword()
{
	string Password;
	cout << "Enter Password\n";
	cin >> Password;
	return Password;
}

string ConvertRecordToLine(stClientData ClientData, string sep = "/##/")
{
	string Line;
	Line += ClientData.AccountNumber + sep;
	Line += ClientData.PinCode + sep;
	Line += ClientData.Name + sep;
	Line += ClientData.Phone + sep;
	Line += to_string(ClientData.AccountBalance) + sep;
	return Line;
}
string ConvertUserRecordToLine(stUserData User, string sep = "/##/")
{
	string Line;
	Line += User.UserName + sep;
	Line += User.Passsword + sep;
	Line += to_string(User.Premission) + sep;
	return Line;
}

vector<string> SplitStrings(string StringToSplit, string Delm = " ")
{
	vector<string> vString;
	short pos = 0;
	string sWord;
	while (((pos = StringToSplit.find(Delm)) != std::string::npos))
	{
		sWord = StringToSplit.substr(0, pos);
		if (sWord != " ")
		{
			vString.push_back(sWord);
		}
		StringToSplit.erase(0, pos + Delm.length());
	}
	if (StringToSplit != " ")
		vString.push_back(StringToSplit);
	return vString;
}

stClientData ConvertLineToRecord(string Line, string Sep = "/##/")
{
	stClientData ClientData;
	vector<string> vClient = SplitStrings(Line, Sep);
	ClientData.AccountNumber = vClient[0];
	ClientData.PinCode = vClient[1];
	ClientData.Name = vClient[2];
	ClientData.Phone = vClient[3];
	ClientData.AccountBalance = stod(vClient[4]);
	return ClientData;
}
stUserData ConvertUserLineToRecord(string Line, string Sep = "/##/")
{
	stUserData User;
	vector<string> vUser = SplitStrings(Line, Sep);
	User.UserName = vUser[0];
	User.Passsword = vUser[1];
	User.Premission = stoi(vUser[2]);
	
	return User;
}

void PrintClientsData(stClientData Clients)
{
	cout << "| " << left << setw(20) << Clients.AccountNumber;
	cout << "| " << left << setw(15) << Clients.PinCode;
	cout << "| " << left << setw(40) << Clients.Name;
	cout << "| " << left << setw(11) << Clients.Phone;
	cout << "| " << left << setw(15) << Clients.AccountBalance << endl;
}
void PrintUserData(stUserData User)
{
	cout << "| " << left << setw(20) << User.UserName;
	cout << "| " << left << setw(15) << User.Passsword;
	cout << "| " << left << setw(15) << User.Premission;
}
void PrintTotalBalances(stClientData Clients)
{
	cout << "| " << left << setw(20) << Clients.AccountNumber;
	cout << "| " << left << setw(40) << Clients.Name;
	cout << "| " << left << setw(15) << Clients.AccountBalance << endl;
}

vector <stClientData> SaveClientsDataToFile(string FileName, vector <stClientData> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (stClientData C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}
vector <stUserData> SaveUsersDataToFile(string UsersFileName, vector <stUserData> vUsers)
{
	fstream UsersFile;
	UsersFile.open(UsersFileName, ios::out);
	string DataLine;
	if (UsersFile.is_open())
	{
		for (stUserData U : vUsers)
		{
			if (U.MarkForDelete == false)
			{
				DataLine = ConvertUserRecordToLine(U);
				UsersFile << DataLine << endl;
			}
		}
		UsersFile.close();
	}
	return vUsers;
}

vector<stClientData> LoadDataFromFile(string FileName)
{
	fstream ClientsFile;
	vector <stClientData> vClient;
	ClientsFile.open(FileName, ios::in);
	if (ClientsFile.is_open())
	{
		string Line;
		stClientData Client;
		while (getline(ClientsFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClient.push_back(Client);
		}
		ClientsFile.close();
	}
	return vClient;
}
vector<stUserData> LoadDataFromUsersFile(string UsersFileName)
{
	fstream UsersFile;
	vector <stUserData> vUsers;
	UsersFile.open(UsersFileName, ios::in);
	if (UsersFile.is_open())
	{
		string Line;
		stUserData User;
		while (getline(UsersFile, Line))
		{
			User = ConvertUserLineToRecord(Line);
			vUsers.push_back(User);
		}
		UsersFile.close();
	}
	return vUsers;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

	vector <stClientData> vClients;

	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open())
	{

		string Line;
		stClientData Client;

		while (getline(MyFile, Line))
		{

			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}


			vClients.push_back(Client);
		}

		MyFile.close();

	}

	return false;


}
bool UserExistsByUserName(string UserName, string UsersFileName)
{

	vector <stUserData> vUsers;

	fstream MyFile;
	MyFile.open(UsersFileName, ios::in);//read Mode

	if (MyFile.is_open())
	{

		string Line;
		stUserData User;

		while (getline(MyFile, Line))
		{

			User = ConvertUserLineToRecord(Line);
			if (User.UserName == UserName)
			{
				MyFile.close();
				return true;
			}


			vUsers.push_back(User);
		}

		MyFile.close();

	}

	return false;


}
void ShowClientsScreen()
{
	system("cls");
	if (!CheckAccessPermission (ShowPermission))
	{
		ShowAccessDeniedMassage();
		BackToMenu();
	}
	vector<stClientData> vClient = LoadDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\t Client List (" << vClient.size() << ")  Client(s). ";
	cout << "\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
	cout << "| " << left << setw(20) << "Account Number ";
	cout << "| " << left << setw(15) << "Pin Code ";
	cout << "| " << left << setw(40) << "Client Name ";
	cout << "| " << left << setw(11) << "Phone ";
	cout << "| " << left << setw(15) << "Account Balance ";
	cout << "\n\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
	for (stClientData Client : vClient)
	{
		PrintClientsData(Client);
	}
	cout << "\n\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
}
void ShowUsersScreen()
{
	system("cls");
	vector<stUserData> vUsers = LoadDataFromUsersFile(UsersFileName);
	cout << "\n\t\t\t\t\t Users List (" << vUsers.size() << ")  Client(s). ";
	cout << "\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
	cout << "| " << left << setw(20) << "User Name";
	cout << "| " << left << setw(15) << "Password";
	cout << "| " << left << setw(15) << "Premission";
	cout << "\n\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
	for (stUserData User : vUsers)
	{
		PrintUserData(User);
		cout << endl;
	}
	cout << "\n\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
}

void AddNewDataLine(string FileName, string Line)
{
	fstream File;
	File.open(FileName, ios::app | ios::out);
	if (File.is_open())
	{
		File << Line << endl;
		File.close();
	}
}

stClientData ReadNewClient()
{
	stClientData Client;

	cout << "Enter Account Number ? ";
	getline(cin >> ws, Client.AccountNumber);
	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode ? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;
	return Client;
}

int UserAccess()
{
	char access = ' ';
	int permission = 0;
	cout << "Do you want to give full access ? Y/N ? ";
	cin >> access;
	if ( toupper(access)=='Y')
		return permission = -1;
	else if (toupper(access) == 'N')
	{
		char access2=' ';
		cout << "\n Do you want to give access to : \n";
		cout << "\n Show Client List ? y/n ?  \n";
		cin >> access2;
		if (toupper(access2) == 'Y')
		{
			permission += 1;
		}
		cout << "\n Add New Client  ? y/n ?  \n";
		cin >> access2;
		if (toupper(access2) == 'Y')
		{
			permission += 2;
		}
		cout << "\n Delete Client ? y/n ?  \n";
		cin >> access2;
		if (toupper(access2) == 'Y')
		{
			permission += 4;
		}
		cout << "\n Update Client  ? y/n ?  \n";
		cin >> access2;
		if (toupper(access2) == 'Y')
		{
			permission += 8;
		}
		cout << "\n Find Client ? y/n ?  \n";
		cin >> access2;
		if (toupper(access2) == 'Y')
		{
			permission += 16;
		}
		cout << "\nTransactions ? y/n ?  \n";
		cin >> access2;
		if (toupper(access2) == 'Y')
		{
			permission += 32;
		}
		cout << "\n Manage Clients ? y/n ?  \n";
		cin >> access2;
		if (toupper(access2) == 'Y')
		{
			permission += 64;
		}
	}
	return permission;
}

stUserData ReadNewUser()
{
	stUserData User;
	cout << "Enter User Name ? ";
	getline(cin >> ws, User.UserName);
	while (UserExistsByUserName(User.UserName, UsersFileName))
	{
		cout << "\n User with [" << User.UserName << "] already exists, Enter another UserName? ";
		getline(cin >> ws, User.UserName);
	}
	cout << "Enter Password ? ";
	getline(cin, User.Passsword);
	User.Premission=UserAccess();
	return User;
}

void AddNewClient()
{
	stClientData Client = ReadNewClient();
	AddNewDataLine(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewUser()
{
	stUserData User = ReadNewUser();
	AddNewDataLine(UsersFileName, ConvertUserRecordToLine(User));
}

void AddNewClientScreen()
{
	if (!CheckAccessPermission(AddPermission))
	{
		ShowAccessDeniedMassage();
		BackToMenu();
	}
	char Addmore = 'Y';
	do
	{
		system("cls");
		cout << "---------------------------------------------------- \n";
		cout << "\t\tAdd New Client Screen \n";
		cout << "---------------------------------------------------- \n";
		cout << "\nAdding New Client : \n";
		AddNewClient();

		cout << "\nClient Added Successfully , do you want to add more clients ? ";
		cin >> Addmore;

	} while (toupper(Addmore) == 'Y');
}

void AddNewUserScreen()
{
	char Addmore = 'Y';
	do
	{
		system("cls");
		cout << "---------------------------------------------------- \n";
		cout << "\t\tAdd New User Screen \n";
		cout << "---------------------------------------------------- \n";
		cout << "\nAdding New User : \n";
		AddNewUser();

		cout << "\n User Added Successfully , do you want to add more Users ? ";
		cin >> Addmore;

	} while (toupper(Addmore) == 'Y');
}

void ShowCLientCard(stClientData Client)
{
	cout << "\nThe Following Is The Client Details : \n";
	cout << " \n----------------------------------------\n";
	cout << "Account Number  : " << Client.AccountNumber << endl;
	cout << "PinCode         : " << Client.PinCode << endl;
	cout << "Name            : " << Client.Name << endl;
	cout << "Phone           : " << Client.Phone << endl;
	cout << "Account Balance : " << Client.AccountBalance << endl;
	cout << " \n----------------------------------------\n";
}

void ShowUserCard(stUserData User)
{
	cout << "\nThe Following Is The User Details : \n";
	cout << " \n----------------------------------------\n";
	cout << "UserName        : " << User.UserName << endl;
	cout << "Passsword       : " << User.Passsword << endl;
	cout << "Premission      : " << User.Premission << endl;
	cout << " \n----------------------------------------\n";
}

bool FindCLientByAccountNumber(string AccountNumber, stClientData& Client, vector <stClientData> vClient)
{
	for (stClientData& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}


bool FindUserByUserName(string UserName, stUserData& User, vector <stUserData> vUser)
{
	for (stUserData& C : vUser)
	{
		if (C.UserName == UserName)
		{
			User = C;
			return true;
		}
	}
	return false;
}
bool FindUserByUserNameAndPassword(string UserName,string Password, stUserData& User, vector <stUserData> vUser)
{
	for (stUserData& U : vUser)
	{
		if (U.UserName == UserName && U.Passsword==Password)
		{
			User = U;
			return true;
		}
	}
	return false;
}
void FindClientScreen()
{
	system("cls");
	if (!CheckAccessPermission(FindPermission))
	{
		ShowAccessDeniedMassage();
		BackToMenu();
	}
	vector<stClientData> vClient = LoadDataFromFile(ClientsFileName);
	cout << "---------------------------------------------------- \n";
	cout << "\t\tFind Client Screen \n";
	cout << "---------------------------------------------------- \n";
	string AccountNumber = ReadAccountNumber();
	stClientData Client;
	if (FindCLientByAccountNumber(AccountNumber, Client, vClient))
		ShowCLientCard(Client);
	else
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
}

void FindUserScreen()
{
	system("cls");
	vector<stUserData> vUser = LoadDataFromUsersFile(UsersFileName);
	cout << "---------------------------------------------------- \n";
	cout << "\t\tFind User Screen \n";
	cout << "---------------------------------------------------- \n";
	string UserName = ReadUserName();
	stUserData User;
	if (FindUserByUserName(UserName, User, vUser))
		ShowUserCard(User);
	else
		cout << "\n User with the User Name (" << UserName << ") is Not Found!\n";
}

bool MarkForDelete(string AccountNumber, vector <stClientData> &vClient)
{
	for (stClientData &C : vClient)
	{
		if (AccountNumber == C.AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

bool MarkUserForDelete(string UserName, vector <stUserData>& vUser)
{
	for (stUserData& U : vUser)
	{
		if (UserName == U.UserName)
		{
			U.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
<
void DeleteClientScreen()
{

	system("cls");
	if (!CheckAccessPermission(DeletePermission))
	{
		ShowAccessDeniedMassage();
		BackToMenu();
	}
	cout << "---------------------------------------------------- \n";
	cout << "\t\tDelete Client Screen \n";
	cout << "---------------------------------------------------- \n";
	stClientData Client;
	vector<stClientData> vClient = LoadDataFromFile(ClientsFileName);
	char Delete = ' ';
	string AccountNumber = ReadAccountNumber();
	if (FindCLientByAccountNumber(AccountNumber, Client, vClient))
	{
		ShowCLientCard(Client);
		cout << "\n\nAre You Sure You Want To Delete is Client ? Y/N\n ";
		cin >> Delete;
		if (toupper(Delete) == 'Y')
		{
			MarkForDelete(AccountNumber, vClient);
			SaveClientsDataToFile(ClientsFileName, vClient);
			vClient = LoadDataFromFile(ClientsFileName);
			cout << "\nClient Is Deleted Successfully. ";


		}
	}
	else
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";

}

void DeleteUserScreen()
{

	system("cls");
	cout << "---------------------------------------------------- \n";
	cout << "\t\tDelete User Screen \n";
	cout << "---------------------------------------------------- \n";
	stUserData User;
	vector<stUserData> vUser = LoadDataFromUsersFile(UsersFileName);
	char Delete = ' ';
	string UserName = ReadUserName();
	if (FindUserByUserName(UserName, User, vUser))
	{
		ShowUserCard(User);
		cout << "\n\nAre You Sure You Want To Delete is User ? Y/N\n ";
		cin >> Delete;
		if (toupper(Delete) == 'Y')
		{
			MarkUserForDelete(UserName, vUser);
			SaveUsersDataToFile(UsersFileName, vUser);
			vUser = LoadDataFromUsersFile(UsersFileName);
			cout << "\n User Is Deleted Successfully. ";


		}
	}
	else
		cout << "\n User with The User Name (" << UserName << ") is Not Found!\n";

}

stClientData ChangeClientRecord(string AccountNumber)
{
	stClientData Client;

	Client.AccountNumber = AccountNumber;
	cout << "Enter PinCode ? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;
	return Client;
}

stUserData ChangeUserRecord(string UserName)
{
	stUserData User;

	User.UserName = UserName;
	cout << "Enter Password ? ";
	getline(cin >> ws, User.Passsword);
	User.Premission = UserAccess();
	return User;
}

bool UpadateClientScreen()
{
	system("cls");
	if (!CheckAccessPermission(UpdatePermission))
	{
		ShowAccessDeniedMassage();
		BackToMenu();
	}
	cout << "---------------------------------------------------- \n";
	cout << "\t\tUpdate Client Screen \n";
	cout << "---------------------------------------------------- \n";
	vector<stClientData> vClient = LoadDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	char Update = ' ';
	stClientData Client;
	if (FindCLientByAccountNumber(AccountNumber, Client, vClient))
	{
		ShowCLientCard(Client);

		cout << "\n\nAre You Sure You Want To Update this Client ? Y/N \n";
		cin >> Update;
		if (toupper(Update) == 'Y')
		{
			for (stClientData& C : vClient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveClientsDataToFile(ClientsFileName, vClient);
			cout << "\nClient Is Updated Successfully. ";
			return true;
		}

	}
	else
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
	return false;
}

bool UpadateUserScreen()
{
	system("cls");
	cout << "---------------------------------------------------- \n";
	cout << "\t\tUpdate User Screen \n";
	cout << "---------------------------------------------------- \n";
	vector<stUserData> vUser = LoadDataFromUsersFile(UsersFileName);
	string UserName = ReadUserName();
	char Update = ' ';
	stUserData User;
	if (FindUserByUserName(UserName, User, vUser))
	{
		ShowUserCard(User);

		cout << "\n\nAre You Sure You Want To Update this User ? Y/N \n";
		cin >> Update;
		if (toupper(Update) == 'Y')
		{
			for (stUserData& U : vUser)
			{
				if (U.UserName == UserName)
				{
					U = ChangeUserRecord(UserName);
					break;
				}
			}
			SaveUsersDataToFile(UsersFileName, vUser);
			cout << "\n User Is Updated Successfully. ";
			return true;
		}

	}
	else
		cout << "\n User with Account Number (" << UserName << ") is Not Found!\n";
	return false;
}

enTransactionOptions ConvertTransactionOptionToEnum(short UserInput)
{
	return enTransactionOptions(UserInput);
}

void PerformDeposit()
{
	vector<stClientData> vClient = LoadDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	int Deposit = 0;
	char ConfirmDeposit = ' ';
	stClientData Client;
	if (FindCLientByAccountNumber(AccountNumber, Client, vClient))
	{
		ShowCLientCard(Client);

		cout << "\n\nPlease Enter Deposit Amount ? \n";
		cin >> Deposit;
		for (stClientData &C:vClient)
		{
			if (AccountNumber==C.AccountNumber)
			{
				cout << "\nAre You Sure You Want To Complete This Transaction ? Y/N \n";
				cin >> ConfirmDeposit;
				if (toupper(ConfirmDeposit)=='Y')
				{
					C.AccountBalance += Deposit;

					cout << "Done Successfully ,New Balance is : " << C.AccountBalance<<endl;
					SaveClientsDataToFile(ClientsFileName, vClient);
				}
				
			}
		}
		

	}
	else
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
}

void PerformWithdraw()
{
	vector<stClientData> vClient = LoadDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	int Withdraw = 0;
	char ConfirmWithdraw = ' ';
	stClientData Client;
	if (FindCLientByAccountNumber(AccountNumber, Client, vClient))
	{
		ShowCLientCard(Client);

		cout << "\n\nPlease Enter Withdraw Amount ? \n";
		cin >> Withdraw;
		while (Withdraw>Client.AccountBalance )
		{
			cout << "Amount Exceeds The Balance, You Can Withdraw Up To : " << Client.AccountBalance ;
			cout << "\nPlease Enter Another Amount : ";
			cin >> Withdraw;
		}
		for (stClientData& C : vClient)
		{
			if (AccountNumber == C.AccountNumber)
			{
				cout << "\nAre You Sure You Want To Complete This Transaction ? Y/N \n";
				cin >> ConfirmWithdraw;
				if (toupper(ConfirmWithdraw) == 'Y')
				{
					C.AccountBalance -= Withdraw;
					
					cout << "Done Successfully ,New Balance is : " << C.AccountBalance << endl;
					SaveClientsDataToFile(ClientsFileName, vClient);
				}

			}
		}


	}
	else
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
}

void PerformTotalBalances()
{
	system("cls");
	vector<stClientData> vClient = LoadDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\t Client List (" << vClient.size() << ")  Client(s). ";
	cout << "\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
	cout << "| " << left << setw(20) << "Account Number ";
	cout << "| " << left << setw(40) << "Client Name ";
	cout << "| " << left << setw(15) << "Account Balance ";
	cout << "\n\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
	double TotalBalances =0;
	for (stClientData Client : vClient)
	{
		TotalBalances += Client.AccountBalance;
		PrintTotalBalances(Client);
	}
	cout << "\n\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
	cout << "\n\t\t\t\tTotalBalances : " << TotalBalances;
}

void ShowDepositScreen()
{
	system("cls");
	cout << "---------------------------------------------------- \n";
	cout << "\t\t Deposit Screen \n";
	cout << "---------------------------------------------------- \n";
	PerformDeposit();
}

void ShowWithdrawScreen()
{
	system("cls");
	cout << "---------------------------------------------------- \n";
	cout << "\t\t Withdraw Screen \n";
	cout << "---------------------------------------------------- \n";
	PerformWithdraw();
}

void ShowTotalBalances()
{
	system("cls");
	cout << "---------------------------------------------------- \n";
	cout << "\t\t TotalBalances Screen \n";
	cout << "---------------------------------------------------- \n";
	PerformTotalBalances();
}

void ExitScreen()
{
	system("cls");
	cout << "-------------------------------------------- \n";
	cout << "\t\tProgram Ends :( \n";
	cout << "-------------------------------------------- \n";
}

bool CheckAccessPermission(enUserPermissions Permission)
{
	if (CurrentUser.Premission == enUserPermissions::All)
		return true;

	if ((Permission & CurrentUser.Premission) == Permission)
		return true;
	else
		return false;

}

enMainMenuOptions ConvertOptionsToEnum(short UserInput)
{
	return enMainMenuOptions(UserInput);
}

enManageUserOptions ConvertUserOptionsToEnum(short UserInput)
{
	return enManageUserOptions(UserInput);
}

void TransactionOptions(enTransactionOptions TransactionOptionInEnum)
{
	if (TransactionOptionInEnum == Deposit)
	{
		ShowDepositScreen();
		BackToTransctionsMenu();

	}
	else if (TransactionOptionInEnum == Withdraw)
	{
		ShowWithdrawScreen();
		BackToTransctionsMenu();
	}
	else if (TransactionOptionInEnum == TotalBalance)

	{
		ShowTotalBalances();
		BackToTransctionsMenu();

	}
	else if (TransactionOptionInEnum == MainMenu)
	{
		ShowMainMenu();

	}
}

void ManageUserOptions(enManageUserOptions ManageUserOptionInEnum)
{

	if (ManageUserOptionInEnum == ListUser)
	{
		ShowUsersScreen();
		BackToManageUsersScreen();
	}
	else if (ManageUserOptionInEnum == AddUser)
	{
		AddNewUserScreen();
		BackToManageUsersScreen();
	}
	else if (ManageUserOptionInEnum == DeleteUser)
	{
		DeleteUserScreen();
		BackToManageUsersScreen();
	}
	else if (ManageUserOptionInEnum == UpdateUser)
	{
		UpadateUserScreen();
		BackToManageUsersScreen();
	}
	else if (ManageUserOptionInEnum == FindUser)
	{
		FindUserScreen();
		BackToManageUsersScreen();
	}
	else if (ManageUserOptionInEnum == MainMenuUser)
	{
		ShowMainMenu();
	}
}
void ShowAccessDeniedMassage()
{
	system("cls");
	cout << "============================================================\n";
	cout << " Access Denied ,\n";
	cout << " You do not have access to do this,\n";
	cout << "  Please contact with your Admin.\n";
	cout << "============================================================\n";
	
}
void ShowManageUsersScreen()
{
	system("cls");
	if (!CheckAccessPermission(ManageUsersPermission))
	{
		ShowAccessDeniedMassage();
		BackToMenu();
	}
	cout << "============================================================\n";
	cout << "\t\t Manage Users Screen\n";
	cout << "============================================================\n";
	cout << "\t[1] List All Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu.\n";
	cout << "============================================================\n";
	ManageUserOptions(ConvertUserOptionsToEnum(ReadUserOptions()));

}

void ShowTransactionScreen()
{
	system("cls");
	if (!CheckAccessPermission(TransactionsPermission))
	{
		ShowAccessDeniedMassage();
		BackToMenu();
	}
	cout << "============================================================\n";
	cout << "\t\t Transaction Menu Screen\n";
	cout << "============================================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total balances.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "============================================================\n";
	TransactionOptions(ConvertTransactionOptionToEnum(ReadTransactionMenuOptions()));
}

void Options(enMainMenuOptions OptionsInEnum)
{

	if (OptionsInEnum == Show)
	{
		ShowClientsScreen();
		BackToMenu();
	}
	else if (OptionsInEnum == Add)
	{
		AddNewClientScreen();
		BackToMenu();
	}
	else if (OptionsInEnum == Delete)

	{
		DeleteClientScreen();
		BackToMenu();
	}
	else if (OptionsInEnum == Update)
	{
		UpadateClientScreen();
		BackToMenu();
	}
	else if (OptionsInEnum == Find)
	{
		FindClientScreen();
		BackToMenu();
	}
	else if (OptionsInEnum == Transactions)
	{
		ShowTransactionScreen();
	}
	else if (OptionsInEnum == ManageUsers)
	{
		ShowManageUsersScreen();
	}
	else if (OptionsInEnum == Logout)
	{
		ShowLoginScren();
	}

}

void ShowMainMenu()
{
	system("cls");
	cout << "============================================================\n";
	cout << "\t\t Main Menu Screen\n";
	cout << "============================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "============================================================\n";

	Options(ConvertOptionsToEnum(ReadMenuOptions()));
}

void ShowLoginScren()
{
	vector<stUserData> vUser = LoadDataFromUsersFile(UsersFileName);
	stUserData User;
	bool LoginFalied = false;
	string UserName, Password;
	do
	{
		system("cls");

		cout << "\n---------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n---------------------------------\n";

		if ( LoginFalied )
		{
			cout << "Invlaid Username/Password!\n";
		}

		cout << "Enter Username? ";
		cin >> UserName;

		cout << "Enter Password? ";
		cin >> Password;

		LoginFalied = !FindUserByUserNameAndPassword(UserName, Password, CurrentUser, vUser);

	} while (LoginFalied);
	ShowMainMenu();
}

int main()
{
	ShowLoginScren();
	system("pause>0");
	return 0;
}//account number exist