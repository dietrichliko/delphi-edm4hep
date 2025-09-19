#pragma once

namespace phdst
{
    extern "C" struct
    {
        int lundst;
        int lunstr;
        int lunlog;
        int luntty;
        int lunhst;
        int lunhbo;
        int lunpdl;
        int lundsc;
        int lunptr[10];
        int lunfat;
        int lunfan;
        int lunzip;
    } phlun_;

    inline int &LUNDST = phlun_.lundst;
    inline int &LUNSTR = phlun_.lunstr;
    inline int &LUNLOG = phlun_.lunlog;
    inline int &LUNTTY = phlun_.luntty;
    inline int &LUNHST = phlun_.lunhst;
    inline int &LUNHBO = phlun_.lunhbo;
    inline int &LUNPDL = phlun_.lunpdl;
    inline int &LUNDSC = phlun_.lundsc;
    inline int &LUNPTR(int i) { return phlun_.lunptr[i]; }
    inline int &LUNFAT = phlun_.lunfat;
    inline int &LUNFAN = phlun_.lunfan;
    inline int &LUNZIP = phlun_.lunzip;
} // namespace phdst   