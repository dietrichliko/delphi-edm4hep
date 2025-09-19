#pragma once

namespace phdst
{
    extern "C" struct
    {
        int nwpilt;
        int iupilt[1024];
    } pxchdr_;

    inline int &NWPILT = pxchdr_.nwpilt;
    inline int &NPILOT = pxchdr_.nwpilt;
    inline int &IUPILT(int i) { return pxchdr_.iupilt[i - 1]; }
    inline int &IPILOT(int i) { return pxchdr_.iupilt[i - 1]; }
} // namespace phdst