#include "skelana/functions.hpp"
#include "skelana/pscflg.hpp"
#include <map>
#include <stdexcept>

namespace skelana
{
    void SET_FLAG(const std::string &options, int value)
    {
        static std::map<std::string, int*> option_map =  {
            {"IFLTRA", &pscflg_.ifltra},
            {"IFLODR", &pscflg_.iflodr},
            {"IFLVEC", &pscflg_.iflvec},
            {"IFLSTR", &pscflg_.iflstr},
            {"IFLCUT", &pscflg_.iflcut},
            {"IFLRVR", &pscflg_.iflrvr},
            {"IFLSIM", &pscflg_.iflsim},
            {"IFLBSP", &pscflg_.iflbsp},
            {"IFLBTG", &pscflg_.iflbtg},
            {"IFLPVT", &pscflg_.iflpvt},
            {"IFLVDR", &pscflg_.iflvdr},
            {"IFLFCT", &pscflg_.iflfct},
            {"IFLRNQ", &pscflg_.iflrnq},
            {"IFLBHP", &pscflg_.iflbhp},
            {"IFLUTE", &pscflg_.iflute},
            {"IFLVDH", &pscflg_.iflvdh},
            {"IFLMUO", &pscflg_.iflmuo},
            {"IFLECL", &pscflg_.iflecl},
            {"IFLELE", &pscflg_.iflele},
            {"IFLEMC", &pscflg_.iflemc},
            {"IFLPHO", &pscflg_.iflpho},
            {"IFLPHC", &pscflg_.iflphc},
            {"IFLSTC", &pscflg_.iflstc},
            {"IFLHAC", &pscflg_.iflhac},
            {"IFLHAD", &pscflg_.iflhad},
            {"IFLRV0", &pscflg_.iflrv0},
            {"IFLJET", &pscflg_.ifljet}
        };
        auto it = option_map.find(options);
        if (it != option_map.end()) {
            *(it->second) = value;
        } else {
            throw std::invalid_argument("Unknown option: " + options);
        }
    }
}
