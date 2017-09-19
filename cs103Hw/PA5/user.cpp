/*Name: Jacob Pitts
Program Info:
  user.cpp: defines the actual
  functions that were prototyped in
  user.h.
*/

#include "user.h"
#include <iostream>
#include <string>

using std::string;
using std::vector;

  User::User() {
  }

  User::User(string name, int year, int zip) {
    set_name(name);
    set_year(year);
    set_zip(zip);
  }

  User::~User() {     
  }

  void User::add_friend(int id) {
    id_friends.push_back(id);
  }
  
  void User::delete_friend(int id) {
    for (unsigned int i = 0; i < id_friends.size(); i++) {
      if (id_friends[i] == id) 
        id_friends.erase(id_friends.begin() + i);
    }
  }
   
   
  string User::get_name() {
    return user_name;
  }
   
  int User::get_year() {
    return user_year;
  }
   
  int User::get_zip() {
    return user_zip;
  }
   
  vector<int> User::get_friends_list() {
    vector<int> friends;
    for (unsigned int i = 0; i < id_friends.size(); i++)
      friends.push_back(id_friends[i]); //get ids, push them into friends vector

    return friends;
  }


  void User::set_name(string name) {
    user_name = name;
  }
   
  void User::set_year(int year) {
    user_year = year;
  }
   
  void User::set_zip(int zip) {
    user_zip = zip;
  }