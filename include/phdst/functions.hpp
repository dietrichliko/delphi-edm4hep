#pragma once

#include <string>
#include <cstring>

namespace phdst
{
    extern "C" void phdst_(char *, int *, int *, size_t);
    extern "C" void phset_(char *, int *, size_t);
    extern "C" void phpone_(char *, int *, size_t);
    extern "C" void phrty_(char *, size_t);
    extern "C" int iphpic_(char *, int *, size_t);
    extern "C" void timed_(float *);
    extern "C" void timex_(float *);

    // Wrappers to use std::string instead of char*
    // and rvalue references for integers
    // to avoid unnecessary copies.
    // Note: the length of the string is passed as a separate argument
    // to comply with Fortran's calling convention for strings.

    inline int PHDST(const std::string &name)
    {
        int flag;
        int dummy;
        phdst_(const_cast<char *>(name.c_str()), &dummy, &flag, name.size());
        return flag;
    }

    inline void PHSET(const std::string &name, int &&n)
    {
        phset_(const_cast<char *>(name.c_str()), &n, name.size());
    }

    inline int PHPONE(const std::string &name)
    {
        int flag;
        phpone_(const_cast<char *>(name.c_str()), &flag, name.size());
        return flag;
    }

    inline std::string PHRTY()
    {
        char name[] = "1234";
        size_t len = 4;
        phrty_(name, len);

        // strip blanks
        while (len > 0 && name[len - 1] == ' ')
        {
            len--;
        }

        return std::string(name, len);
    }

    inline int IPHPIC(const std::string &name, int &&n)
    {
        return iphpic_(const_cast<char *>(name.c_str()), &n, name.size());
    }

    inline void TIMED(float &time)
    {
        timed_(&time);
    }

    inline void TIMEX(float &time)
    {
        timex_(&time);
    }
} // namespace phdst