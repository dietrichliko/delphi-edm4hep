// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: PHDST common block PHGEN wrapper

/**
 * @file phgen.hpp
 * @brief PHDST common block PHGEN for general control and statistics
 * 
 * This header provides C++ access to the PHDST Fortran common block PHGEN,
 * which contains general control variables, event counters, timing information,
 * and various flags used throughout the PHDST framework for event processing
 * and system management.
 * 
 * The PHGEN common block serves as the central control panel for PHDST
 * operations, containing counters for events processed, timing statistics,
 * file handling parameters, and system state flags.
 */

#pragma once

namespace phdst
{
    /**
     * @brief Fortran common block PHGEN structure
     * 
     * C structure mapping for the Fortran common block PHGEN.
     * This structure provides direct access to general control variables,
     * event counters, timing information, and system flags used by PHDST.
     * 
     * @note This structure maps directly to Fortran memory layout
     */
    extern "C" struct
    {
        int phgfst;      ///< First call flag for PHDST initialization
        int nfzfil;      ///< Number of FZ files processed
        int nfzpil;      ///< Number of FZ pilot records processed
        int nfzget;      ///< Number of FZ GET operations
        int nfzpix;      ///< Number of FZ PIX operations
        int nfzgex;      ///< Number of FZ GEX operations
        int nevent;      ///< Current event number being processed
        int ngoods;      ///< Number of good events processed successfully
        int nevenx;      ///< Extended/auxiliary event counter
        int ngoodx;      ///< Extended/auxiliary good event counter
        int intrct;      ///< Interactive mode flag
        float timtot;    ///< Total processing time
        float timend;    ///< End time marker
        int maxpst;      ///< Maximum number of post-processing steps
        int limpsf;      ///< Limit for post-processing flags
        int lapstg;      ///< Last post-processing stage
        int nfilou;      ///< Number of output files
        int ndssav[10];  ///< Array for saving DSS (Data Set Service) information
        int packed;      ///< Data packing flag
        int ivpack;      ///< Version of packing algorithm
        float filimt;    ///< File size limit
        int filacc;      ///< File access mode/counter
        int stgputw;     ///< Stage PUT word counter
        int sgnexit;     ///< Signal exit flag
        int phglst;      ///< PHDST last operation flag
    } phgen_;

    /**
     * @brief Reference to first call initialization flag
     * 
     * Flag indicating whether PHDST has been initialized. Typically set
     * during the first call to PHDST initialization routines.
     */
    inline int &PHGFST = phgen_.phgfst;
    
    /**
     * @brief Reference to FZ file counter
     * 
     * Counter for the number of FZ (Fortran Z) files that have been
     * processed during the current PHDST session.
     */
    inline int &NFZFIL = phgen_.nfzfil;
    
    /**
     * @brief Reference to FZ pilot record counter
     * 
     * Counter for the number of FZ pilot records processed. Pilot records
     * contain event header information used for event selection.
     */
    inline int &NFZPIL = phgen_.nfzpil;
    
    /**
     * @brief Reference to FZ GET operation counter
     * 
     * Counter for the number of FZ GET operations performed to read
     * data from FZ files.
     */
    inline int &NFZGET = phgen_.nfzget;
    
    /**
     * @brief Reference to FZ PIX operation counter
     * 
     * Counter for the number of FZ PIX (Pixel/Picture) operations
     * performed during data processing.
     */
    inline int &NFZPIX = phgen_.nfzpix;
    
    /**
     * @brief Reference to FZ GEX operation counter
     * 
     * Counter for the number of FZ GEX (Get Extended) operations
     * performed during data processing.
     */
    inline int &NFZGEX = phgen_.nfzgex;
    
    /**
     * @brief Reference to current event number
     * 
     * The event number currently being processed by PHDST. This counter
     * increments as events are read and processed.
     */
    inline int &NEVENT = phgen_.nevent;
    
    /**
     * @brief Reference to good events counter
     * 
     * Counter for the number of events that have been successfully
     * processed without errors or rejections.
     */
    inline int &NGOODS = phgen_.ngoods;
    
    /**
     * @brief Reference to extended event counter
     * 
     * Extended or auxiliary event counter used for additional event
     * bookkeeping purposes.
     */
    inline int &NEVENX = phgen_.nevenx;
    
    /**
     * @brief Reference to extended good events counter
     * 
     * Extended counter for good events, used in conjunction with
     * the extended event counter for detailed statistics.
     */
    inline int &NGOODX = phgen_.ngoodx;
    
    /**
     * @brief Reference to interactive mode flag
     * 
     * Flag indicating whether PHDST is running in interactive mode,
     * which may affect user interface and processing behavior.
     */
    inline int &INTRCT = phgen_.intrct;
    
    /**
     * @brief Reference to total processing time
     * 
     * Total elapsed time for processing events, typically measured
     * in seconds. Used for performance monitoring and statistics.
     */
    inline float &TIMTOT = phgen_.timtot;
    
    /**
     * @brief Reference to end time marker
     * 
     * Time marker indicating the end of processing or a specific
     * processing phase. Used for timing calculations.
     */
    inline float &TIMEND = phgen_.timend;
    
    /**
     * @brief Reference to maximum post-processing steps
     * 
     * Maximum number of post-processing steps allowed during
     * event reconstruction and analysis.
     */
    inline int &MAXPST = phgen_.maxpst;
    
    /**
     * @brief Reference to post-processing flag limit
     * 
     * Limit or threshold value for post-processing flags,
     * controlling when certain post-processing operations are triggered.
     */
    inline int &LIMPSF = phgen_.limpsf;
    
    /**
     * @brief Reference to last post-processing stage
     * 
     * Identifier for the last post-processing stage that was
     * executed during event processing.
     */
    inline int &LAPSTG = phgen_.lapstg;
    
    /**
     * @brief Reference to output file counter
     * 
     * Counter for the number of output files created or being
     * written during the PHDST session.
     */
    inline int &NFILOU = phgen_.nfilou;
    
    /**
     * @brief Access to DSS save array
     * 
     * Provides access to the Data Set Service (DSS) save array,
     * which stores information about data sets for later retrieval.
     * 
     * @param i Index into the NDSSAV array (1-based Fortran indexing)
     * @return Reference to the i-th DSS save value
     * 
     * @note Uses 1-based indexing to match Fortran conventions
     * @note Array size is 10 elements (indices 1-10)
     */
    inline int &NDSSAV(int i) { return phgen_.ndssav[i - 1]; }
    
    /**
     * @brief Reference to data packing flag
     * 
     * Flag indicating whether data compression/packing is enabled
     * for data storage and transfer operations.
     */
    inline int &PACKED = phgen_.packed;
    
    /**
     * @brief Reference to packing algorithm version
     * 
     * Version identifier for the data packing/compression algorithm
     * currently being used.
     */
    inline int &IVPACK = phgen_.ivpack;
    
    /**
     * @brief Reference to file size limit
     * 
     * Maximum allowed size for output files, typically specified
     * in megabytes or other appropriate units.
     */
    inline float &FILIMT = phgen_.filimt;
    
    /**
     * @brief Reference to file access mode/counter
     * 
     * File access mode indicator or counter for file operations,
     * controlling how files are opened and accessed.
     */
    inline int &FILACC = phgen_.filacc;
    
    /**
     * @brief Reference to stage PUT word counter
     * 
     * Counter for PUT operations in staged data processing,
     * tracking the number of data words written to staging area.
     */
    inline int &STGPUTW = phgen_.stgputw;
    
    /**
     * @brief Reference to signal exit flag
     * 
     * Flag used to signal that the program should exit or terminate
     * processing, typically set when stop conditions are met.
     */
    inline int &SGNEXIT = phgen_.sgnexit;
    
    /**
     * @brief Reference to PHDST last operation flag
     * 
     * Flag indicating the last operation performed by PHDST,
     * used for state management and debugging purposes.
     */
    inline int &PHGLST = phgen_.phglst;
    
} // namespace phdst

