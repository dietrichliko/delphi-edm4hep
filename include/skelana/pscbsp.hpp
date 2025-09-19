#pragma once

namespace skelana
{
/*    +KEEP,PSCBSP.            Beam spot coordinates
 */
    extern "C" struct
    {
        int ierrbs;
        float xyzbs[3];
        float dxyzbs[3];
    } pscbsp_;

    inline int &IERRBS = pscbsp_.ierrbs;
    inline float &XYZBS(int i) { return pscbsp_.xyzbs[i - 1]; }
    inline float &DXYZBS(int i) { return pscbsp_.dxyzbs[i - 1]; }
}