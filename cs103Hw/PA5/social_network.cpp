/*Name: Jacob Pitts
Program Info:
  social_network.cpp: instantiates the network 
  and manages the i/o interactions between the
  user and the menu.  also handles most of the
  user checks, ensuring that the users actually
  exist.

*/


#include "network.h"
#include "user.h"

using namespace std;

void menu();

int main(int argc, char *argv[])
{

string User1, User2, LastName;
int zip, year, option;
int check = 0;

  if (argc != 2)
  {
    cout << "Invalid args." << endl;
    cout << "Usage: social_network File" << endl;
    return 1;
  }

  //start network
  Network social_Network;
  int read = social_Network.read_friends(argv[1]);

  if (read == -1)
  {
    cerr << "Couldn't open file";
    return 1;
  }
do
  //options
  {
    menu();

    cin >> option;

    // option 1
    if (option == 1)
    {
      cin >> User1 >> LastName; 
      User1.append(1, ' '); //add the space and the Last Name to the Name string
      User1.append(LastName);
      cin >> year;
      cin >> zip;
      
      social_Network.add_user(User1, year, zip);
    }

    // option 2
    if (option == 2)
    {
      cin >> User1 >> LastName;
      User1.append(1, ' ');
      User1.append(LastName);

      cin >> User2 >> LastName;
      User2.append(1, ' ');
      User2.append(LastName);
      
      check = social_Network.add_connection(User1, User2);
      if (check == -1)
      {
        cerr << "Error, one of the users cannot be found." << endl;
      }
    }

    // option 3
    if (option == 3)
    {
      cin >>  User1 >> LastName;
      User1.append(1, ' ');
      User1.append(LastName);

      cin >> User2 >> LastName;
      User2.append(1, ' ');
      User2.append(LastName);
      
      check = social_Network.remove_connection(User1, User2);
      if (check == -1)
      {
        cerr << "Error, one of the users cannot be found." << endl;
      }
    }

    // option 4
    if (option == 4)
    {
      social_Network.get_user_list();
    }

    // option 5
    if (option == 5)
    {
      cin >> User1 >> LastName;
      User1.append(1, ' ');
      User1.append(LastName);

      social_Network.get_friends_list(User1);
    }

    // option 6
    if (option == 6)
    {
      string file;
      cin >> file;
      check = social_Network.write_friends(file.c_str());
      if (check == -1)
      {
        cerr << "Error, one of the users cannot be found." << endl;
      }
    }

    cout << endl;
  } while ((option > 0) && (option < 7)); //repeat the options as user inputs
  //else end it 
  return 0;
}

void menu()
{
  cout << "=================== MENU ===================" << endl;
  cout << "Option 1: Add a user" << endl;

  cout << "Option 2: Add friend connection" << endl;

  cout << "Option 3: Remove friend connection" << endl;

  cout << "Option 4: Print users" << endl;

  cout << "Option 5: List friend" << endl;

  cout << "Option 6: Write to file" << endl;

  cout << "Option 7: Exit the program" << endl;
}