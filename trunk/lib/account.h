#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>

class ContactList;

class   Account
{
public:
    Account();
    Account(std::string const &login, std::string const &password, ContactList *contactList = 0);
    std::string const & getLogin() const;
    std::string const & getPassword() const;
    ContactList const*        getContacts() const;
    ContactList*        getContacts();
    void                setLogin(std::string const &login);
    void                setPassword(std::string const &password);
    void                setContact(ContactList *contactList);
    ~Account();

private:
    std::string _login;
    std::string _password;
    ContactList *_contactList;
};

#endif // ACCOUNT_H
