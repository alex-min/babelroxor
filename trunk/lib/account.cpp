#include "account.h"
#include "contactlist.h"

Account::Account()
{
    _login = "";
    _password = "";
    _contactList = new ContactList;
}

Account::Account(const std::string &login, const std::string &password, ContactList *contactList)
{
    _login = login;
    _password = password;
    _contactList = ((contactList) ? (contactList) : (new ContactList));
}

std::string const & Account::getLogin() const
{
    return (_login);
}

std::string const & Account::getPassword() const
{
    return (_password);
}

void                Account::setLogin(std::string const &login)
{
    _login = login;
}

void                Account::setPassword(std::string const &password)
{
    _password = password;
}

ContactList const*        Account::getContacts() const
{
    return (_contactList);
}


ContactList*        Account::getContacts()
{
    return (_contactList);
}


void                Account::setContact(ContactList *contactList)
{
    _contactList = contactList;
}


Account::~Account()
{

}
