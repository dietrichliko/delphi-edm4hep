// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: Wrapper for PHDST Fortran library

#pragma once
#include <string>

namespace phdst {
    extern "C" void phdst_(char *, int *, int *, size_t);
    extern "C" void phset_(char *, int *, size_t);
    extern "C" void phpone_(char *, int *, size_t);
    extern "C" void phrty_(char *, size_t);
    extern "C" int iphpic_(char *, int *, size_t);
    extern "C" void timed_(float *);
    extern "C" void timex_(float *);

    /// @brief Run PHDST initializing and running the package
    /// @param options "" for normal operation, "L" for event lists, "C" for noop
    /// @return Status flag (0 = success)
    inline int PHDST(const std::string &options = "")
    {
        int flag;
        int dummy;
        // Fortran expects non-const char*, so we need to cast away constness
        phdst_(const_cast<char *>(options.c_str()), &dummy, &flag, options.size());
        return flag;
    }

    /// @brief Set PHDST options
    /// @param name for options (See PHDST manual for details)
    /// @return value of the option 
    inline void PHSET(const std::string &name, int value)
    {
        // Fortran expects non-const char*, so we need to cast away constness
        phset_(const_cast<char *>(name.c_str()), &value, name.size());
    }

    /// @brief Execute PDL by user call
    /// @param line pdl declaration line
    /// @return flag (0 = success, -1 = continue, = 1 error)
    inline int PHPONE(const std::string &line)
    {
        int flag;
        // Fortran expects non-const char*, so we need to cast away constness
        phpone_(const_cast<char *>(line.c_str()), &flag, line.size());
        return flag;
    }
    
    /// @brief Get the DST record type
    /// @return run type string (e.g. "DST"). Check manual for other values.
    inline std::string PHRTY()
    {
        constexpr int max_len = 4;
        char name[max_len + 1] = {}; // extra byte for safety
        int len = max_len;
        phrty_(name, len);

        // strip blanks
        while (len > 0 && name[len - 1] == ' ')
        {
            len--;
        }

        return std::string(name, len);
    }

    /// @brief Search blocklet in pilot record by name
    /// @param name name of the picture (e.g. "EVT")
    /// @return address of the found blocklet in the pilot in such way that IPILOT(IADDR+1) = NBwords 
    ///         -1 if not found, -13 other error
    inline int IPHPIC(const std::string &name)
    {
        int dummy;
        return iphpic_(const_cast<char *>(name.c_str()), &dummy, name.size());
    }

    /// @brief Get the current time in seconds since some epoch
    /// @param time variable to store the time
    inline void TIMED(float &time)
    {
        timed_(&time);
    }
    /// @brief Get the current CPU time in seconds since some epoch
    /// @param time variable to store the time
    inline void TIMEX(float &time)
    {
        timex_(&time);
    }
}
