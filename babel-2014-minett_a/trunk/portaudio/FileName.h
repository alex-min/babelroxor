
#ifndef FILENAME_H_INCLUDED
#define FILENAME_H_INCLUDED

#include <string>
#include "Config.h"

namespace Utils
{
    class LINK_OPTION_UTILS FileName
    {
        public:
        /*
	      constructeurs et operateur
	    */
            FileName(const std::string& aPath = "");
            FileName(const char* aPath);

            FileName	&operator = (const FileName& f);
            bool	    operator == (const FileName& f) const;

            friend std::ostream& operator << (std::ostream& os, const FileName& f)
            {
                os << "Filename : " << f._path;
                return os;
            }

        /*
	      Accesseurs
	    */
	    // nom complet
            inline operator const std::string & () const		        {return _path;}	    // operateur de cast en string
            inline void		    Fullname(const std::string& aPath)	    {_path = aPath;}
            inline std::string	Fullname() const			            {return _path;}

	    // partie du nom
            std::string		Path() const;			// chemin du fichier
            std::string		Filename() const;		// nom + extension
            void		    SetFilename(std::string s);
            std::string		ShortFilename() const;		// nom seul
            std::string		Extension() const;		// extension seul

	    // Accessibilite du fichier
            bool		IsReadable() const;

        private:
            std::string		_path;  // chemin complet (url+NomFichier+extention)
    };
}

#endif // UFILENAME_H_INCLUDED
