/*Name: Jacob Pitts
Program Info:
  network.h: defines the network header
  which contains the public and private
  members of the network class:
*/

#ifndef NETWORK_H
#define NETWORK_H
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include "user.h"
#include <sstream>

class Network {
 public:
  Network();
  ~Network();
  int read_friends(const char *filename);
  int write_friends(const char *filename);
  void add_user(std::string username, int yr, int zipcode);
  int add_connection(std::string name1, std::string name2);
  int remove_connection(std::string name1, std::string name2);
  int get_id(std::string username);
  void get_user_list();
  void get_friends_list(std::string username);

 private:
   User* nUser;
   vector<User*> user_list;
};


#endif