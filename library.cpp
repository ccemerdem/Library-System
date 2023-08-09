#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

struct userInfo
{
  string nameSurname, password;
  int ID, totalBook;
};

struct bookInfo
{
  string bookName, authorName, name_book_author, category, status;
  int ID, owner, categoryID;
};

int activeID;
bool is_admin = false;

// Admin
void menu_admin();
void add_book();

// User
void signup();
void menu_user();
void return_books();
void list_category();
void choose_category(int amount);
void list_books(int categoryID, string category);
void choose_book(int categoryID, string category, int amount);
void assing_book(int bookID, string name_book_author);

// Common
int menu_main();
void login();
int book_status(int bookID);
void assing_book(int bookID, string name_book_author);
void unAssing_book(int bookID);
string get_ID(int userID);

int main()
{
  menu_main();
  return 0;
}

int menu_main()
{
  is_admin = false;
  system("cls");
  int select_menu, verify = 1;

  cout << " /-----------------------------------\\" << endl;
  cout << "|    Welcome To The Library System    |" << endl;
  cout << " \\-----------------------------------/" << endl;
  cout << "\nSelect the action you want to do" << endl;
  cout << "\n1) Log In     2) Sign Up     3) Exit" << endl;

  do
  {
    select_menu = getch();

    switch (select_menu)
    {
    // It's in quotes because the getch() function returns the ascii value of the input.
    case '1':
      verify = 0;

      system("cls");
      login();
      break;

    case '2':
      verify = 0;

      system("cls");
      signup();

      break;

    case '3':
      verify = 0;
      return 0;
    }
  } while (verify);
  return 0;
}

void signup()
{
  fstream user;
  fstream admin;
  userInfo u;

  // 'IDdummy' was created to check the existence of the ID
  int IDdummy, verify, step, adminID;

  // It was created to skip the password and name surname in '.txt'
  string dummy;

  // Created to check the existence of the user.txt file
  ifstream if_user("user.txt");

  // The existence of the User.txt file is queried
  if (!if_user.good())
  {
    ofstream create_user("user.txt");
  }

  admin.close();
  user.close();

  user.open("user.txt", ios::in);
  admin.open("admin.txt", ios::in);

  do
  {
    verify = 1;
    step = 0;

    cout << "Enter a ID: ";
    cin >> IDdummy;

    for (int temp = IDdummy; temp > 0; step++)
    {
      temp /= 10;
    }

    if (step != 6)
    {
      system("cls");
      cout << "\t\tWarning!" << endl
           << "\nThis ID is not valid! Must be have 6 digit" << endl;
      verify = 0;
      continue;
    }

    if (verify == 1)
    {
      user.seekg(0);

      while (!user.eof() && !admin.eof())
      {
        user >> dummy >> u.ID;
        cin.ignore(0);
        getline(user, dummy);
        admin >> adminID;

        if (IDdummy == u.ID || IDdummy == adminID)
        {
          system("cls");
          cout << "\tWarning!" << endl
               << "\nThis ID already exists!\n"
               << endl;
          verify = 0;
          break;
        }
      }
    }
  } while (!verify);

  u.ID = IDdummy;
  user.close();
  admin.close();

  user.open("user.txt", ios::app);
  user.setf(ios::left);

  cout << "Enter your name and surname: ";
  cin.ignore();
  getline(cin, u.nameSurname);

  cout << "Enter your password: ";
  cin >> u.password;

  user << setw(5) << 0;
  user << setw(10) << u.ID;
  user << setw(30) << u.password;
  user << u.nameSurname << endl;

  user.close();

  cout << "\nSign p successful!   Returning main menu...";

  Sleep(2000);
  system("cls");
  Sleep(150);

  menu_main();
}

void login()
{
  fstream user;

  fstream admin;
  userInfo u;

  // 'dummy' was created to skip the first and last names found in .txt
  string dummy, password;

  // 'int' and 'long int' can only take ten digits of input so using 'long long int' this limitation is circumvented
  long long ID, verify = 0, verify2 = 1, step;

  ifstream if_user("user.txt");

  // The existence of the 'User.txt' file is queried
  if (!if_user.good())
  {
    ofstream create_user("user.txt");
  }

  admin.close();
  user.close();

  admin.open("admin.txt", ios::in);
  user.open("user.txt", ios::in);

  do
  {
    user.seekg(0);
    admin.seekg(0);

    while (verify2)
    {
      cout << "Enter your ID: ";
      cin >> ID;

      step = 0;
      for (long long temp = ID; temp > 0; step++)
      {
        temp /= 10;
      }

      if (step != 6)
      {
        system("cls");
        cout << "\t\tWarning!" << endl
             << "\nThis ID is not valid! Must be have 6 digit\n"
             << endl;
        continue;
      }

      verify2 = 0;
    }

    cout << "Enter your password: ";
    cin.ignore();
    getline(cin, password);

    while (!admin.eof())
    {
      admin >> u.ID >> u.password;

      if (ID == u.ID && password == u.password)
      {
        cout << "Admin Login successful!";
        verify = 1;
        is_admin = true;
        admin.close();
        menu_admin();
        break;
      }
    }

    while (!user.eof())
    {
      user >> dummy >> u.ID >> u.password;

      // It was created to skip the password and name surname in '.txt'
      getline(user, dummy); //

      if (ID == u.ID && password == u.password)
      {
        cout << "\nLogin successful!";

        Sleep(600);

        verify = 1;
        activeID = ID;

        user.close();
        menu_user();

        break;
      }
    }

    if (!verify)
    {
      system("cls");
      cout << "      Warning!" << endl;
      cout << "\nWrong ID or password!\n"
           << endl;

      Sleep(1700);

      menu_main();
    }
  } while (!verify);
}

void menu_admin()
{
  fstream book_list;
  int select_menu, verify = 1;
  system("cls");

  cout << "Select the action you want to do;" << endl;
  cout << "\n1) Add books   2) Remove a book   3) Log Out" << endl;

  do
  {
    select_menu = getch();

    switch (select_menu)
    {
    // It's in quotes because the getch() function returns the ascii value of the input.
    case '1':
      verify = 0;

      system("cls");
      add_book();
      break;

    case '2':
      verify = 0;

      system("cls");
      list_category();
      break;

    case '3':
      verify = 0;
      activeID = 0;

      system("cls");
      menu_main();
    }
  } while (verify);
}

void add_book()
{
  fstream book_list;
  bookInfo b;
  int amount, number = 1;

  book_list.close();

  book_list.open("book_list.txt", ios::out | ios::app);

  cout << "How many books do you want to enter? : ";
  cin >> amount;

  system("cls");

  while (amount != 0)
  {
    amount--;

    cout << "          Book " << number << endl;
    cout << "--------------------------" << endl;
    number++;

    cout << "Category ID : ";
    cin >> b.categoryID;
    cout << "Book ID (Max. lenght is 6): ";
    cin >> b.ID;

    cout << "Book name: ";
    cin.ignore();
    getline(cin, b.bookName);

    cout << "Author name: ";
    getline(cin, b.authorName);

    book_list << endl << left << setw(8) << b.categoryID << right << setw(7) << b.ID << " '" << b.bookName << "' by " << b.authorName;
    cout << endl;
  }

  book_list.close();
  menu_admin();
}

void remove_book(int bookID)
{
  fstream book_list;
  fstream temp_book_list;
  bookInfo b;
  userInfo u;
  string dummy;

  book_list.close();

  book_list.open("book_list.txt", ios::in);
  temp_book_list.open("temp_book_list.txt", ios::out);

  while (!book_list.eof())

  {
    book_list >> b.categoryID >> b.ID;
    getline(book_list, b.name_book_author);

    if (bookID == b.ID)
    {
      continue;
    }

    temp_book_list << endl
                   << left << setw(7) << b.categoryID << right << setw(7) << b.ID << b.name_book_author;
  }

  book_list.close();
  temp_book_list.close();

  remove("book_list.txt");
  rename("temp_book_list.txt", "book_list.txt");

  unAssing_book(bookID);
  menu_admin();
}

void menu_user()
{
  fstream assing_list;

  int select_menu, verify = 1;
  system("cls");
  cout << "Hi " << get_ID(activeID) << "!" << endl;

  cout << "\nSelect the action you want to do" << endl;
  cout << "\n1) Borrow books   2) Return books    3) Log Out" << endl;
  cout << "     (Max. 3)" << endl;

  do
  {
    select_menu = getch();

    switch (select_menu)
    {
    case '1':
      verify = 0;

      list_category();
      break;

    case '2':
      verify = 0;

      return_books();
      break; // t�rnak i�inde yaz�ld���nda ascii de�eri baz al�n�r ('2')
    case '3':
      verify = 0;
      activeID = 0;

      system("cls");
      menu_main();
    }
  } while (verify);
}

void list_category()
{
  fstream book_category;
  bookInfo b;
  int number, amount = 0;

  system("cls");

  book_category.close();
  book_category.open("book_category.txt", ios::in);

  while (!book_category.eof())
  {
    amount++;
    book_category >> number;
    cout << number << ")";

    getline(book_category, b.category);
    cout << b.category << endl;
  }

  cout << endl
       << amount + 1 << ") Back" << endl;
  book_category.close();

  choose_category(amount);
}

void choose_category(int amount)
{
  fstream book_category;
  bookInfo b;
  string dummy;
  int number;

  cout << "\nSelect the category: ";
  cin >> b.categoryID;

  // '+1' was added to create the back option and prevent possible larger digit entries
  if (b.categoryID > amount + 1)
  {
    list_category();
  }

  if (b.categoryID == amount + 1)
  {
    if (is_admin)
    {
      menu_admin();
    }

    menu_user();
  }
  // It has been put to return to the beginning of the file
  book_category.close();
  book_category.open("book_category.txt", ios::in);

  while (!book_category.eof())
  {
    book_category >> number;

    if (b.categoryID == number)
    {
      getline(book_category, b.category);
      book_category.close();
      list_books(b.categoryID, b.category);
    }

    getline(book_category, dummy);
  }
}

void list_books(int categoryID, string category)
{
  fstream book_list;
  bookInfo b;
  string dummy;
  int status, amount = 0;

  book_list.close();

  book_list.open("book_list.txt", ios::in);

  system("cls");
  cout << category << endl
       << " ---------------" << endl;

  while (!book_list.eof())
  {
    book_list >> b.categoryID >> b.ID;
    getline(book_list, b.name_book_author);

    if (categoryID == b.categoryID)
    {
      amount++;
      status = book_status(b.ID);
      cout << endl
           << amount << ")" << left << setw(70) << b.name_book_author;

      if (status == 1)
      {
        cout << "Available" << endl;
      }
      else
      {
        cout << "Not available" << endl;
      }
    }
  }

  book_list.close();
  cout << endl
       << amount + 1 << ")"
       << "  Back" << endl
       << endl;
  choose_book(categoryID, category, amount);
}

void choose_book(int categoryID, string category, int amount)
{
  fstream book_list;
  bookInfo b;
  string dummy;
  int number, step = 0, value = 1;

  book_list.close();

  book_list.open("book_list.txt", ios::in);
  cin >> number;

  // '+1' was added to create the back option
  if (number == amount + 1)
  {
    list_category();
  }

  while (!book_list.eof())
  {
    book_list >> b.categoryID >> b.ID;
    getline(book_list, b.name_book_author);

    if (b.categoryID == categoryID)
    {
      step++;
      if (step == number)
      {
        book_list.close();
        value = 0;

        if (is_admin)
        {
          remove_book(b.ID);
          break;
        }

        assing_book(b.ID, b.name_book_author);
        break;
      }
    }
  }

  if (value == 1)
  {
    book_list.close();
    list_books(categoryID, category);
  }
}

void assing_book(int bookID, string name_book_author)
{
  fstream assing_list;
  bookInfo b;
  userInfo u;
  string dummy;
  int amount = 0, value = 1;

  assing_list.close();

  assing_list.open("assing_list.txt", ios::in);

  while (!assing_list.eof())
  {
    assing_list >> u.ID >> dummy;
    getline(assing_list, dummy);

    if (u.ID == activeID)
    {
      amount++;

      if (amount == 3)
      {
        system("cls");

        cout << "        Warning!" << endl;
        cout << "\nYou have already 3 books.";

        Sleep(1700);

        assing_list.close();
        value = 0;

        menu_user();
        break;
      }
    }

    if (!book_status(bookID))
    {
      system("cls");

      cout << "        Warning!" << endl;
      cout << "\nThe book is already taken.";

      Sleep(1700);

      assing_list.close();
      value = 0;

      menu_user();
      break;
    }
  }

  if (value)
  {
    assing_list.close();
    assing_list.open("assing_list.txt", ios::app);

    assing_list << endl
                << left << setw(8) << activeID << right << setw(6) << bookID << left << name_book_author;

    assing_list.close();

    list_category();
  }
}

void unAssing_book(int bookID)
{
  fstream assing_list;
  fstream temp_assing_list;
  bookInfo b;
  userInfo u;

  assing_list.close();

  assing_list.open("assing_list.txt", ios::in);
  temp_assing_list.open("temp_assing_list.txt", ios::out);

  while (!assing_list.eof())
  {
    assing_list >> u.ID >> b.ID;
    getline(assing_list, b.name_book_author);

    if (bookID == b.ID)
    {
      continue;
    }

    temp_assing_list << endl
                     << left << setw(8) << u.ID << right << setw(6) << b.ID << left << b.name_book_author;
  }
  assing_list.close();
  temp_assing_list.close();

  remove("assing_list.txt");
  rename("temp_assing_list.txt", "assing_list.txt");
}

int book_status(int bookID)
{
  fstream assing_list;
  bookInfo b;
  string dummy;
  int value = 0;

  assing_list.close();
  assing_list.open("assing_list.txt", ios::in);

  while (!assing_list.eof())
  {
    assing_list >> dummy >> b.ID;
    getline(assing_list, dummy);

    if (b.ID == bookID)
    {
      value = 1;
      assing_list.close();

      return 0;
      break;
    }
  }
  if (value == 0)
  {
    assing_list.close();
    return 1;
  }
  return -1;
}

void return_books()
{
  fstream assing_list;
  bookInfo b;
  userInfo u;
  string dummy;
  int value = 0, amount = 0, number, step = 0;

  system("cls");

  assing_list.close();
  assing_list.open("assing_list.txt", ios::in);

  // Sorts and prints the books the user owns. (Inventory System)
  while (!assing_list.eof())
  {
    assing_list >> u.ID >> dummy;
    getline(assing_list, b.name_book_author);

    if (u.ID == activeID)
    {
      value = 1;
      amount++;

      cout << amount << ")" << b.name_book_author << endl;
    }
  }
  assing_list.close();
  assing_list.open("assing_list.txt", ios::in);

  if (value == 1)
  {
    cout << "\nSelect the book which you want to return: ";
    cin >> number;

    // Repeats the process if the input exceeds the number of books listed.
    if (number > amount)
    {
      assing_list.close();
      return_books();
    }

    while (!assing_list.eof())
    {
      assing_list >> u.ID >> b.ID;
      getline(assing_list, dummy);

      if (u.ID == activeID)
      {
        step++;
      }

      if (step == number)
      {
        assing_list.close();

        cout << b.ID;

        unAssing_book(b.ID);

        menu_user();
      }
    }
    assing_list.close();
  }

  if (value == 0)
  {
    cout << "You dont have any book.     Returning to the main menu...";

    Sleep(2000);
    menu_user();
  }
  assing_list.close();
}

// Created to know who is logged
string get_ID(int userID)
{
  fstream user;
  string dummy, name;
  userInfo u;

  user.close();
  user.open("user.txt", ios::in);

  while (!user.eof())
  {
    user >> dummy >> u.ID;

    if (u.ID == userID)
    {
      user >> dummy >> name;

      return name;

      user.close();
      break;
    }

    getline(user, dummy);
  }
  return 0;
}

