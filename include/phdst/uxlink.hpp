#pragma once

namespace phdst
{
    extern "C" struct
    {
        int ltemp;
        int lrtop;
        int lstop;
        int lttop;
        int litop;
        int lrtemp;
        int lrwtmp;
        int lrawux;
        int lbktop;
        int lortop;
        int lrtint;
        int ldtop;
    } uxlink_;

    inline int &LTEMP = uxlink_.ltemp;
    inline int &LRTOP = uxlink_.lrtop;
    inline int &LSTOP = uxlink_.lstop;
    inline int &LTTOP = uxlink_.lttop;
    inline int &LITOP = uxlink_.litop;
    inline int &LRTEMP = uxlink_.lrtemp;
    inline int &LRWTMP = uxlink_.lrwtmp;
    inline int &LRAWUX = uxlink_.lrawux;
    inline int &LBKTOP = uxlink_.lbktop;
    inline int &LORTOP = uxlink_.lortop;
    inline int &LRTINT = uxlink_.lrtint;
    inline int &LDTOP = uxlink_.ldtop;
} // namespace phdst