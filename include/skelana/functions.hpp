#pragma once
#include <string>

namespace skelana
{
    extern "C" void psini_();
    extern "C" void psbeg_();
    extern "C" void psrunq_(int *);
    extern "C" void psruns_(int *);
    extern "C" void psenrg_();
    extern "C" void psbhpc_();
    extern "C" void dstqid_(char *, size_t);

    void SET_FLAG(const std::string &options, int value);

    inline void PSINI() { psini_(); }
    inline void PSBEG() { psbeg_(); }
    inline void PSRUNQ(int &&n) { psrunq_(&n); }
    inline int PSRUNS()
    {
        int n;
        psruns_(&n);
        return n;
    }
    inline void PSENRG() { psenrg_(); }
    inline void PSBHPC() { psbhpc_(); }
    inline std::string DSTQID()
    {
        char name[] = "1234";
        size_t len = 4;
        dstqid_(name, len);

        // strip blanks
        while (len > 0 && name[len - 1] == ' ')
        {
            len--;
        }

        return std::string(name, len);
    }

 }
