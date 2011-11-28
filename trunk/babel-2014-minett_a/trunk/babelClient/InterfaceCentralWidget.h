#ifndef INTERFACECENTRALWIDGET_H
#define INTERFACECENTRALWIDGET_H

#include <iostream>

namespace Graphic
{
class InterfaceCentralWidget
{
public:
    virtual void    callClient(std::string const &login) = 0;
    virtual void    hangUpClient(std::string const &login) = 0;
};
}

#endif // INTERFACECENTRALWIDGET_H
