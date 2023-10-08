#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <ctime>
using namespace std;

bool allDigits(string &str)
{
  for (char c : str)
  {
    if (!isdigit(c))
    {
      return false;
    }
  }
  return true;
}

class Bank
{
public:
  string acc_no;
  long account_number;
  string name;
  string dob;
  int age;
  string date;
  string phone;
  int balance;
  string depo;
  string acc_type;
  string password;

  int Exit()
  {
    return 0;
  }

  void login()
  {
    //-------------ACCOUNT NUMBER------------------
    system("cls");
    system("color 3");
    cout << "Enter the Acc number: ";

    int flag = 1;
    while (flag)
    {
      cin >> acc_no;
      if (allDigits(acc_no))
      {
        flag = 0;
      }
      else
      {
        cout << "invalid account number" << endl;
      }
    }
    cout << "Password\n";
    char password[8]; // Array to store the password
    int i = 0;        // Index for password characters

    cout << "Enter password: ";
    char ch;
    while (true)
    {
      ch = _getch(); // Read a character without echoing it

      if (ch == '\r' || ch == '\n') // Check for Enter key
        break;
      else if (ch == '\b')
      {
        if (i > 0)
        {
          i--;
          cout << "\b \b";
        }
      }
      else
      {
        if (i < sizeof(password) - 1)
        {
          password[i++] = ch;
          cout << '*'; // Print a '*' to represent the character
        }
      }
    }
    cout << "\n";
    password[i] = '\0'; // Null-terminate the password string

    fstream fin;

    fin.open("Acc.csv", ios::in);

    if (!fin.is_open())
    {
      cout << "Error opening file.\n";
    }

    int count = 0;

    vector<string> row;
    string line, word;

    while (getline(fin, line))
    {
      row.clear();

      stringstream s(line);

      while (getline(s, word, ','))
      {
        row.push_back(word);
      }
      string acc2 = row[0];
      string pass = row[7];
      if (acc2 == acc_no && pass == password)
      {
        count = 1;
        cout << "Acc number : " << row[0] << "\n";
        cout << "Name : " << row[1] << "\n";
        cout << "DOB : " << row[2] << "\n";
        cout << "Age : " << row[3] << "\n";
        cout << "Phone : " << row[4] << "\n";
        cout << "Type : " << row[5] << "\n";
        cout << "DOAC : " << row[6] << "\n";
        Option();
      }
      
    }
    fin.close();
  }

  void Create_acc()
  {
    system("cls");
    system("color 3");
    fstream fout,fin;
    string text;
    int bal = 0;
    cout << "Enter your details" << endl;
    fout.open("Acc.csv", ios::out | ios::app);
   
    cout << "Enter the Acc number: ";

    int flag = 1;
    while (flag)
    {
      cin >> acc_no;
      if (allDigits(acc_no))
      {
        flag = 0;
      }
      else
      {
        cout << "*invalid account number*" << endl;
        cout << "Enter valid account number" << endl;
      }
    }
    fin.open("Acc.csv", ios::in);

    int count = 0;

    vector<string> row;
    string line, word;

    while (getline(fin, line))
    {
      row.clear();

      stringstream s(line);

      while (getline(s, word, ','))
      {
        row.push_back(word);
      }
      string acc2 = row[0];
      
      if (acc2 == acc_no)
      {
        cout<<"This account number is taken"<<endl;
        return ;
      }
      
    }
    fin.close();

    cout << "Name:";
    getline(cin, name);
    getline(cin, name);

    cout << "DOB:";

    getline(cin, dob);
    cout << "Age:";
    cin >> age;

    cout << "Phone number:";
    cin >> phone;

    cin.clear();

    cout << "Type Of Account:";

    cin >> acc_type;

    cout << "Date of Account creation:";
    cin >> date;

    cout << "NOTE: Password should not be greater than 8 characters\n";
    char password[8]; // Array to store the password
    int i = 0;        // Index for password characters

    cout << "Enter password: ";
    char ch;
    while (true)
    {
      ch = _getch(); // Read a character without echoing it

      if (ch == '\r' || ch == '\n') // Check for Enter key
        break;
      if (ch == '\b')
      {
        if (i > 0)
        {
          i--;
          cout << "\b \b";
        }
      }
      if (i < sizeof(password) - 1)
      {
        password[i++] = ch;
        cout << '*'; // Print a '*' to represent the character
      }
    }
    cout << "\n";
    password[i] = '\0'; // Null-terminate the password string
    cin.sync();

    fout << acc_no << "," << name << "," << dob << "," << age << "," << phone << "," << acc_type << "," << date << "," << password << "," << bal << endl;

    fout.close();

    fout.open("balance.csv", ios::out | ios::app);
    cout << "Deposit money:";
    cin >> bal;
    fout << acc_no << "," << bal << endl;

    fout.close();
    fout.open("Password.csv", ios::out | ios::app);
    fout << acc_no << "," << password << endl;
    fout.close();
    cout << "Your account created successfully" << endl;
    cout << "Login to your account" << endl;

    login();
  }

  void deposit()
  {

    time_t now = time(0);
    string dt = ctime(&now);

    fstream fin;

    int count = 0, amt, amt2;

    vector<string> row;
    string line, word;

    fstream fout;

    fin.open("balance.csv", ios::in);
    if (!fin.is_open())
    {
      cout << "Error opening file.\n";
    }

    fout.open("balancenew.csv", ios::out);

    string acc1, y;
    int i, choice;
    int index = 1;
    row.clear();

    cout << "\n\nDo you want to\n1.Deposit\n2.Withdraw?\n\n"
         << "Enter your choice(1 for deposit and 2 for withdraw):";
    cin >> choice;
    cout << "Enter Amount: ";
    cin >> amt;
    int z = 0;
    // Traverse the file
    while (!fin.eof())
    {
      row.clear();

      getline(fin, line);
      stringstream s(line);

      while (getline(s, word, ','))
      {
        row.push_back(word);
      }
      depo = row[1];

      acc1 = row[0];
      int row_size = row.size();

      if (acc1 == acc_no)
      {

        stringstream convert;
        if (choice == 1 && count == 0)
        {
          amt2 = atoi(depo.c_str()) + amt;
          y = to_string(amt2);
          cin.clear();
          cout << "Give money to counter" << endl
               << "Your money deposited successfully" << endl;
          count = 1;
          fstream file;
          file.open("History.csv", ios::app);

          file << acc_no << ","
               << "Self deposit"
               << "," << amt << ","
               << ""
               << "," << amt2 << "," << dt;

          file.close();
        }
        else if (choice == 2 && count == 0)
        {
          cin.clear();
          amt2 = atoi(depo.c_str()) - amt;
          cin.clear();

          if (amt2 < 500 && z == 0)
          {
            y = depo;
            cout << "withdraw not possible" << endl;
            z = 1;
          }
          if (500 <= amt2 && z == 0)
          {
            y = to_string(amt2);
            cin.clear();
            cout << "Withdraw successful" << endl
                 << "Take money from counter" << endl;
            z = 1;
            count = 1;
            fstream file;
            file.open("History.csv", ios::app);

            file << acc_no << ","
                 << "Self withdraw"
                 << ","
                 << ""
                 << "," << amt << "," << amt2 << "," << dt;
            file.close();
          }
        }

        // sending a number as a stream into output string
        convert << y;

        // the str() converts number into string
        row[index] = convert.str();

        for (i = 0; i < row_size - 1; i++)
        {
          fout << row[i] << ",";
        }
        fout << row[row_size - 1] << "\n";
      }
      else
      {
        for (i = 0; i < row_size - 1; i++)
        {
          // writing other existing records
          // into the new file using fout.
          fout << row[i] << ",";
        }

        // the last column data ends with a '\n'
        fout << row[row_size - 1] << "\n";
      }
      if (fin.eof())
      {
        break;
      }
    }

    if (count == 0)
      cout << "Record not found\n";

    fin.close();
    fout.close();
    cin.clear();

    // removing the existing file
    remove("balance.csv");

    // renaming the updated file with the existing file name
    rename("balancenew.csv", "balance.csv");

    Option();
  }

  void modifyAcc()
  {
    fstream fin;

    system("cls");
    system("color 3");
    // Open an existing file
    fin.open("Acc.csv", ios::in);

    if (!fin.is_open())
    {
      cout << "Error opening file.\n";
    }

    int count = 0;

    vector<string> row;
    string line, word;

    while (getline(fin, line))
    {
      row.clear();

      stringstream s(line);

      while (getline(s, word, ','))
      {
        row.push_back(word);
      }

      string acc2 = row[0];
      if (acc2 == acc_no)
      {
        count = 1;
        cout << "Acc number : " << row[0] << "\n";
        cout << "Name : " << row[1] << "\n";
        cout << "DOB : " << row[2] << "\n";
        cout << "Age : " << row[3] << "\n";
        cout << "Phone : " << row[4] << "\n";
        cout << "Type : " << row[5] << "\n";
        cout << "DOAC : " << row[6] << "\n";
      }
    }

    if (count == 0)
    {
      cout << "Record not found\n";
    }
    fin.close();

    fstream fout;

    fin.open("Acc.csv", ios::in);

    fout.open("Accnew.csv", ios::out);

    string acc1, change;
    count = 0;
    int i;
    int index;
    row.clear();

    int z;
    cout << "Choose which one you want to change" << endl;
    cout << "   PRESS 1 : Name" << endl;
    cout << "   PRESS 2 : DOB" << endl;
    cout << "   PRESS 3 : Age " << endl;
    cout << "   PRESS 4 : Phone no. " << endl;
    cout << "   PRESS 5 : Type " << endl;

    cin >> z;
    switch (z)
    {
    case 1:
      index = 1;
      break;
    case 2:
      index = 2;
      break;
    case 3:
      index = 3;
      break;
    case 4:
      index = 4;
      break;
    case 5:
      index = 5;
      break;

    default:
      cout << "       Wrong choice.Enter again\n"
           << endl;
      modifyAcc();
      break;
    }

    cout << "Enter change: ";

    getline(cin, change);
    getline(cin, change);
    cin.clear();
    // Traverse the file
    while (!fin.eof())
    {

      row.clear();

      getline(fin, line);
      stringstream s(line);

      while (getline(s, word, ','))
      {
        row.push_back(word);
      }

      acc1 = row[0];
      int row_size = row.size();

      if (acc1 == acc_no)
      {
        count = 1;
        stringstream convert;

        // sending a number as a stream into output string
        convert << change;

        // the str() converts number into string
        row[index] = convert.str();

        if (!fin.eof())
        {
          for (i = 0; i < row_size - 1; i++)
          {
            fout << row[i] << ",";
          }
          fout << row[row_size - 1] << "\n";
        }
      }
      else
      {
        if (!fin.eof())
        {
          for (i = 0; i < row_size - 1; i++)
          {
            // writing other existing records
            // into the new file using fout.
            fout << row[i] << ",";
          }
          // the last column data ends with a '\n'
          fout << row[row_size - 1] << "\n";
        }
      }
      if (fin.eof())
      {
        break;
      }
    }
    if (count == 0)
      cout << "Record not found\n";

    fin.close();
    fout.close();

    remove("Acc.csv");

    rename("Accnew.csv", "Acc.csv");
    Option();
  }

  int transfer()
  {
    time_t now = time(0);
    string dt = ctime(&now);

    fstream fin, fout;

    int count = 0, amt, amt2;
    string Accnum2;

    cout << "Enter the Acc number to whoom you want to send money: ";
    cin >> Accnum2;
    vector<string> row;
    string line, word;

    fin.open("balance.csv", ios::in);
    if (!fin.is_open())
    {
      cout << "Error opening file.\n";
    }

    fout.open("balancenew.csv", ios::out);

    string acc1, y;
    int i, choice;
    int index = 1;

    cout << "Enter Amount: ";
    cin >> amt;

    int z = 0;
    // Traverse the file
    while (!fin.eof())
    {
      row.clear();

      getline(fin, line);
      stringstream s(line);

      while (getline(s, word, ','))
      {
        row.push_back(word);
      }
      depo = row[1];

      acc1 = row[0];
      int row_size = row.size();

      if (acc1 == acc_no)
      {

        stringstream convert;

        amt2 = atoi(depo.c_str()) - amt;
        y = depo;

        if (500 <= amt2 && z == 0)
        {
          y = to_string(amt2);
          cin.clear();
          cout << "Money transfered successfully" << endl;
          z = 1;
          count = 1;

          fstream file;
          file.open("History.csv", ios::app);

          file << acc_no << "," << Accnum2 << ","
               << ""
               << "," << amt << "," << amt2 << "," << dt;

          file.close();
        }
        else if (amt2 < 500 && z == 0)
        {
          y = depo;
          amt = 0;
          cout << "This amount cannot be transfered." << endl;
          z = 1;
          count = 2;
        }

        // sending a number as a stream into output string
        convert << y;

        // the str() converts number into string
        row[index] = convert.str();

        for (i = 0; i < row_size - 1; i++)
        {
          fout << row[i] << ",";
        }
        fout << row[row_size - 1] << "\n";
      }
      else
      {
        for (i = 0; i < row_size - 1; i++)
        {
          // writing other existing records into the new file using fout.
          fout << row[i] << ",";
        }
        // the last column data ends with a '\n'
        fout << row[row_size - 1] << "\n";
      }
      if (fin.eof())
      {
        break;
      }
    }
    if (count == 0)
      cout << "Record not found\n";

    fin.close();
    fout.close();

    // removing the existing file
    remove("balance.csv");

    // renaming the updated file with the existing file name
    rename("balancenew.csv", "balance.csv");

    Option();
  }

  void display_balance()
  {
    fstream fin;

    system("cls");
    // Open an existing file
    fin.open("balance.csv", ios::in);

    if (!fin.is_open())
    {
      cout << "Error opening file.\n";
    }

    int count = 0;

    vector<string> row;
    string line, word;

    while (getline(fin, line))
    {
      row.clear();

      stringstream s(line);

      while (getline(s, word, ','))
      {
        row.push_back(word);
      }

      string acc2 = row[0];
      if (acc2 == acc_no)
      {
        count = 1;
        cout << "Balance : " << row[1] << "\n";
        break;
      }
    }

    if (count == 0)
    {
      cout << "Record not found\n";
    }
    fin.close();
    Option();
  }

  void Option()
  {
    int k;

    cout << endl
         << "   PRESS 1 : Menu " << endl;
    cout << "   PRESS 2 : Exit " << endl;
    cin >> k;
    switch (k)
    {
    case 1:
      set();
      break;
    case 2:
      Exit();
      break;
    default:
      cout << "       You entered wrong number" << endl;
      Option();
      break;
    }
  }

  void set()
  {
    system("cls");
    int k;
    cout << "   PRESS 1 : Check Balance" << endl;
    cout << "   PRESS 2 : Deposite or Withdraw Money" << endl;
    cout << "   PRESS 3 : Transfer money " << endl;
    cout << "   PRESS 4 : Update account information " << endl;
    cout << "   PRESS 5 : Exit " << endl;
    cout << "   PRESS 6 : Show history " << endl;
    cin >> k;

    switch (k)
    {
    case 1:
      display_balance();
      break;
    case 2:
      deposit();
      break;
    case 3:
      transfer();
      break;
    case 4:
      modifyAcc();
      break;
    case 5:
      Exit();
      break;
    case 6:
      show_Statement();
      break;
    default:
      cout << "       You entered wrong number" << endl;
      set();
      break;
    }
  }

  void show_Statement()
  {

    fstream fin;

    system("cls");
    // Open an existing file
    fin.open("History.csv", ios::in);

    if (!fin.is_open())
    {
      cout << "Error opening file.\n";
    }

    int count = 0;

    vector<string> row;
    string line, word;

    cout << "\tTo acc no.\t\t\tCredit\t\t\tDebit\t\t\tBalance\t\tDate" << endl;
    while (getline(fin, line))
    {
      row.clear();

      stringstream s(line);

      while (getline(s, word, ','))
      {
        row.push_back(word);
      }

      string acc2 = row[0];
      if (acc2 == acc_no)
      {
        count = 1;
        cout << "\t" << row[1] << "\t\t\t";
        cout << row[2] << "\t\t\t";
        cout << row[3] << "\t\t\t";
        cout << row[4] << "\t\t";
        cout << row[5];
        cout << endl;
      }
    }

    if (count == 0)
    {
      cout << "Record not found\n";
    }
    fin.close();
    Option();
  }
};

void main2()
{
  int ch;
  Bank A;
  cin >> ch;

  switch (ch)
  {
  case 1:
    A.login();
    break;
  case 2:
    cout << "Create acc" << endl;
    A.Create_acc();
    break;
  default:
    cout << "                      You entered wrong number." << endl
         << "                      Try again. ";
    main2();
  }
}

int main()
{
  int ch;

menu:
  system("cls");
  system("color 3");
  cout << "\t\t\t....WELCOME TO OUR BANK SERVICE SYSTEM...." << endl
       << endl;
  cout << "\t\t\t\t\tMENU" << endl
       << endl;

  cout << "\t\t\t\tPress 1:To login to account" << endl;
  cout << "\t\t\t\tPress 2: To create a new account" << endl;
  cout << "\t\t\t\tchoose one option  ";

  main2();

  return 0;
}