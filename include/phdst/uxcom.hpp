#pragma once

namespace phdst
{
    struct uxcom_t
    {
        int uxfenv[10];
        int luxstr[30];
        int luxref[30];
    }; 
    
    extern "C" uxcom_t uxcom_;

    inline int &LQ(int i) { return uxcom_.luxstr[i - 1]; }
    inline int &IQ(int i) { return uxcom_.luxstr[i + 7]; }
    inline float &Q(int i) { return *reinterpret_cast<float *>(&uxcom_.luxstr[i + 7]); }
} // namespace phdst