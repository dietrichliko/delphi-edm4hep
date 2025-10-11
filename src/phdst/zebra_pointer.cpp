// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: ZebraPointer implementation

#include "phdst/zebra_pointer.hpp"
#include <stdexcept>
#include <functional>

namespace phdst
{
    // Initialize static registry counter
    int ZebraPointer::registry_count_ = 0;
    
    void ZebraPointer::initialize()
    {
        // Call Fortran initialization routine
        // This sets up the common block and declares it to Zebra
        zebptrini_();
    }
    
    int ZebraPointer::find_or_add_link(int zebra_link)
    {
        // Search for existing entry in the Fortran common block
        for (int i = 0; i < registry_count_; ++i) {
            if (zeblll_.lzebptr[i] == zebra_link) {
                // Found existing entry, return its index
                return i;
            }
        }
        
        // Not found, add new entry if there's space
        if (registry_count_ >= MXZEBPTR) {
            throw std::runtime_error("ZebraPointer: Registry full - cannot add more links");
        }
        
        // Add new entry
        zeblll_.lzebptr[registry_count_] = zebra_link;
        return registry_count_++;
    }
    
    ZebraPointer ZebraPointer::create_impl(int zebra_link)
    {
        int index = find_or_add_link(zebra_link);
        return ZebraPointer(index);
    }
    
    bool ZebraPointer::is_valid() const
    {
        return registry_index_ >= 0 && 
               registry_index_ < registry_count_;
    }
    
    int ZebraPointer::get_link() const
    {
        if (!is_valid()) {
            throw std::runtime_error("ZebraPointer: Invalid pointer - cannot get link");
        }
        return zeblll_.lzebptr[registry_index_];
    }
    
    int& ZebraPointer::int_at(int offset) const
    {
        if (!is_valid()) {
            throw std::runtime_error("ZebraPointer: Invalid pointer - cannot access int data");
        }
        
        int link = zeblll_.lzebptr[registry_index_];
        return IQ(link + offset);
    }
    
    float& ZebraPointer::float_at(int offset) const
    {
        if (!is_valid()) {
            throw std::runtime_error("ZebraPointer: Invalid pointer - cannot access float data");
        }
        
        int link = zeblll_.lzebptr[registry_index_];
        return Q(link + offset);
    }
    
    int ZebraPointer::link_at(int offset) const
    {
        if (!is_valid()) {
            throw std::runtime_error("ZebraPointer: Invalid pointer - cannot access link data");
        }
        
        int link = zeblll_.lzebptr[registry_index_];
        return LQ(link + offset);
    }
    
    ZebraPointer ZebraPointer::ptr_at(int offset) const
    {
        if (!is_valid()) {
            throw std::runtime_error("ZebraPointer: Invalid pointer - cannot access link data");
        }
        
        int link = zeblll_.lzebptr[registry_index_];
        int linked_bank = LQ(link + offset);
        
        // Check if the link is valid (non-zero)
        if (linked_bank == 0) {
            // Return invalid ZebraPointer for null links
            return ZebraPointer();
        }
        
        // Create and return ZebraPointer for the linked bank
        return ZebraPointer::create(linked_bank);
    }
    
    size_t ZebraPointer::registry_size()
    {
        return static_cast<size_t>(registry_count_);
    }
    
    void ZebraPointer::reset()
    {
        // Zero out the entire Fortran array using VZERO
        int length = MXZEBPTR;
        vzero_(zeblll_.lzebptr, &length);
        
        // Reset the registry counter
        registry_count_ = 0;
    }
    
    // Comparison operators implementation
    
    bool ZebraPointer::operator==(const ZebraPointer& other) const
    {
        // If both are invalid, they are equal
        if (!is_valid() && !other.is_valid()) {
            return true;
        }
        
        // If one is invalid and the other is not, they are not equal
        if (!is_valid() || !other.is_valid()) {
            return false;
        }
        
        // Both are valid, compare the actual link values
        return get_link() == other.get_link();
    }
    
    bool ZebraPointer::operator!=(const ZebraPointer& other) const
    {
        return !(*this == other);
    }
    
    bool ZebraPointer::operator<(const ZebraPointer& other) const
    {
        // Invalid pointers are "less than" valid pointers
        if (!is_valid() && other.is_valid()) {
            return true;
        }
        
        // Valid pointers are "greater than" invalid pointers
        if (is_valid() && !other.is_valid()) {
            return false;
        }
        
        // If both are invalid, they are equal (not less than)
        if (!is_valid() && !other.is_valid()) {
            return false;
        }
        
        // Both are valid, compare link values
        return get_link() < other.get_link();
    }
    
    size_t ZebraPointer::hash() const
    {
        if (!is_valid()) {
            return 0; // Consistent hash for invalid pointers
        }
        
        // Use std::hash for the link value
        return std::hash<int>{}(get_link());
    }

} // namespace phdst
