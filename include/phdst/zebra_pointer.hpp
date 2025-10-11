// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: ZebraPointer type for managing Zebra common block links

/**
 * @file zebra_pointer.hpp
 * @brief ZebraPointer type for efficient Zebra link management
 * 
 * This header provides the ZebraPointer class that manages Zebra common block
 * links through a centralized registry. Instead of storing the actual int-based
 * Zebra link directly, ZebraPointer stores only an index into a common registry,
 * reducing memory overhead and providing type-safe access to Zebra memory.
 * 
 * The ZebraPointer provides convenient member functions to access data at
 * specific offsets within the Zebra bank as integers, floats, or linked banks.
 * 
 * @par Usage Example:
 * @code
 * // Initialize the ZebraPointer system first
 * ZebraPointer::initialize();
 * 
 * // Create a ZebraPointer from a Zebra link
 * int zebra_link = LQ(some_index);
 * ZebraPointer ptr = ZebraPointer::create(zebra_link);
 * 
 * // Access data with offsets
 * int int_val = ptr.int_at(5);     // IQ(link+5)
 * float float_val = ptr.float_at(3); // Q(link+3)
 * 
 * // Access linked banks
 * int linked_bank = ptr.link_at(-1);  // LQ(link-1) - raw link value
 * ZebraPointer next_ptr = ptr.ptr_at(-1); // Direct ZebraPointer to linked bank
 * 
 * // Chain navigation using ptr_at
 * ZebraPointer child = ptr.ptr_at(2).ptr_at(1); // Navigate through structure
 * 
 * // Use in std::map (requires comparison operators)
 * std::map<ZebraPointer, int> zebra_map;
 * zebra_map[ptr] = 42;
 * 
 * // Use in std::unordered_map (requires hash function)
 * std::unordered_map<ZebraPointer, std::string> zebra_hash_map;
 * zebra_hash_map[ptr] = "some data";
 * @endcode
 */

#pragma once
#include "uxcom.hpp"
#include <stdexcept>
#include <cstddef>
#include <functional>
#include <type_traits>

namespace phdst
{
    /**
     * @brief Maximum number of ZebraPointer links that can be tracked
     * 
     * This must match the MXZEBPTR parameter in the Fortran common block.
     * Defines the maximum size of the registry stored in the /ZEBLLL/ common block.
     */
    constexpr int MXZEBPTR = 1000;
    
    /**
     * @brief Fortran common block /ZEBLLL/ declaration
     * 
     * External declaration for the Fortran common block that stores all
     * Zebra links referenced by ZebraPointer instances. This common block
     * is properly declared to the Zebra system using MZLINK.
     */
    extern "C" {
        extern struct {
            int lzebptr[MXZEBPTR];
        } zeblll_;
        
        /**
         * @brief Fortran initialization routine
         * 
         * This routine must be called before using any ZebraPointer objects.
         * It initializes the Fortran common block and declares it to Zebra
         * using MZLINK for proper memory management.
         */
        void zebptrini_();
        
        /**
         * @brief CERN library routine to zero memory
         * 
         * VZERO is a CERN library routine that zeros out an array.
         * Used to clear the ZebraPointer registry array.
         * 
         * @param array Pointer to the array to be zeroed
         * @param length Number of words to zero
         */
        void vzero_(int* array, int* length);
    }

    /**
     * @brief Efficient pointer type for Zebra common block links
     * 
     * ZebraPointer manages Zebra links through the Fortran common block /ZEBLLL/.
     * Instead of storing the actual int-based Zebra link (which could be 4 bytes),
     * it stores only an index into the Fortran registry, potentially reducing memory
     * usage when many pointers reference the same or similar Zebra links.
     * 
     * The class provides convenient access methods for reading data at specific
     * offsets within the Zebra bank, following the standard Zebra conventions
     * for data access through IQ, Q, and LQ arrays.
     * 
     * The registry is implemented as a Fortran common block (/ZEBLLL/) which is
     * properly declared to the Zebra system for memory management and garbage
     * collection purposes.
     * 
     * @important Call ZebraPointer::initialize() before using any ZebraPointer objects
     * 
     * @note All offset parameters use Fortran-style 1-based indexing to match
     *       the original Zebra conventions
     * @note The registry is thread-safe for read operations but not for
     *       concurrent modifications
     */
    class ZebraPointer
    {
    private:
        /**
         * @brief Index into the Fortran common block registry
         * 
         * This index references an entry in the /ZEBLLL/ Fortran common block
         * that contains the actual Zebra link value. Using an index instead of 
         * storing the link directly can reduce memory usage when multiple 
         * ZebraPointers reference the same link.
         */
        int registry_index_;
        
        /**
         * @brief Current number of entries in the registry
         * 
         * Tracks how many entries are currently stored in the Fortran common
         * block registry. This is used to manage the allocation of new entries.
         */
        static int registry_count_;
        
        /**
         * @brief Find or add a link to the Fortran registry
         * 
         * Searches the Fortran common block /ZEBLLL/ for an existing entry with 
         * the given Zebra link. If found, returns the index of the existing entry. 
         * If not found, adds the link to the registry and returns the new index.
         * 
         * @param zebra_link The Zebra link value to find or add
         * @return Index into the Fortran registry where the link is stored
         * @throws std::runtime_error if the registry is full (exceeds MXZEBPTR)
         * 
         * @note This method provides automatic deduplication of identical links
         * @note Registry indices are stable - once assigned, they never change
         * @note The registry is limited to MXZEBPTR entries (1000 by default)
         */
        static int find_or_add_link(int zebra_link);
        
    public:
        /**
         * @brief Default constructor creating an invalid pointer
         * 
         * Creates a ZebraPointer that doesn't reference any valid Zebra link.
         * This is useful for initialization and can be checked with is_valid().
         */
        ZebraPointer() : registry_index_(-1) {}
        
        /**
         * @brief Private constructor from registry index
         * 
         * Creates a ZebraPointer from a registry index. This is used internally
         * by the create() method and should not be called directly.
         * 
         * @param index Index into the static registry
         */
        explicit ZebraPointer(int index) : registry_index_(index) {}
        
        /**
         * @brief Initialize the ZebraPointer system
         * 
         * This method must be called before using any ZebraPointer objects.
         * It calls the Fortran initialization routine that sets up the common
         * block and declares it to the Zebra memory management system.
         * 
         * @note This is a wrapper around the Fortran ZEBPTRINI subroutine
         * @note Safe to call multiple times - initialization is idempotent
         */
        static void initialize();
        
        /**
         * @brief Create a ZebraPointer from a Zebra link
         * 
         * Factory method to create a ZebraPointer from an existing Zebra link.
         * The link is automatically added to the registry if not already present.
         * Accepts both signed and unsigned 32-bit integer types.
         * 
         * @tparam T Integer type (int32_t, uint32_t, int, unsigned int, etc.)
         * @param zebra_link The Zebra link value (typically from LQ array)
         * @return ZebraPointer object referencing the link
         * 
         * @par Example:
         * @code
         * int link = LQ(10);           // signed int
         * std::uint32_t ulink = LQ(20); // unsigned int
         * ZebraPointer ptr1 = ZebraPointer::create(link);   // works
         * ZebraPointer ptr2 = ZebraPointer::create(ulink);  // also works
         * @endcode
         */
        template<typename T>
        static ZebraPointer create(T zebra_link) {
            static_assert(std::is_integral_v<T> && sizeof(T) == 4, 
                         "ZebraPointer::create() requires a 32-bit integer type");
            return create_impl(static_cast<int>(zebra_link));
        }
        
    private:
        /**
         * @brief Internal implementation of create method
         * 
         * @param zebra_link The Zebra link value as signed int
         * @return ZebraPointer object referencing the link
         */
        static ZebraPointer create_impl(int zebra_link);
        
    public:
        
        /**
         * @brief Check if the pointer references a valid Zebra link
         * 
         * @return true if the pointer references a valid entry in the Fortran registry
         * @return false if the pointer is invalid (default-constructed)
         */
        bool is_valid() const;
        
        /**
         * @brief Get the underlying Zebra link value
         * 
         * Retrieves the actual Zebra link value from the Fortran registry.
         * This is useful when interfacing with legacy Fortran code that
         * expects raw integer link values.
         * 
         * @return The Zebra link value
         * @throws std::runtime_error if the pointer is invalid
         * 
         * @note Use is_valid() to check validity before calling this method
         */
        int get_link() const;
        
        /**
         * @brief Access integer data at specified offset
         * 
         * Provides access to integer data within the Zebra bank at the given
         * offset. This corresponds to accessing IQ(link + offset) in Fortran.
         * 
         * @param offset Offset from the base link (1-based Fortran indexing)
         * @return Reference to integer value at the specified offset
         * @throws std::runtime_error if the pointer is invalid
         * 
         * @par Example:
         * @code
         * ZebraPointer ptr = ZebraPointer::create(some_link);
         * int value = ptr.int_at(5);  // Equivalent to IQ(link+5)
         * @endcode
         * 
         * @note Uses 1-based indexing to match Fortran conventions
         * @note No bounds checking is performed on the offset
         */
        int& int_at(int offset) const;
        
        /**
         * @brief Access floating-point data at specified offset
         * 
         * Provides access to floating-point data within the Zebra bank at the 
         * given offset. This corresponds to accessing Q(link + offset) in Fortran.
         * 
         * @param offset Offset from the base link (1-based Fortran indexing)
         * @return Reference to float value at the specified offset
         * @throws std::runtime_error if the pointer is invalid
         * 
         * @par Example:
         * @code
         * ZebraPointer ptr = ZebraPointer::create(some_link);
         * float value = ptr.float_at(3);  // Equivalent to Q(link+3)
         * @endcode
         * 
         * @note Uses 1-based indexing to match Fortran conventions
         * @note No bounds checking is performed on the offset
         * @note Assumes IEEE754 float representation compatibility
         */
        float& float_at(int offset) const;
        
        /**
         * @brief Access linked bank at specified offset
         * 
         * Provides access to linked Zebra banks at the given offset. This
         * corresponds to accessing LQ(link + offset) in Fortran and returns
         * the link value to another Zebra bank.
         * 
         * @param offset Offset from the base link (1-based Fortran indexing)
         * @return Link value to another Zebra bank
         * @throws std::runtime_error if the pointer is invalid
         * 
         * @par Example:
         * @code
         * ZebraPointer ptr = ZebraPointer::create(some_link);
         * int linked_bank = ptr.link_at(-1);  // Equivalent to LQ(link-1)
         * ZebraPointer next_ptr = ZebraPointer::create(linked_bank);
         * @endcode
         * 
         * @note Uses 1-based indexing to match Fortran conventions
         * @note Negative offsets are commonly used for parent/control links
         * @note No bounds checking is performed on the offset
         */
        int link_at(int offset) const;
        
        /**
         * @brief Create ZebraPointer to linked bank at specified offset
         * 
         * Provides direct access to linked Zebra banks at the given offset as
         * a ZebraPointer object. This is equivalent to calling link_at() followed
         * by create(), but more convenient and type-safe.
         * 
         * @param offset Offset from the base link (1-based Fortran indexing)
         * @return ZebraPointer to the linked bank
         * @throws std::runtime_error if the pointer is invalid
         * @throws std::runtime_error if the linked bank value is zero (null link)
         * 
         * @par Example:
         * @code
         * ZebraPointer ptr = ZebraPointer::create(some_link);
         * ZebraPointer next_ptr = ptr.ptr_at(-1);  // Direct ZebraPointer to LQ(link-1)
         * @endcode
         * 
         * @note Uses 1-based indexing to match Fortran conventions
         * @note Negative offsets are commonly used for parent/control links
         * @note No bounds checking is performed on the offset
         * @note Returns invalid ZebraPointer if the link value is zero
         */
        ZebraPointer ptr_at(int offset) const;
        
        /**
         * @brief Get registry statistics
         * 
         * Returns the current number of entries in the Fortran registry. This can be 
         * useful for debugging and monitoring memory usage.
         * 
         * @return Number of entries currently in the Fortran registry
         */
        static size_t registry_size();
        
        /**
         * @brief Clear the registry (for testing/cleanup)
         * 
         * Resets the registry count to zero and zeros out the entire Fortran 
         * common block array using the CERN library routine VZERO. This 
         * invalidates all existing ZebraPointer objects and should only be 
         * used for testing or cleanup purposes.
         * 
         * @warning This method invalidates all existing ZebraPointer objects!
         * @note Use with extreme caution in production code
         * @note Clears the entire MXZEBPTR array using VZERO for proper cleanup
         */
        static void reset();
        
        // Comparison operators for std::map support
        
        /**
         * @brief Equality comparison operator
         * 
         * Two ZebraPointers are equal if they reference the same Zebra link.
         * Invalid pointers are only equal to other invalid pointers.
         * 
         * @param other ZebraPointer to compare with
         * @return true if both pointers reference the same link
         */
        bool operator==(const ZebraPointer& other) const;
        
        /**
         * @brief Inequality comparison operator
         * 
         * @param other ZebraPointer to compare with
         * @return true if pointers reference different links
         */
        bool operator!=(const ZebraPointer& other) const;
        
        /**
         * @brief Less-than comparison operator for std::map ordering
         * 
         * Provides strict weak ordering based on the underlying Zebra link values.
         * Invalid pointers are considered "less than" valid pointers.
         * 
         * @param other ZebraPointer to compare with
         * @return true if this pointer should be ordered before other
         */
        bool operator<(const ZebraPointer& other) const;
        
        /**
         * @brief Get hash value for std::unordered_map support
         * 
         * Returns a hash value based on the underlying Zebra link.
         * Invalid pointers return a consistent hash value (0).
         * 
         * @return Hash value suitable for std::unordered_map
         */
        size_t hash() const;
    };

} // namespace phdst

// Hash specialization for std::unordered_map support
namespace std {
    /**
     * @brief Hash specialization for ZebraPointer
     * 
     * Enables ZebraPointer to be used as a key in std::unordered_map.
     * The hash is based on the underlying Zebra link value.
     */
    template<>
    struct hash<phdst::ZebraPointer> {
        size_t operator()(const phdst::ZebraPointer& ptr) const {
            return ptr.hash();
        }
    };
}
