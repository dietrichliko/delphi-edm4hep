#pragma once

namespace skelana
{
    inline const int NVMAX = 511;
    extern "C" struct
    {
        int npa;
        int nst;
        int nsh;
        int nlu;
        int ishst[NVMAX];
        int istsh[NVMAX];
        int istpa[NVMAX];
        int ipast[NVMAX];
        int ishlu[NVMAX];
        int llush[NVMAX];
        int ilust[NVMAX];
        int istlu[NVMAX];
        int ipapv[NVMAX][2];
        int istvx[NVMAX][2];
    } psctbl_;

    inline int &NPA = psctbl_.npa;
    inline int &NST = psctbl_.nst;
    inline int &NSH = psctbl_.nsh;
    inline int &NLU = psctbl_.nlu;
    inline int &ISHST(int i) { return psctbl_.ishst[i - 1]; }
    inline int &ISTSH(int i) { return psctbl_.istsh[i - 1]; }
    inline int &ISTPA(int i) { return psctbl_.istpa[i - 1]; }
    inline int &IPAST(int i) { return psctbl_.ipast[i - 1]; }
    inline int &ISHLU(int i) { return psctbl_.ishlu[i - 1]; }
    inline int &LLUSH(int i) { return psctbl_.llush[i - 1]; }
    inline int &ILUST(int i) { return psctbl_.ilust[i - 1]; }
    inline int &ISTLU(int i) { return psctbl_.istlu[i - 1]; }
    inline int &IPAPV(int i, int j) { return psctbl_.ipapv[j - 1][i - 1]; }
    inline int &ISTVX(int i, int j) { return psctbl_.istvx[j - 1][i - 1]; }

} // namespace skelana