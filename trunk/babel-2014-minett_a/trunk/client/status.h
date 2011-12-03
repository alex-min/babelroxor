#ifndef STATUS_H
#define STATUS_H

#include "singleton.h"
#include "protocol.h"
#include "StatusAnswer.h"

#define STATUSTAB_SIZE  (6)

class Status
{
public:
    struct AssocStatus
    {
        int status;

        Protocol::Status statusProtocol;
    };

    Status();
    static Protocol::Status    getProtocolStatusFromClientStatus(int status);
    static int                 getClientStatusFromProtocolStatus(Protocol::Status status);
    void    updateStatus(int status, std::list<std::string> const &updateList);
    void    updateStatus(std::string const &login);
    void    sendCallStatus(std::string const &login, int callStatus);
    void    requestStatus(std::string const &login);
    ~Status();

private:
    static AssocStatus  _statusTab[7];
    Protocol::Status    _currentStatus;
};

typedef Singleton<Status>   StatusSingleton;

#endif // STATUS_H
