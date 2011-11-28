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

}

void    Status::updateStatus(std::string const &login, int status)
{
    Protocol::Status stat = Protocol::NEED_REGISTRATION;

    stat = Status::getProtocolStatusFromClientStatus(status);

    if (stat != (Protocol::Status)(-1))
    {
        Protocol::getInstance()->send(login, Protocol::STATUS, &stat, sizeof(Protocol::STATUS));
    }
}

void    Status::sendCallStatus(std::string const &login, int callStatus)
{
   Protocol::Status stat = Protocol::OK;

   if (!callStatus)
       stat = Protocol::FAILED;

    Protocol::getInstance()->send(login, Protocol::CALL, &stat, sizeof(Protocol::CALL));
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
