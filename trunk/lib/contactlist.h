#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <iostream>
#include <list>
#include <algorithm>

class Account;

class ContactList
{
public:
    ContactList();
    ContactList(std::list<Account*>   &contactList);
    void                addContact(Account* account);
    void                addContact(std::string const &login, std::string const &password);
    Account const*      getContactAt(int id) const;
    Account*            getContactAt(int id);
    Account const*      getContactFromLogin(std::string const &login) const;
    Account*            getContactFromLogin(std::string const &login);
    bool                removeAccount(Account* account);
    bool                removeAccountFromLogin(std::string const &login);
    bool                removeAccountAt(int id);
    ~ContactList();

private:
    std::list<Account*>       _contactList;
};

#endif // CONTACTLIST_H
