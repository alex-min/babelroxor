#include "contactlist.h"
#include "account.h"

ContactList::ContactList()
{

}


ContactList::ContactList(std::list<Account*>   &contactList)
{
    _contactList = contactList;
}


void    ContactList::addContact(Account* account)
{
    _contactList.push_back(account);
}


void    ContactList::addContact(std::string const &login, std::string const &password)
{
    Account *account = new Account(login, password);

    _contactList.push_back(account);
}


Account const*    ContactList::getContactAt(int id) const
{
    std::list<Account*>::const_iterator it;
    int i = 0;

    for (it = _contactList.begin(); it != _contactList.end(); ++it)
        if (i++ == id)
            return (*it);

    return (0);
}


Account*    ContactList::getContactAt(int id)
{
    std::list<Account*>::iterator it;
    int i = 0;

    for (it = _contactList.begin(); it != _contactList.end(); ++it)
        if (i++ == id)
            return (*it);

    return (0);
}

Account const*  ContactList::getContactFromLogin(std::string const &login) const
{
    std::list<Account*>::const_iterator it;

    for (it = _contactList.begin(); it != _contactList.end(); ++it)
        if ((*it)->getLogin() == login)
            return (*it);

    return (0);
}

Account*    ContactList::getContactFromLogin(std::string const &login)
{
    std::list<Account*>::iterator it;

    for (it = _contactList.begin(); it != _contactList.end(); ++it)
        if ((*it)->getLogin() == login)
            return (*it);

    return (0);
}

bool    ContactList::removeAccount(Account* account)
{
    std::list<Account*>::iterator it;

    for (it = _contactList.begin(); it != _contactList.end(); ++it)
        if (*it == account)
        {
            it = _contactList.erase(it);
            delete account;

            return (true);
        }

    return (false);
}

bool    ContactList::removeAccountFromLogin(std::string const &login)
{
    std::list<Account*>::iterator it;

    for (it = _contactList.begin(); it != _contactList.end(); ++it)
        if ((*it)->getLogin() == login)
        {
            Account *account = *it;

            it = _contactList.erase(it);
            delete account;

            return (true);
        }

    return (false);
}

bool    ContactList::removeAccountAt(int id)
{
    std::list<Account*>::iterator it;
    int i = 0;

    for (it = _contactList.begin(); it != _contactList.end(); ++it)
        if (i++ == id)
        {
            Account *account = *it;

            it = _contactList.erase(it);
            delete account;

            return (true);
        }

    return (false);
}


ContactList::~ContactList()
{

}

