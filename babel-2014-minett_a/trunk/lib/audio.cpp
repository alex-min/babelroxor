#include "audio.h"

Audio::Audio()
{
}

void    Audio::onCall(Network *network, std::string const & login, void *data, unsigned int len,
                      Protocol::NetworkPacket::NetworkHeader *header)
{
    std::cout << "Length : " << len << std::endl;
    std::cout << "Audio Packet received : " << std::string((char *) data, len) << std::endl;
    std::cout << "from " << login << std::endl;
    Protocol::getInstance()->send(login, Protocol::AUDIO, "test", 4, 4);
}
