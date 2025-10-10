#pragma once
// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: Wrapper class for a PHDST Analysis

#include <string>
#include <memory>
#include <vector>

namespace phdst {

/**
 * @brief Singleton Analysis base class for PHDST operations
 * 
 * This class implements a singleton pattern to ensure only one Analysis
 * instance (base or derived) exists at any time. The implementation is
 * designed for single-threaded use and does not include thread-safety
 * mechanisms.
 * 
 * The Analysis class serves as the base for all PHDST analysis operations,
 * providing a framework interface to the legacy DELPHI Fortran code. It
 * manages the lifecycle of analysis operations and provides virtual methods
 * that can be overridden by derived classes to implement specific analysis
 * logic.
 * 
 * @note This class is designed for single-threaded environments only.
 * @note Only one instance (base or derived) can exist at any time.
 * 
 * @example analysis.hpp
 * @code{.cpp}
 * class MyAnalysis : public phdst::Analysis {
 * public:
 *     MyAnalysis() : Analysis() {}
 *     void user00() override { // custom initialization }
 * };
 * 
 * MyAnalysis analysis;
 * analysis.run();
 * @endcode
 */
class Analysis {

public:
    /**
     * @brief Get the current Analysis instance
     * 
     * Returns a pointer to the currently active Analysis instance, or nullptr
     * if no instance exists. This method provides access to the singleton
     * instance from anywhere in the code.
     * 
     * @return Pointer to the current Analysis instance, or nullptr if none exists
     * @note Not thread-safe - designed for single-threaded use only
     */
    static Analysis* getInstance() { return instance_; }
    
    /**
     * @brief Virtual destructor
     * 
     * Cleans up the Analysis instance and resets the singleton state,
     * allowing a new instance to be created later.
     */
    virtual ~Analysis();

    // Delete copy constructor and assignment operator
    Analysis(const Analysis&) = delete;
    Analysis& operator=(const Analysis&) = delete;
    Analysis(Analysis&&) = delete;
    Analysis& operator=(Analysis&&) = delete;

    /**
     * @brief Run the analysis with given options
     * 
     * Run the PHDST framework with the provided configuration options
     * and prepares the analysis for execution. 
     * 
     * @param options Configuration options string passed to PHDST initialization
     * @return Status code (typically 0 for success)
     * 
     * @note This method
     */
    int run(const std::string & options = "");

    /**
     * @brief Set the maximum number of events to process
     * 
     * Sets the maximum number of events that should be processed during
     * the analysis run. If set to 0 (default), all events will be processed.
     * 
     * @param max_events Maximum number of events to process (0 = unlimited)
     */
    void setMaxEvent(int max_events);

    /**
     * @brief Set input file for PHDST processing
     * 
     * Stores the input file path for later processing. The actual "FILE =" command
     * will be sent to PHPONE during the user00() initialization phase, not immediately.
     * This allows multiple input files to be specified before analysis starts.
     * 
     * @param filepath Path to the input file (can be absolute or relative)
     * 
     * @note The file path is stored and will be processed during user00() initialization
     * @note Multiple input files can be set by calling this method multiple times
     * @note This method should be called before run()
     * 
     * @example
     * @code
     * MyAnalysis analysis;
     * analysis.setInput("/path/to/data/file1.dst");
     * analysis.setInput("/path/to/data/file2.dst");
     * analysis.run(); // Files will be processed during initialization
     * @endcode
     */
    void setInput(const std::string &filepath);

    /**
     * @brief Set T4 hadron filtering flag
     * 
     * When enabled, the analysis will filter T4 hadrons during event processing.
     * This affects event selection and vertex processing.
     * 
     * @param filter True to enable T4 hadron filtering, false to disable
     */
    void setFilterT4Hadrons(bool filter) { filter_t4_hadrons_ = filter; }

    /**
     * @brief Internal initialization method
     * 
     * Called by the C interface user00_() function. Performs framework
     * initialization including processing stored input files via PHPONE,
     * setting LUNPDL to 0, and then calling the virtual user00() method.
     * 
     * @note This method should not be overridden by derived classes
     * @note Derived classes should override user00() instead
     * @note Made public to allow access from C interface functions
     */
    void init();

    /**
     * @brief Pilot record processing with event limit handling
     * 
     * Internal method that handles event counting and max_event_ logic.
     * Called by the C interface user01_() function. Checks the current
     * event count and calls the virtual user01() method if within limits.
     * 
     * @return Processing status (1 = read event, 0 = skip event, -3 = stop processing)
     * @note Made public to allow access from C interface functions
     */
    int pilot_record();

    /**
     * @brief Set event logging interval for user01 processing
     * 
     * Controls how often event processing information is logged:
     * - If interval < 0: Disable all event processing logging
     * - If interval > 0: Log run and event number every 'interval' events
     * - If interval = 0: No periodic logging (default)
     * 
     * @param interval Number of events between log messages (0 = no logging, <0 = disabled)
     */
    void setEventLogInterval(int interval);

    /**
     * @brief User initialization routine
     * 
     * Called by the framework during initialization phase. Override this
     * method in derived classes to perform custom initialization tasks
     * such as booking histograms, setting up data structures, etc.
     * 
     * @note Called once at the beginning of analysis
     */
    virtual void user00();

    /**
     * @brief Pilot record processing
     * 
     * Called by the framework after the pilot record has been read.
     * 
     * @return Processing status (1 = read event, 0 = skip event, -3 = stop processing)
     */
    virtual int user01();

    /**
     * @brief Event processing routine
     * 
     * Called for each event
     * 
     */
    virtual void user02();

    /**
     * @brief Finalization routine
     * 
     * Called by the framework at the end of analysis. Override this
     * method in derived classes to perform cleanup tasks such as
     * writing histograms, calculating final results, etc.
     * 
     * @note Called once at the end of analysis
     */
    virtual void user99();


protected:
    /**
     * @brief Protected constructor
     * 
     * Can only be called by derived classes. Enforces the singleton pattern
     * by throwing an exception if an instance already exists.
     * 
     * @throws std::runtime_error if an Analysis instance already exists
     */
    Analysis();

private:
    /**
     * @brief Static instance pointer
     * 
     * Tracks the single Analysis instance. Used to enforce the singleton
     * pattern and provide global access to the current instance.
     */
    static Analysis* instance_;
    
    /**
     * @brief Maximum number of events to process
     * 
     * If set to 0 (default), all events will be processed.
     * Otherwise, processing stops after this many events.
     */
    int max_event_ = 0;
    
    /**
     * @brief Container for input file paths
     * 
     * Stores file paths that will be processed during user00() initialization.
     * This allows multiple input files to be specified before analysis starts.
     */
    std::vector<std::string> input_files_;
    
    /**
     * @brief Flag to enable T4 hadron filtering during event processing
     * 
     * When true, the analysis will apply T4 hadron filtering logic
     * during event selection and vertex processing.
     */
    bool filter_t4_hadrons_ = false;
    
    /**
     * @brief Event logging interval
     * 
     * Controls logging of event processing in user01:
     * - If <= 0: No event processing output
     * - If > 0: Print run and event number every N events
     */
    int event_log_interval_ = 0;
};

} // namespace phdst
