#include "contactListSaver.h"

ContactListSaver::ContactListSaver(const std::string &nameoffile)
{
    name = nameoffile;
}

ContactListSaver::~ContactListSaver()
{}

bool   ContactListSaver::LoadFile()
{
    std::ifstream	file(name.c_str(), std::ifstream::in);
    std::string		str;
    size_t		found;

    if (file)
        while (getline(file, str))
        {
            found = str.find(';');
            if (found != 0 && found != std::string::npos)
                users.push_back(str.substr(0, found));
            else
                std::cerr << "Syntax error in users file." << std::endl;
        }
    else
    {
        std::cerr << "Users file error." << std::endl;
        return (false);
    }
    return (true);
}

bool    ContactListSaver::IsRegistered(const std::string &name)
{
    std::list<std::string>::iterator it;

    for (it = users.begin() ; it != users.end(); ++it)
        if (name == *it)
            return (true);
    return (false);
}

bool    ContactListSaver::AddContact(const std::string &name)
{
    if (IsRegistered(name) == true)
        return (false);

    users.push_back(name);
    UpdateFile();

    return (true);
}

bool    ContactListSaver::RemoveContact(const std::string &name)
{
    std::list<std::string>::iterator it;

    for (it = users.begin() ; it != users.end(); ++it)
        if (name == *it)
        {
            users.erase(it);
            UpdateFile();

            return (true);
        }
    return (false);
}

bool    ContactListSaver::UpdateContact(const std::string &name, const std::string &new_name)
{
    std::list<std::string>::iterator it;

    for (it = users.begin() ; it != users.end(); ++it)
        if (name == *it)
        {
            users.erase(it);
            AddContact(new_name);
            UpdateFile();

            return (true);
        }

    return (false);
}

bool    ContactListSaver::UpdateFile()
{
    std::ofstream	file(name.c_str(), std::ios::out | std::ios::trunc);
    std::list<std::string>::iterator it;

    if (file)
    {
        for (it = users.begin() ; it != users.end(); ++it)
            file << *it << ";" << std::endl;
    }
    else
        return (false);

    return (true);
}

std::list<std::string> const	&ContactListSaver::getUsers()
{
    return (users);
}
