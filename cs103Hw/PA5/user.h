/*Name: Jacob Pitts
Program Info:
  user.h: defines the user header
  which contains the public and private
  members of the user class:

	contains public class:
		User construction
		User deconstruction
		add_friend
		delete_friend

		accessors for...
			year, username, zip, friendslist
		mutators for..
			name, year, zip 
	
	contains private class:
		year, username, zip, friendslist
*/

#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class User {
 public: 
   User();
   User(string name, int year, int zip);
   ~User();

   void add_friend(int user_id);
   void delete_friend(int user_id);

   // accessors
   string get_name();
   int get_year();
   int get_zip();
   vector<int> get_friends_list();

   // mutators
   void set_name(string name);
   void set_year(int year);
   void set_zip(int zip);

 private:
   int user_year;
   string user_name;
   int user_zip;
   vector<int> id_friends;	
};


#endif