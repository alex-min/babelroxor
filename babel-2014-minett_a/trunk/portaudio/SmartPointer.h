
#ifndef UTILS_SMART_POINTER_H_
#define UTILS_SMART_POINTER_H_

#include <typeinfo>
#include "Config.h"
#include "Exception.h"

namespace Utils
{
    template<typename T, bool IsArray>
    class NoDestroyableSmartPointer;
    //TODO : gestion des ptr NULL, pour le moment on throw une exception, mais boost ne throw jamais pour avoir un truc truc thread safe
    // voir comment BOOST fait
    template<typename T, bool IsArray = false>
    class SmartPointer
    {
        public:
            SmartPointer(T *ptr = 0, bool destroyable = true);
            SmartPointer(const SmartPointer &sp);
            virtual ~SmartPointer();

            /// operator
            SmartPointer    &operator = (const SmartPointer &sp);
            bool            operator == (const SmartPointer &sp) const;
            bool            operator != (const SmartPointer &sp) const;
            T               &operator * () const;
            T               *operator ->() const;

            friend std::ostream &operator << (std::ostream &os, const SmartPointer &sp)
            {
                os << sp._ptr;
                return os;
            }

            /// Accesseurs
            inline T        *Get() const    {return _ptr;}
            inline bool     Unique() const  {return ((*_nbRef) == 1);}

            /// modificateurs
            void                    Swap(SmartPointer &sp);
            inline SmartPointer     CloneNoDestroyable() const {return SmartPointer<T,IsArray>(_ptr, false);}

        protected:
            void Release();
            virtual void AddRefPtr() const  {}
            virtual void ReleasePtr()       {if (IsArray) delete[] _ptr; else delete _ptr;}

            T               *_ptr;
            unsigned int    *_nbRef;
            bool            _destroyable;
    };

    template<typename T, bool isArray>
    SmartPointer<T,isArray>::SmartPointer(T *ptr, bool destroyable)
    {
        _nbRef = new unsigned int;
        *_nbRef = 1;
        _ptr = ptr;
        _destroyable = destroyable;
        //std::cout << "construction\tshared : " << _nbRef << "\tptr : " << _ptr << "\tNB Ref = " << *_nbRef << std::endl;
    }

    template<typename T, bool isArray>
    SmartPointer<T,isArray>::SmartPointer(const SmartPointer &sp)
    {
        _nbRef = sp._nbRef;
        if (_nbRef != NULL)
            ++(*_nbRef);
        _ptr = sp._ptr;
        _destroyable = sp._destroyable;
        //std::cout << "construction\tshared : " << _nbRef << "\tptr : " << _ptr << "\tNB Ref = " << *_nbRef << std::endl;
    }

    template<typename T, bool isArray>
    SmartPointer<T,isArray>::~SmartPointer()
    {
        Release();
    }

    template<typename T, bool isArray>
    SmartPointer<T,isArray>    &SmartPointer<T,isArray>::operator = (const SmartPointer &sp)
    {
        _destroyable = sp._destroyable;
        if (_nbRef != sp._nbRef)
        {
            Release();
            _ptr = sp._ptr;
            _nbRef = sp._nbRef;
            if (_nbRef != NULL)
                ++(*_nbRef);
            if (_ptr != NULL)
                AddRefPtr();
        }
        //std::cout << "construction\tshared : " << _nbRef << "\tptr : " << _ptr << "\tNB Ref = " << *_nbRef << std::endl;
        return *this;
    }

    template<typename T, bool isArray>
    void SmartPointer<T,isArray>::Release()
    {
        if (_nbRef != NULL)
        {
            --(*_nbRef);
            //std::cout << "destruction\tshared : " << _nbRef << "\tptr : " << _ptr << "\tNB Ref = " << *_nbRef << std::endl;
            if (*_nbRef == 0)
            {
                delete _nbRef;
                if (_ptr != NULL && _destroyable)
                    ReleasePtr();
                _nbRef = NULL;
                _ptr = NULL;
            }
        }
    }

    template<typename T, bool isArray>
    bool SmartPointer<T,isArray>::operator != (const SmartPointer<T,isArray> &sp) const
    {
        return (_ptr != sp._ptr);
    }

    template<typename T, bool isArray>
    bool SmartPointer<T,isArray>::operator == (const SmartPointer<T,isArray> &sp) const
    {
        return (_ptr == sp._ptr);
    }

    template<typename T, bool isArray>
    T    &SmartPointer<T,isArray>::operator * () const
    {
        if (_ptr == NULL)
            throw Exception("SmartPointer operator*: The pointer of type " + std::string(typeid(*_ptr).name()) + " is NULL");
        return *_ptr;
    }

    template<typename T, bool isArray>
    T    *SmartPointer<T,isArray>::operator ->() const
    {
        if (_ptr == NULL)
            throw Exception("SmartPointer operator->: The pointer of type " + std::string(typeid(*_ptr).name()) + " is NULL");
        return _ptr;
    }

    template<typename T, bool isArray>
    void SmartPointer<T,isArray>::Swap(SmartPointer &sp)
    {
        unsigned int    *tmpNbRef = sp._nbRef;
        T               *tmpPtr = sp._ptr;

        sp._nbRef = _nbRef;
        sp._ptr = _ptr;
        _nbRef = tmpNbRef;
        _ptr = tmpPtr;
    }
}

#endif
