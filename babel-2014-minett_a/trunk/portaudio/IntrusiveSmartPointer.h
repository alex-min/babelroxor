
#ifndef UTILS_INTRUSIVESMART_POINTER_H_
#define UTILS_INTRUSIVESMART_POINTER_H_

#include "Config.h"
#include "SmartPointer.h"

namespace Utils
{
    template<typename T, bool IsArray = false>
    class IntrusiveSmartPointer : public SmartPointer<T, IsArray>
    {
        public:
            IntrusiveSmartPointer(T *ptr = 0, bool destroyable = true) : SmartPointer<T,IsArray>::SmartPointer(ptr, destroyable)
            {
                if (SmartPointer<T,IsArray>::_ptr != NULL)
                    AddRefPtr();
            }
            IntrusiveSmartPointer(const IntrusiveSmartPointer &sp) : SmartPointer<T,IsArray>::SmartPointer(sp)
            {
                if (SmartPointer<T,IsArray>::_ptr != NULL)
                    AddRefPtr();
            }

            inline IntrusiveSmartPointer   CloneNoDestroyable() const  {return IntrusiveSmartPointer(SmartPointer<T,IsArray>::_ptr, false);}

        protected:
            virtual void AddRefPtr()    {SmartPointer<T>::_ptr->SPAddRef(this);}
    };
}

#endif
