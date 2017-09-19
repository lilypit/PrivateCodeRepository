/*Name: Jacob Pitts
Program Info:
  network.cpp: defines many of operations
  that are to be used by player in the
  interaction with social_network.cpp. 

*/

#include "network.h"

  Network::Network() {  //default no argument constructor
  }

  Network::~Network() { //deconstructor that deallocates the user.list size
    for (int i = 0; i < user_list.size(); i++)
      delete user_list[i]; 
  }

  int Network::read_friends(const char *File) {
    std::ifstream iFile(File);
    
    if (iFile.fail()) {
      std::cerr << "File couldn't be opened." << std::endl;
      return -1;
    }
    
    std::string id, name, year, zip, friends;

    std::string numOfUsers;
    getline(iFile, numOfUsers);
    int num = atoi(numOfUsers.c_str());   

    for (int i = 0; i < num; i++) { 
      //note, erase is used below to remove the tab that is recieved with getline
      getline(iFile, id);

      getline(iFile, name);

      name.erase(name.begin(), name.begin()+1); 
      
      getline(iFile, year);
      year.erase(year.begin(), year.begin()+1);
      
  
      getline(iFile, zip);
      zip.erase(zip.begin(), zip.begin()+1); 

      nUser = new User(name, atoi(year.c_str()), atoi(zip.c_str()));
      user_list.push_back(nUser); //once we get the user, push it into the list

      getline(iFile, friends);
      friends.erase(friends.begin(), friends.begin()+1);
      std::stringstream ss(friends); 

      int friend_id;
      while(ss >> friend_id)
      { //adds all the friends assosiated with the indv user
        user_list[atoi(id.c_str())]->add_friend(friend_id);
      }
      ss.clear();
      ss.str("");
    }

    iFile.close();

    return 0;
  }
  
  int Network::write_friends(const char *File) {
   
    std::ofstream oFile(File);

    if (oFile.fail()) {
      std::cerr << "File couldn't be opened." << std::endl;
      return -1;
    }

    oFile << user_list.size() << std::endl;
    for (unsigned int i = 0; i < user_list.size(); i++) {
      //for each friend, retrieve their data
      std::string name = user_list[i]->get_name();
      int id = get_id(name);
      int year = user_list[i]->get_year();
      int zip = user_list[i]->get_zip();
      vector<int> friends = user_list[i]->get_friends_list();

      //notation: \t as tab characters. output the info
      oFile << id << std::endl << 
        "\t" << name << std::endl <<
        "\t" << year << std::endl <<
        "\t" << zip << std::endl << "\t";

      for (int j = 0; j < friends.size(); j++)
      {
        if (j == (friends.size() - 1))
          oFile << friends[j];
        else
          oFile << friends[j] << " ";
      }
      oFile << std::endl;
    }

    oFile.close();
    return 0;
  }

  void Network::add_user(std::string name, int yr, int zipcode) {
    //adding a user just pushes the user into the userList
    nUser = new User(name, yr, zipcode);
      //note dynamic allocation: must deallocate user_list later
    user_list.push_back(nUser);
  }

  int Network::add_connection(std::string name1, std::string name2) {
    int id_user1 = -1, id_user2 = -1; //set to -1 for error checking

    for (unsigned int i = 0; i < user_list.size(); i++)
    {
      if (user_list[i]->get_name() == name1)
        id_user1 = i;

      else if (user_list[i]->get_name() == name2)
        id_user2 = i;
    }

    if ((id_user1 == -1) || (id_user2 == -1)) { 
      std::cout << "User not found." << std::endl; 
      return -1; 
    }
    else
    {
      //if the users are found, add them both friends
      user_list[id_user1]->add_friend(id_user2);
      user_list[id_user2]->add_friend(id_user1);
      return 0;
    }
  }
  
  int Network::remove_connection(std::string name1, std::string name2) {
    //same processes as adding friends, just using delete_friend instead
    int id_user1 = -1, id_user2 = -1;

    for (unsigned int i = 0; i < user_list.size(); i++) {
      if (user_list[i]->get_name() == name1)
        id_user1 = i;
      if (user_list[i]->get_name() == name2)
        id_user2 = i;
    }

    if ( (id_user1 == -1) || (id_user2 == -1) ) { 
      std::cout << "User not found." << std::endl; 
      return -1;
    }
    else {
      user_list[id_user1]->delete_friend(id_user2);
      user_list[id_user2]->delete_friend(id_user1);
      return 0;
    }
  }

  int Network::get_id(std::string name) {
    //iterate through the list & retrieve the id
    for (unsigned int i = 0; i < user_list.size(); i++) {
      if (user_list[i]->get_name() == name) 
        return i;
    }
    std::cout << "User not found." << std::endl;
    return -1;
  }

  
  void Network::get_user_list() {
    //std left ensures a left output.
    //setw to adjust spacing
    std::cout << std::left <<
    std::setw(7) << "ID" <<
    std::setw(15) << "Name" <<
    std::setw(7) << "Year" <<
    std::setw(10) << "Zip" << std::endl;
    std::cout << "================================================" << std::endl;
    
  
    for (unsigned int i = 0; i < user_list.size(); i++) {
      int id = i; // id shows as 1. 
      if (id > 10) 
        //must adjust format for two digit numbers 
        std::cout << std::left << id << std::setw(5) << ".";
      else
        std::cout << std::left << id << std::setw(6) << ".";

      std::string name = user_list[i]->get_name();
      std::cout << std::left << std::setw(15) << name;
      
      int year = user_list[i]->get_year();
      std::cout << std::left << std::setw(7) << year;

      int zip = user_list[i]->get_zip();
      std::cout << std::left << std::setw(10) << zip << std::endl;
    }
  }

  void Network::get_friends_list(std::string name) {
    bool check = false; //bool to check if user exists
    vector<int> friends;
    std::cout << std::left <<
    std::setw(7) << "ID" <<
    std::setw(15) << "Name" <<
    std::setw(7) <<"Year" <<
    std::setw(10) << "Zip" << std::endl;
    std::cout << "================================================" << std::endl;
    for (unsigned int i = 0; i < user_list.size(); i++)
    {
      if (user_list[i]->get_name() == name) {
        friends = user_list[i]->get_friends_list();
        check = true;  //we found a user in the list!
      }
    }

    if (check == false) {
    std::cerr << "Error, user cannot be found";

    }
    

    for (unsigned int j = 0;  j < friends.size(); j++)
    {
      std::string username = user_list[friends[j]]->get_name();
      int id = get_id(username);
  
      if (id > 10)
        std::cout << std::left << id << std::setw(5) << ".";
      else
        std::cout << std::left << id << std::setw(6) << ".";
      
      std::cout << std::left << std::setw(15) << name;
      
      int year = user_list[friends[j]]->get_year();
      std::cout << std::left << std::setw(7) << year;

      int zip = user_list[friends[j]]->get_zip();
      std::cout << std::left << std::setw(10) << zip << std::endl;
    }
  }