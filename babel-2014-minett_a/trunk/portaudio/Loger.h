
#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Singleton.h"
#include "FileName.h"

namespace Utils
{
  class LINK_OPTION_UTILS Loger : public Singleton<Loger>
  {
  public:
    static Loger	&Log(int status);

    // surcharge de l'operateur << permettant d'appeler la fonction
    // Write sur n'importe quel objet ayant defini la surcharge <<
    template<class T>
      Loger& operator << (const T &ToLog);
    friend Loger &operator << (Loger &out, std::ostream &(*f)(std::ostream &)) // permet de gerer le std::endl
    {
      std::ostringstream oss;

      f(oss);
      out.Write(oss.str(), true);
      return out;
    }

  protected:
    /*
      constructeur - destructeur
    */
    Loger();
    virtual ~Loger();

    virtual void CheckFile();					// ouverture du fichier, si ce n'est pas deja fait
    virtual void Write(const std::string msg, bool flush);	// effectue la loggisation dans le cout et le fichier

    std::ofstream	_file;
    FileName		_filename;
    static int		_status;		// status d'ecriture du logger (default = 0; error = 1; debug = 2)

    friend class Singleton<Loger>; // pour avoir acces a l'instance du singleton
  };

  template<class T>
    Loger &Loger::operator <<(const T& ToLog)
    {
      std::ostringstream s;

      s << ToLog;
      Write(s.str(), false);
      return *this;
    }
}

#endif // LOG_H_INCLUDED
