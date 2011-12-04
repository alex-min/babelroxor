#include "TextMessage.h"

TextMessage::TextMessage()
{

}

void    TextMessage::sendTextMessage(std::string const &login, std::string const &text)
{
    std::cout << "Message sent: " << text << std::endl;

    Protocol::getInstance()->send(login, Protocol::TEXT, text.c_str(), text.length(), false);
}

TextMessage::~TextMessage()
{

}

