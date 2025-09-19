#pragma once

namespace phdst
{
    extern "C" struct
    {
        int phgfst;
        int nfzfil;
        int nfzpil;
        int nfzget;
        int nfzpix;
        int nfzgex;
        int nevent;
        int ngoods;
        int nevenx;
        int ngoodx;
        int intrct;
        float timtot;
        float timend;
        int maxpst;
        int limpsf;
        int lapstg;
        int nfilou;
        int ndssav[10];
        int packed;
        int ivpack;
        float filimt;
        int filacc;
        int stgputw;
        int sgnexit;
        int phglst;
    } phgen_;

    inline int &PHGFST = phgen_.phgfst;
    inline int &NFZFIL = phgen_.nfzfil;
    inline int &NFZPIL = phgen_.nfzpil;
    inline int &NFZGET = phgen_.nfzget;
    inline int &NFZPIX = phgen_.nfzpix;
    inline int &NFZGEX = phgen_.nfzgex;
    inline int &NEVENT = phgen_.nevent;
    inline int &NGOODS = phgen_.ngoods;
    inline int &NEVENX = phgen_.nevenx;
    inline int &NGOODX = phgen_.ngoodx;
    inline int &INTRCT = phgen_.intrct;
    inline float &TIMTOT = phgen_.timtot;
    inline float &TIMEND = phgen_.timend;
    inline int &MAXPST = phgen_.maxpst;
    inline int &LIMPSF = phgen_.limpsf;
    inline int &LAPSTG = phgen_.lapstg;
    inline int &NFILOU = phgen_.nfilou;
    inline int &NDSSAV(int i) { return phgen_.ndssav[i - 1]; }
    inline int &PACKED = phgen_.packed;
    inline int &IVPACK = phgen_.ivpack;
    inline float &FILIMT = phgen_.filimt;
    inline int &FILACC = phgen_.filacc;
    inline int &STGPUTW = phgen_.stgputw;
    inline int &SGNEXIT = phgen_.sgnexit;
    inline int &PHGLST = phgen_.phglst;   
} // namespace phdst

