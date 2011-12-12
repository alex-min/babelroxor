#ifndef CONTACTLISTSAVER_H
#define CONTACTLISTSAVER_H

#include <iostream>
#include <string>
#include <fstream>
#include <list>

class ContactListSaver
{
public:
    ContactListSaver(const std::string &nameoffile);
    ~ContactListSaver();
    bool	LoadFile();
    bool	IsRegistered(const std::string &name);
    bool	AddContact(const std::string &name);
    bool	RemoveContact(const std::string &name);
    bool	UpdateContact(const std::string &name, const std::string &new_name);
    std::list<std::string> const &getUsers();

private:
    std::string				file;
    std::string				name;
    std::list<std::string>               users;
    bool				UpdateFile();
};

#endif // CONTACTLISTSAVER_H
