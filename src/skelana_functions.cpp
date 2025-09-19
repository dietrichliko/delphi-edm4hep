#include "skelana/functions.hpp"
#include "skelana/pscflg.hpp"
#include <map>
#include <stdexcept>

namespace skelana
{
    void SET_FLAG(const std::string &options, int value)
    {
        inline static std::map<std::string, int*> option_map =  {
            {"IFLTRA", &pscflg_.ifltra},
            {"IFLFIX", &pscflg_.iflfix},
            {"IFLRNQ", &pscflg_.iflrnq},
            {"IFLSTR", &pscflg_.iflstr},
            {"IFLJET", &pscflg_.ifljet},
            {"IFLSIM", &pscflg_.iflsim},
            {"IFLBSP", &pscflg_.iflbsp},
            {"IFLBTG", &pscflg_.iflbtg},
            {"IFLEMC", &pscflg_.iflemc},
            {"IFLHAC", &pscflg_.iflhac},
            {"IFLSTC", &pscflg_.iflstc},
            {"IFLELE", &pscflg_.iflele},
            {"IFLPHO", &pscflg_.iflpho},
            {"IFLMUO", &pscflg_.iflmuo},
            {"IFLHAD", &pscflg_.iflhad},
            {"IFLVDH", &pscflg_.iflvdh},
            {"IFLRV0", &pscflg_.iflrv0},
            {"IFLUTE", &pscflg_.iflute},
            {"IFLPHC", &pscflg_.iflphc},
            {"IFLVEC", &pscflg_.iflvec},
            {"IFLBHP", &pscflg_.iflbhp},
            {"IFLECL", &pscflg_.iflecl},
            {"IFLRVR", &pscflg_.iflrvr},
            {"IFLODR", &pscflg_.iflodr},
            {"IFLPVT", &pscflg_.iflpvt},
            {"IFLCUT", &pscflg_.iflcut},
            {"IFLVDR", &pscflg_.iflvdr},
            {"IFLFCT", &pscflg_.iflfct},
            {"IFLENR", &pscflg_.iflenr}
        };
        auto it = option_map.find(options);
        if (it != option_map.end()) {
            *(it->second) = value;
        } else {
            throw std::invalid_argument("Unknown option: " + options);
        
    }
}
