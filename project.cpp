#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <unistd.h>
#include <vector>
#include <conio.h>

using namespace std;

class customer
{
public:
  string name;
  string room_no;
  string phone_no;
  string password;
  string nm, pwd, ph;
  string login_id;
  vector<string> registered_users;
  string line;
};
class staff
{
public:
  string name;
  string phone_no;
};
class signup : public customer
{
public:
  string confirm_pass;
  void register_cust()
  {
    ofstream fout;
    ifstream fin;
    fout.open("HOTEL MANAGEMENT.txt", ios::out | ios::app);
    fin.open("HOTEL MANAGEMENT.txt");
    if (!fout || !fin)
    {
      cout << "error in opening a file" << endl;
    }

    string data;

    fout.seekp(0, ios::end);
    cout << "signup to your new account!" << endl;
    cout << "ENTER NAME:";
    cin.ignore();
    getline(cin, name);

    cout << "PHONE NO:";
    cin >> phone_no;

    // cout << "ROOM NO:";
    // cin >> room_no;

    nm = name.substr(0, 3);
    ph = phone_no.substr(6);
    pwd = nm + ph;
    cout << "CONGRATULATIONS! \n YOUR LOGIN ID:ABC@\nPASSWORD:" << pwd;

    login_id = "ABC@" + room_no;

    fout << login_id << endl
         << pwd << endl;

    fout.close();
  }
};
class login_cust : public customer
{
public:
  login_cust()
  {

    ifstream fin("HOTEL MANAGEMENT.txt");

    while (getline(fin, line))
    {
      registered_users.push_back(line);
    }

    fin.close();

    string user;
    string pass;
    bool success = false;
    int max_trials = 3;
    system("cls");

    for (int i = 0; i < max_trials; i++)
    {
      cout << "Login ID: ";
      cin >> user;
      cout << "Password: ";
      cin >> pass;
      for (int j = 0; j < registered_users.size(); j += 2)
      {
        stringstream ss(registered_users[j + 1]);
        string stored_pwd;
        ss >> stored_pwd;
        if (user == registered_users[j] && pass == stored_pwd)
        {
          system("cls");
          cout << "######  Welcome!  ######" << endl;
          success = true;

          getch();
          break;
        }
      }
      if (success)
      {

        break;
      }
      else
      {
        cout << "*Incorrect user ID or password.*\nEnter any key from keyboard to try again!" << endl;
        getch();
        system("cls");
      }
    }
    if (!success)
    {
      cout << "Sorry, you have exceeded the maximum number of trials.\n"
           << setw(40) << "Please try again in 30 seconds.\n";
      sleep(30);
      login_cust();
    }
    system("cls");
  }
};
class login_staff
{

public:
  class staff_room_login : public customer
  {
  public:
    string room_pwd;
    string maintenance, line, login_id;
    char response;
    void room_login()
    {
      ofstream fout;
      fout.open("Maintenance_Required.txt", ios::app);
      cout << "Please enter detail of room where maintenance is required!\n";
      cout << "Room Number:";
      cin.ignore();
      getline(cin, room_no);
      fout << "\t\t ROOM NO.:" << room_no << endl;
      cout << "Name of Customer:";
      getline(cin, name);
      fout << "NAME:" << name << endl;
      cout << "Phone Number:";
      getline(cin, phone_no);
      fout << "PHONE NUMBER:" << phone_no << endl;
      cout << "\nEnter the maintenance required if any(one at a time)" << endl;
      fflush(stdin);
      getline(cin, maintenance);
      fout << "MAINTENANCE:" << maintenance << endl;
      bool valid_response = true;
      do
      {
        cout << "Do you want to add any other maintenance (y/n)::";
        cin >> response;
        switch (response)
        {
        case 'y':
        case 'Y':
        {
          cout << "\nEnter the maintenance required if any (one at a time)" << endl;
          cin.ignore();
          getline(cin, maintenance);
          fout << "MAINTENANCE:" << maintenance << endl;
          valid_response = true;

          break;
        }
        case 'n':
        case 'N':
          valid_response = false;
          cout << "Thank youu!!";
          getch();
          exit(1);
        default:
        {
          cout << "Please enter a valid response!" << endl;
          valid_response = false;
          break;
        }
        }
      } while (valid_response);
      fout.close();
    }
  };
  void login_as_staff()
  {
    string login;
    string fixed_password, password;
    login = "services@ABC_hotel";
    fixed_password = "ABChotel";
    int max_trials = 3;
    bool success = false;
    bool outer_loop = false;
    for (int j = 0; !outer_loop && j >= 0; j++)
    {
      for (int i = 0; i < max_trials; i++)
      {
        system("cls");
        cout << "LOGIN ID:" << login << endl;
        cout << "Enter password:";
        fflush(stdin);
        //				getch();
        getline(cin, password);

        // interchanged
        if (fixed_password == password)
        {
          system("cls");
          cout << "######  Welcome!  ######" << endl;
          getch();
          success = true;
          staff_room_login room;
          system("cls");
          room.room_login();
          break;
        }

        if (success)
        {
          outer_loop = true;
          break;
        }
        else
        {
          cout << "\nIncorrect user ID or password.\n*Enter any key from keyboard to try again!*" << endl;
          success = false;
          getch();

          system("cls");
        }
      }
      if (!success)
      {
        cout << "*Sorry, you have exceeded the maximum number of trials.*\n"
             << setw(40) << "Please try again in 30 seconds." << endl;
        sleep(30);
      }
      system("cls");
    }
  }
};

class hotel
{

  int room_no;
  char name[30];
  char address[50];
  char phone[10];

public:
  void main_menu();     // to dispay the main menu
  void add();           // to book a room
  void display();       // to display the customer record
  void rooms();         // to display alloted rooms
  void edit();          // to edit the customer record
  int check(int);       // to check room status
  void modify(int);     // to modify the record
  void delete_rec(int); // to delete the record
  void bill(int);       // for the bill of a record
  void Order_food();
  void foodbill();
};
void hotel::main_menu()
{

  int choice;
  while (choice != 5)
  {

    system("cls");
    cout << "\n\t\t\t\t*************************";
    cout << "\n\t\t\t\t SIMPLE HOTEL MANAGEMENT ";
    cout << "\n\t\t\t\t      * MAIN MENU *";
    cout << "\n\t\t\t\t*************************";
    cout << "\n\n\n\t\t\t1.Book A Room";
    cout << "\n\t\t\t2.Customer Records";
    cout << "\n\t\t\t3.Rooms Allotted";
    cout << "\n\t\t\t4.Edit Record";
    cout << "\n\t\t\t5.Order Food";
    cout << "\n\t\t\t6.Exit";
    cout << "\n\n\t\t\tEnter Your Choice: ";
    cin >> choice;

    switch (choice)
    {

    case 1:
      add();
      break;

    case 2:
      display();
      break;

    case 3:
      rooms();
      break;

    case 4:
      edit();
      break;

    case 5:
      Order_food();
      break;

    case 6:
      cout << "THANK YOU!";
      getch();
      exit(1);

    default:
    {

      cout << "\n\n\t\t\tWrong choice.....!!!";
      cout << "\n\t\t\tPress any key to   continue....!!";
      getch();
    }
    }
  }
}
void hotel::add()
{

  system("cls");
  int r, flag;
  ofstream fout("Record.dat", ios::app);

  cout << "\n Enter Customer Detalis";
  cout << "\n ----------------------";
  cout << "\n\n Room no: ";
  cout << "\n Total no. of Rooms - 50";
  cout << "\n Ordinary Rooms from 1 - 30";
  cout << "\n Luxuary Rooms from 31 - 45";
  cout << "\n Royal Rooms from 46 - 50";
  cout << "\n Enter The Room no. you want to stay in :- " << endl;
  cin >> r;

  flag = check(r);

  if (flag)
    cout << "\n Sorry..!!!Room is already booked";

  else
  {

    room_no = r;
    cout << " Name: ";
    cin >> name;
    cout << " Address: ";
    cin >> address;
    cout << " Phone No: ";
    cin >> phone;

    fout.write((char *)this, sizeof(hotel));
    cout << "\n Room is booked...!!!";
  }

  cout << "\n Press any key to continue.....!!";

  getch();
  fout.close();
}
void hotel::display()
{

  system("cls");

  ifstream fin("Record.dat", ios::in);
  int r, flag;

  cout << "\n Enter room no. for a particular customer`s details :- " << endl;
  cin >> r;

  while (!fin.eof())
  {

    fin.read((char *)this, sizeof(hotel));
    if (room_no == r)
    {

      system("cls");
      cout << "\n Customer Details";
      cout << "\n ----------------";
      cout << "\n\n Room no: " << room_no;
      cout << "\n Name: " << name;
      cout << "\n Address: " << address;
      cout << "\n Phone no: " << phone;
      flag = 1;
      break;
    }
  }

  if (flag == 0)
    cout << "\n Sorry Room no. not found or vacant....!!";
  cout << "\n\n Press any key to continue....!!";

  getch();
  fin.close();
}
void hotel::rooms()
{
  hotel co;
  system("cls");
  int c = 0;
  ifstream fin("Record.dat", ios::in);
  cout << "\n\t\t\t    List Of Rooms Allotted";
  cout << "\n\t\t\t    ----------------------";
  cout << "\n\n Room No.\tName\t\tAddress\t\t\t\tPhone No.\n";
  while (fin.read((char *)this, sizeof(hotel)))
  {
    c++;
  }
  fin.close();
  ifstream fo("Record.dat", ios::in);
  // seekg(0, ios::beg);

  while (c != 0)
  {

    c--;
    fo.read((char *)this, sizeof(hotel));
    cout << "\n\n " << room_no << "\t\t" << name;
    cout << "\t\t" << address << "\t\t" << phone;
  }

  cout << "\n\n\n\t\t\tPress any key to continue.....!!";
  getch();
  fin.close();
  fo.close();
}
void hotel::edit()
{

  system("cls");

  int choice, r;
  cout << "\n EDIT MENU";
  cout << "\n ---------";
  cout << "\n\n 1.Modify Customer Record";
  cout << "\n 2.Delete Customer Record";
  cout << "\n 3. Bill Of Customer";
  cout << "\n Enter your choice: ";

  cin >> choice;
  system("cls");

  cout << "\n Enter room no: ";
  cin >> r;

  switch (choice)
  {

  case 1:
    modify(r);
    break;

  case 2:
    delete_rec(r);
    break;

  case 3:
    bill(r);
    break;

  default:
    cout << "\n Wrong Choice.....!!";
  }
  cout << "\n Press any key to continue....!!!";

  getch();
}
int hotel::check(int r)
{

  int flag = 0;

  ifstream fin("Record.dat", ios::in);

  while (!fin.eof())
  {

    fin.read((char *)this, sizeof(hotel));
    if (room_no == r)
    {

      flag = 1;
      break;
    }
  }

  fin.close();
  return (flag);
}
void hotel::modify(int r)
{

  long pos, flag = 0;

  fstream file("Record.dat", ios::in | ios::out | ios::binary);

  while (!file.eof())
  {

    pos = file.tellg();
    file.read((char *)this, sizeof(hotel));

    if (room_no == r)
    {

      cout << "\n Enter New Details";
      cout << "\n -----------------";
      cout << "\n Name: ";
      cin >> name;
      cout << " Address: ";
      cin >> address;
      cout << " Phone no: ";
      cin >> phone;
      file.seekg(pos);
      file.write((char *)this, sizeof(hotel));
      cout << "\n Record is modified....!!";
      flag = 1;
      break;
    }
  }

  if (flag == 0)
    cout << "\n Sorry Room no. not found or vacant...!!";
  file.close();
}
void hotel::delete_rec(int r)
{

  int flag = 0;
  char ch;
  ifstream fin("Record.dat", ios::in);
  ofstream fout("temp.dat", ios::out);

  while (!fin.eof())
  {

    fin.read((char *)this, sizeof(hotel));
    if (room_no == r)

    {

      cout << "\n Name: " << name;
      cout << "\n Address: " << address;
      cout << "\n Pone No: " << phone;
      cout << "\n\n Do you want to delete this record(y/n): ";
      cin >> ch;

      if (ch == 'n')
        fout.write((char *)this, sizeof(hotel));
      flag = 1;
    }

    else
      fout.write((char *)this, sizeof(hotel));
  }

  fin.close();
  fout.close();

  if (flag == 0)
    cout << "\n Sorry room no. not found or vacant...!!";

  else
  {

    remove("Record.dat");
    rename("temp.dat", "Record.dat");
  }
}
void hotel::bill(int r)

{
  int count = 0;
  hotel h1;
  ifstream f1;
  f1.open("record.dat", ios::in | ios::binary);

  int day = 1;

  if (!f1)
    cout << "cannot open";

  else
  {

    // f1.read((char *)&h1, sizeof(hotel));
    while (f1)

    {

      f1.read((char *)&h1, sizeof(h1));
      if (h1.room_no == r)
      {

        if (h1.room_no >= 1 && h1.room_no <= 30)
        {
          cout << "Total No. Of Days You Stayed  ";
          cin >> day;
          cout << "your bill = " << 2000 * day;
          count++;
          break;
        }

        else if (h1.room_no >= 35 && h1.room_no <= 45)
        {
          cout << "Total No. Of Days You Stayed  ";
          cin >> day;
          cout << "your bill = " << 5000 * day;
          count++;
          break;
        }

        else
        {
          cout << "Total No. Of Days You Stayed   ";
          cin >> day;
          cout << "your bill = " << 7000 * day;
          count++;
          break;
        }
      }
      // if(f1.read((char *)&h1, sizeof(h1)))
      // {

      // }
    }
    if (count == 0)
    {
      cout << "room no. not found";
    }
  }

  f1.close();
  getch();
}
void hotel::Order_food()
{

  cout << "\n\n\n\t\t\t\t\t\t ========== WELCOME TO FOOD ORDERING SYSTEM ==========" << endl;
  cout << "\n\n\t\t\t\t\t\t\t       =====START YOUR ORDER=====" << endl;
  cout << "\n\n\n\t===========================\t\t\t==========================\t\t\t\t===========================" << endl;
  cout << "\t[1] Veggie Supreme (Rs.480)\t\t\t[2] Exotica Pizza(Rs.440)\t\t\t\t[3] Chicken Sizzler (Rs.580)\n\t[4] Chrispy Chicken (Rs.520)\t\t\t[5] Spaghetti (Rs.350)\t\t\t\t\t[6] Country Feast (Rs.400)\n\t[7] Tetrazzini (Rs.420)\t\t\t\t[8] Double Cheese (Rs.540)\t\t\t\t[9] Makizushi (Rs.548)\n\t[10] Ham Burger (Rs.390)\t\t\t[11] Margherita Pizza(Rs.525)\t\t\t\t[12] Fish 'n' Chips (Rs.425)\n\t[13] Fajitas (Rs.335)\t\t\t\t[14] Tempura (Rs.324)\t\t\t\t\t[15] Hot Dog (Rs.360)\n\t===========================\t\t\t==============================\t\t\t\t===========================\n\n\n\t\t\t\t\t\t\t\t[16] EXIT" << endl;
  cout << "\n\t=======================================================================================================================================" << endl;

  foodbill();
}

void hotel::foodbill()
{
  int pizza, ch, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s = 0;
  string y, ye;

  ofstream write;
  write.open("order.text");
  if (!write)
  {
    cout << "file can not open" << endl;
    exit(-1);
  }

a:
b:
c:
  cout << "\n\n\tENTER YOUR ORDER (one order at a time): ";
  cin >> ch;

  cout << "\n\n\tDO YOU WANT TO UPDATE YOUR ORDER (y/n) :";

  cin >> ye;

  if (ye == "y" || ye == "Y")
  {
    goto b;
  }
  else
  {
    switch (ch)
    {
    case 1:
      cout << "\n\n\tHOW MANY PIZZA YOU WANT :";
      cin >> pizza;

      a = 480;
      s = s + a * pizza;
      write << "YOU ORDER  Veggie Supreme : 480";
      write << " \n";
      write << "NUMBER OF PIZZA IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER  Veggie Supreme " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 2:
      cout << "\n\n\tHOW MANY PIZZA YOU WANT :";
      cin >> pizza;

      b = 440;
      s = s + b * pizza;
      write << "YOU ORDER  Exotica : 440";
      write << " \n";
      write << "NUMBER OF PIZZA IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER  Exotica " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 3:
      cout << "\n\n\tHOW MANY CHICKEN SIZZLER YOU WANT :";
      cin >> pizza;

      c = 580;
      s = s + c * pizza;
      write << "YOU ORDER  Chicken Sizzler : 580";
      write << " \n";
      write << "NUMBER OF Chicken Sizzler IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER  Chicken Sizzler " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 4:
      cout << "\n\n\tHOW MANY CHRISPY CHICKEN YOU WANT :";
      cin >> pizza;

      d = 520;
      s = s + d * pizza;
      write << "YOU ORDER  Chrispy Chicken : 520";
      write << " \n";
      write << "NUMBER OF Chrispy Chicken IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER  Chrispy Chicken " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 5:
      cout << "\n\n\tHOW MANY SPAGHETTI YOU WANT:";
      cin >> pizza;

      e = 350;
      s = s + e * pizza;
      write << "YOU ORDER  Spaghetti : 350";
      write << " \n";
      write << "NUMBER OF Spaghetti IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER  Spaghetti " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 6:
      cout << "\n\n\tHOW MANY PIZZA YOU WANT:";
      cin >> pizza;

      f = 400;
      s = s + f * pizza;
      write << "YOU ORDER Country Feast : 400";
      write << "\n ";
      write << "NUMBER OF PIZZA IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER Country Feast " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 7:
      cout << "\n\n\tHOW MANY TETRAZZINI YOU WANT:";
      cin >> pizza;

      g = 420;
      s = s + g * pizza;
      write << "YOU ORDER Tetrazzini : 420";
      write << "\n ";
      write << "NUMBER OF Tetrazzini IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER  Tetrazzini " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 8:
      cout << "\n\n\tHOW MANY PIZZA YOU WANT :";
      cin >> pizza;

      h = 540;
      s = s + h * pizza;
      write << "YOU ORDER Double Cheese : 540";
      write << " \n";
      write << "NUMBER OF PIZZA IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER   Double Cheese " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 9:
      cout << "\n\n\tHOW MANY MAKIZUSHI YOU WANT :";
      cin >> pizza;

      i = 548;
      s = s + i * pizza;
      write << "YOU ORDER Makizushi : 548";
      write << " \n";
      write << "NUMBER OF Makizushi IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER Makizushi " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 10:
      cout << "\n\n\tHOW MANY HAM BURGER YOU WANT :";
      cin >> pizza;

      j = 390;
      s = s + j * pizza;
      write << "YOU ORDER Ham Burger : 390";
      write << " \n";
      write << "NUMBER OF Ham Burger IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER Ham Burger " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 11:
      cout << "\n\n\tHOW MANY PIZZA YOU WANT :";
      cin >> pizza;

      k = 525;
      s = s + k * pizza;
      write << "YOU ORDER Margherita : 525";
      write << " \n";
      write << "NUMBER OF PIZZA IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER   Margherita " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 12:
      cout << "\n\n\tHOW MANY FISH 'n' CHIPS YOU WANT :";
      cin >> pizza;

      l = 425;
      s = s + l * pizza;
      write << "YOU ORDER Fish 'n' Chips : 425";
      write << " \n";
      write << "NUMBER OF Fish 'n' Chips IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER  Fish 'n' Chips " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 13:
      cout << "\n\n\tHOW MANY FAJITAS YOU WANT :";
      cin >> pizza;

      m = 335;
      s = s + m * pizza;
      write << "YOU ORDER  Fajitas  : 335";
      write << " \n";
      write << "NUMBER OF Fajitas IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER Fajitas " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 14:
      cout << "\n\n\tHOW MANY TEMPURA YOU WANT :";
      cin >> pizza;

      n = 324;
      s = s + n * pizza;
      write << "YOU ORDER Tempura : 324";
      write << " \n";
      write << "NUMBER OF Tempura IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER  Tempura " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 15:
      cout << "\n\n\tHOW MANY HOT DOG YOU WANT :";
      cin >> pizza;

      o = 360;
      s = s + o * pizza; // fn1353
      write << "YOU ORDER  Hot Dog : 360";
      write << "\n ";
      write << "NUMBER OF Hot Dog IS : " << pizza;
      write << "\n";
      cout << "\n\n\n\tYOU ORDER  Hot Dog " << endl
           << "\tYOUR ORDER SUCCESSFULLY SAVED " << endl;
      break;

    case 16:
      cout << "\n\t\t\t\t\t Thank You!!";
      exit(0);
      break;

    default:
      cout << "\n\n\t\t\t\t\t\t\tYOU ENTER WRONG ORDER KEY !!!!! " << endl;
      goto c;
      break;
    }
    cout << "\n\tDO YOU WANT ANOTHER ORDER (yes/no) :";
    cin >> y;
    if (y == "yes" || y == "YES")
    {
      goto a;
    }
    else
    {
      cout << "\n\t\t\t\t\t\t\tTHANK YOU FOR YOUR ORDER :) GENERATING BILL ";
    }
  }
  system("cls");
  cout << "\n\t\t\t\t\t\t\t ================================================" << endl;
  cout << "\t\t\t\t\t\t\t|               Food Ordering System             |" << endl;
  cout << "\t\t\t\t\t\t\t ================================================" << endl;
  cout << endl;
  cout << endl;

  cout << "\t\t\t\t\t\t\t  Bill No : CP51           Order : NB1353" << endl;
  cout << endl;
  cout << endl;

  cout << endl;
  cout << "\t\t\t\t\t\t\t    YOUR TOTAL BILL IS Rs." << s << endl;
  write << "\t\t\t\t\t\t\t ";
  write << "\t\t\t\t\t\t\tTOTAL BILL IS : " << s;
  cout << endl;
  cout << endl;

  cout << "\t\t\t\t\t\t\t\t\t\t\tTHANKS FOR COMING";
  cout << "\n\t\t\t\t\t\t\t ================================================" << endl;
  getch();

  write.close();
}
//////
////////
////////////
////////////////
///////////////
///////////////
////////////////
/////////////
/////////////////
/////////////////////////
/////////////////////////////////
//////////////
//////////////
//////////////
//////////////
//////////////
int main()
{
  int choose, y;
  login_staff s1;
  hotel h;
  system("cls");
  cout << "\n\t\t\t****************************";
  cout << "\n\t\t\t*HOTEL MANAGEMENT PROJECT *";
  cout << "\n\t\t\t****************************";
  system("cls");
  do
  {
    system("cls");
    cout << "WELCOME TO HOTEL SERVICES!" << endl;
    cout << "KINDLY SELECT YOUR PROFILE \n 1)STAFF(Maintenance) \n 2)CUSTOMER BOOKING" << endl;
    cin >> y;
    switch (y)
    {
    case (1):
    {
      cout << "WELCOME STAFF MEMBER" << endl
           << "kindly enter the login credentials" << endl;

      s1.login_as_staff();

      break;
    };

    case (2):
    {
      cout << "select the option below\n 1)sign up \n 2)login" << endl;
      cin >> choose;
      switch (choose)
      {
      case (1):
      {
        signup cust1;
        cust1.register_cust();
        getch();
        break;
      }

      case (2):
      {
        login_cust c1;
        // getch();
        h.main_menu();
        break;
      }

      default:
        cout << "enter valid input" << endl;
        getch();
        break;
      }
    }
    }
  }

  while (y != 3);
  // h.main_menu();
  return 0;
}
