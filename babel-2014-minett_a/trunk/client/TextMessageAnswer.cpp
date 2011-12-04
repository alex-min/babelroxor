#include "TextMessageAnswer.h"
#include "ListenServer.h"

TextMessageAnswer::TextMessageAnswer()
{

}

void    TextMessageAnswer::onCall(Network *network, std::string const & login, void *data, unsigned int len,
                       Protocol::NetworkPacket::NetworkHeader *header)
{
    if (!network || login == "" || !data || len <= 0 || !header)
        return ;
    std::cout << "TEXTMESSAGEANSWER !!!" << std::endl;

    std::string text = static_cast<char*>(data);

    text.resize(len);

    ListenServerSingleton::getInstance()->emitTextMessageChanged(text);
}
