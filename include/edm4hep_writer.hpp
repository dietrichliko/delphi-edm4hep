// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identif    /**
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: EDM4hep writer class for DELPHI data conversion

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <phdst/analysis.hpp>
#include <phdst/zebra_pointer.hpp>


// Forward declarations
namespace podio {
    class ROOTWriter;
}

namespace edm4hep {
    class EventHeaderCollection;
    class VertexCollection;
    class ReconstructedParticleCollection;
    class MCParticleCollection;
    class MCRecoParticleAssociationCollection;
    class MutableVertex;
    class MutableReconstructedParticle;
}

namespace edm4delphi {
    class EventHeaderCollection;
    class RunHeaderCollection;
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
 * @example edm4hep_writer.hpp
 * @code{.cpp}
 * EDM4hepWriter writer;
 * writer.setOutput("output.edm4hep.root");
 * writer.setMaxEvent(1000);
 * writer.setInput("input.al");
 * writer.run();
 * 
 * // Example of using the vertex map:
 * // Inside event processing:
 * phdst::ZebraPointer vertex_ptr = phdst::ZebraPointer::create(LQ(some_index));
 * edm4hep::MutableVertex& vertex = writer.getOrCreateVertex(vertex_ptr);
 * vertex.setPosition({x, y, z});
 * vertex.setChi2(chi2_value);
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
     * @brief Set configuration for secondary hadronic interaction fixing
     * 
     * Enables or disables the correction of secondary hadronic interaction
     * blocklets in the ZEBRA data structure.
     * 
     * @param enable If true, apply corrections; if false, skip corrections
     */
    void setFixSecondaryHadronicInteractions(bool enable);
    
    /**
     * @brief Get the current output file path
     * 
     * @return Current output file path, empty if not set
     */
    const std::string& getOutput() const { return output_path_; }

    /**
     * @brief Check if processing Monte Carlo data
     * 
     * Monte Carlo data is identified by negative run numbers in DELPHI data.
     * 
     * @return True if processing Monte Carlo simulation data (IIIRUN < 0)
     */
    bool is_mc() const;
    
    /**
     * @brief Check if processing real data
     * 
     * @return True if processing real (non-Monte Carlo) data (IIIRUN >= 0)
     */
    bool is_data() const { return !is_mc(); }

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
     */
     void fillEventHeader();

    /**
     * @brief Fill vertices from DELPHI data into the vertex map
     * 
     * Processes DELPHI vertex data structures and creates corresponding
     * EDM4hep vertices in the vertex map. This method reads the Zebra
     * data structures containing vertex information and converts them
     * to EDM4hep format.
     */
     void fillVertices();

    /**
     * @brief Start a new run
     * 
     * Creates and initializes a new run header when starting
     * a new run or file.
     */
    void startRun();


    /**
     * @brief Finish the current run
     * 
     * Writes the current run header when the run changes
     * or at the end of processing.
     */
    void finishRun();

     /**
      * @brief Determine and store the center-of-mass energy from DELPHI data
      * 
      * Reads the LEP beam energy information from DELPHI data structures,
      * calculates the center-of-mass energy, and stores it as a member variable.
      * Performs consistency checking during the run.
      */
     void obtainCenterOfMassEnergy();

     /**
      * @brief Determine and store the magnetic field from DELPHI data
      * 
      * Reads the magnetic field information from DELPHI pilot data structures
      * and stores it as a member variable. Performs consistency checking during the run.
      */
     void obtainMagneticField();

     /**
      * @brief Fill reconstructed particles from DELPHI data
      * 
      * Processes DELPHI reconstructed particle data structures and creates
      * corresponding EDM4hep reconstructed particles.
      */
     void fillRecoParticles();

     /**
      * @brief Fill Monte Carlo particles from DELPHI data
      * 
      * Processes DELPHI Monte Carlo particle data structures and creates
      * corresponding EDM4hep MC particles.
      */
     void fillMCParticles();

     /**
      * @brief Fill associations between MC and reconstructed particles
      * 
      * Creates associations between Monte Carlo particles and reconstructed
      * particles in the EDM4hep format.
      */
     void fillMCRecoParticleAssociations();

    /**
     * @brief Fill BTagging information from DELPHI data    
     * 
     */
     void fillBTagging();

     /**
      * @brief Fix secondary hadronic interactions in DELPHI data
      * 
      * Applies corrections for secondary hadronic interactions in the
      * DELPHI detector simulation data.
      */
     void fixSecondaryHadronicInteractions();

     /**
      * @brief Find vertex index by ZebraPointer
      * 
      * Searches for the index of an EDM4hep vertex associated with the given ZebraPointer.
      * 
      * @param zebra_ptr ZebraPointer to the DELPHI vertex data
      * @return Index in vertex collection (0-based), or -1 if not found
      * 
      * @note Use this with (*vertex_collection_)[index] to access the vertex
      */
     int findVertexIndex(const phdst::ZebraPointer& zebra_ptr) const;

private:
    std::string output_path_ = "";           ///< Output file path for EDM4hep data
    
    // Configuration flags
    bool fix_secondary_hadronic_interactions_ = true;  ///< Enable/disable secondary hadronic interaction fixes
    
    // Current run tracking
    int current_run_ = 0;                  ///< Current run number being processed
    int current_file_ = 0;                 ///< Current file number being processed
    int run_event_count_ = 0;              ///< Number of events in current run
    
    // Run-level physics parameters
    float center_of_mass_energy_ = 0.0f;      ///< Center-of-mass energy for current run (GeV), 0 = unset
    // Event level physics parameters
    float magnetic_field_ = 0.0f;             ///< Magentic field in Tesla derived from magnet current
    
    
    std::unique_ptr<podio::ROOTWriter> writer_;                                ///< ROOT file writer for EDM4hep output
    std::unique_ptr<edm4hep::EventHeaderCollection> event_header_collection_; ///< Standard EDM4hep event header collection
    std::unique_ptr<edm4delphi::EventHeaderCollection> delphi_event_header_collection_; ///< DELPHI-specific event header collection with extended metadata
    std::unique_ptr<edm4hep::VertexCollection> vertex_collection_; ///< Collection of vertices
    std::unique_ptr<edm4hep::ReconstructedParticleCollection> reco_particle_collection_; ///< Collection of reconstructed particles
    std::map<phdst::ZebraPointer, std::unique_ptr<edm4hep::VertexCollection>> vertex_map_; ///< Map from DELPHI Zebra pointers to EDM4hep vertices
    std::map<phdst::ZebraPointer, std::unique_ptr<edm4hep::ReconstructedParticleCollection>> reco_particle_map_; ///< Map from DELPHI Zebra pointers to EDM4hep reconstructed particles
    std::unique_ptr<edm4hep::MCParticleCollection> mc_particle_collection_; ///< Collection of Monte Carlo particles
    std::unique_ptr<edm4hep::MCRecoParticleAssociationCollection> mc_reco_particle_association_collection_; ///< Association collection between MC particles and reconstructed particles

    std::vector<phdst::ZebraPointer> vertex_ptrs_; ///< Collection of ZebraPointers for event processing
    std::vector<phdst::ZebraPointer> reco_particle_ptrs_; ///< Collection of ZebraPointers for reconstructed particles
    
    // Mapping from ZebraPointer to collection indices for efficient lookup
    std::unordered_map<phdst::ZebraPointer, size_t> zebra_to_vertex_index_; ///< Map from ZebraPointer to vertex index in collection
    std::unordered_map<phdst::ZebraPointer, size_t> zebra_to_reco_particle_index_; ///< Map from ZebraPointer to reco particle index in collection
};