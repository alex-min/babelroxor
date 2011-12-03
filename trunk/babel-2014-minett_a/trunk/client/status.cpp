#include "status.h"

Status::AssocStatus Status::_statusTab[] =
{
    {0, Protocol::ONLINE},
    {1, Protocol::BUSY},
    {2, Protocol::OFFLINE},
    {3, Protocol::ONCALL},
    {4, Protocol::DISCONNECTED},
    {5, Protocol::NEED_REGISTRATION},
    {(int)(0), (Protocol::Status)(0)}
};

Status::Status()
{
    _currentStatus = Protocol::ONLINE;
}

void    Status::requestStatus(std::string const &login)
{
    std::cout << "requestStatus to add loginContact: " << login << std::endl;

    Protocol::getInstance()->send(login, Protocol::REQUEST_STATUS, "", 0, false);
}

void    Status::updateStatus(std::string const &login)
{
    Protocol::getInstance()->send(login, Protocol::STATUS, &_currentStatus, sizeof(Protocol::STATUS), false);
}

void    Status::updateStatus(int status, std::list<std::string> const &updateList)
{
    Protocol::Status stat = Protocol::OFFLINE;

    stat = Status::getProtocolStatusFromClientStatus(status);

    std::cout << "UPDATE STATUS" << std::endl;

    if (stat != (Protocol::Status)(-1))
    {
        _currentStatus = stat;
        for (std::list<std::string>::const_iterator it = updateList.begin(); it != updateList.end(); ++it)
            Protocol::getInstance()->send(*it, Protocol::STATUS, &stat, sizeof(Protocol::STATUS), false);
    }
}

void    Status::sendCallStatus(std::string const &login, int callStatus)
{
   Protocol::Status stat = Protocol::OK;

   if (!callStatus)
       stat = Protocol::FAILED;

    Protocol::getInstance()->send(login, Protocol::CALL, &stat, sizeof(Protocol::CALL), false);
}

Protocol::Status    Status::getProtocolStatusFromClientStatus(int status)
{
    for (int i = 0; i < STATUSTAB_SIZE; i++)
        if (_statusTab[i].status == status)
            return (_statusTab[i].statusProtocol);

    return ((Protocol::Status)(-1));
}

int                 Status::getClientStatusFromProtocolStatus(Protocol::Status status)
{
    for (int i = 0; i < STATUSTAB_SIZE; i++)
        if (_statusTab[i].statusProtocol == status)
            return (_statusTab[i].status);

    return (-1);
}

Status::~Status()
{

}
