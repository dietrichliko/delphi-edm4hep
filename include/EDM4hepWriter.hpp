// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: EDM4hep writer class for DELPHI data conversion

#pragma once

#include <string>
#include <memory>
#include <phdst/Analysis.hpp>

// Forward declarations
namespace podio {
    class ROOTWriter;
}

namespace edm4hep {
    class EventHeaderCollection;
}

namespace delphi {
    class EventHeaderCollection;
}

/**
 * @brief EDM4hep Writer class for converting DELPHI data to EDM4hep format
 * 
 * This class extends the PHDST Analysis framework to convert DELPHI DST data
 * into the EDM4hep format, enabling integration with modern FCC software
 * frameworks and analysis tools.
 * 
 * The class implements the standard PHDST user hooks to process events and
 * write them in EDM4hep format using the EDM4hep data model libraries.
 * 
 * @example EDM4hepWriter.hpp
 * @code{.cpp}
 * EDM4hepWriter writer;
 * writer.setOutput("output.edm4hep.root");
 * writer.setMaxEvent(1000);
 * writer.setInput("input.al");
 * writer.run();
 * @endcode
 */
class EDM4hepWriter : public phdst::Analysis {
public:
    /**
     * @brief Default constructor
     * 
     * Creates an EDM4hepWriter instance and initializes the EDM4hep
     * data structures and output configuration.
     */
    EDM4hepWriter();
    
    /**
     * @brief Virtual destructor
     * 
     * Ensures proper cleanup of EDM4hep resources and finalizes
     * the output file.
     */
    virtual ~EDM4hepWriter();
    
    /**
     * @brief Set output file path for EDM4hep data
     * 
     * Configures the output file where converted EDM4hep data will be written.
     * The file format is typically ROOT with EDM4hep structure.
     * 
     * @param output_path Path to the output EDM4hep file
     */
    void setOutput(const std::string& output_path);
    
    /**
     * @brief Get the current output file path
     * 
     * @return Current output file path, empty if not set
     */
    const std::string& getOutput() const { return output_path_; }

protected:
    /**
     * @brief Initialize EDM4hep writer and output file
     * 
     * This method is called once during initialization to set up
     * the EDM4hep data model, create the output file, and initialize
     * all necessary data structures for the conversion process.
     * 
     * @note Overrides phdst::Analysis::user00()
     */
    void user00() override;
    
    /**
     * @brief Process pilot record for event selection
     * 
     * Called for each pilot record to determine whether the event
     * should be processed. Can be used to implement event selection
     * criteria for the EDM4hep conversion.
     * 
     * @return 1 to process the event, 0 to skip, -3 to stop
     * @note Overrides phdst::Analysis::user01()
     */
    int user01() override;
    
    /**
     * @brief Convert and write DELPHI event to EDM4hep format
     * 
     * This is the main conversion method called for each selected event.
     * It reads the DELPHI data structures, converts them to EDM4hep format,
     * and writes the result to the output file.
     * 
     * @note Overrides phdst::Analysis::user02()
     */
    void user02() override;
    
    /**
     * @brief Finalize EDM4hep output and cleanup
     * 
     * Called at the end of processing to finalize the output file,
     * write metadata, and perform cleanup operations.
     * 
     * @note Overrides phdst::Analysis::user99()
     */
    void user99() override;

    /**
     * @brief Start processing a new event
     * 
     * This method is called at the beginning of event processing to
     * initialize collections and prepare for data conversion.
     */
    void startEvent();

    /**
     * @brief Finalize and write the current event to EDM4hep output
     * 
     * This method is responsible for finalizing the converted EDM4hep
     * event data and writing it to the output file.
     */
    void finishEvent();

    /**
     * @brief Fill the event header collection with metadata
     *
     */
     void fillEventHeader();


     /**
      * @brief Get timestamp of the current event
      *
      */
     int event_timestamp();
private:
    std::string output_path_;           ///< Output file path for EDM4hep data
    
    std::unique_ptr<podio::ROOTWriter> writer_;
    std::unique_ptr<edm4hep::EventHeaderCollection> event_header_collection_;
    std::unique_ptr<delphi::EventHeaderCollection> delphi_event_header_collection_;
};