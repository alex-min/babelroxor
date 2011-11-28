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
    void    updateStatus(std::string const &login, int status);
    void    sendCallStatus(std::string const &login, int callStatus);

    ~Status();

private:
    static AssocStatus  _statusTab[7];
};

typedef Singleton<Status>   StatusSingleton;

#endif // STATUS_H
