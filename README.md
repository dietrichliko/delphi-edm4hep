# DELPHI-EDM4hep

The project implements a conversion of DELPHI DST data into EDM4hep, enabling integration 
with FCC software frameworks, standardized event data access, and physics validation against 
legacy DELPHI analyses.

## Project Description

The goal of this project is to convert legacy DST (Data Summary Tape) data from the DELPHI 
experiment at LEP into the modern EDM4hep event data model adopted by the FCC and broader 
HEP community. By mapping DELPHI's reconstructed event content into EDM4hep, we enable 
seamless use of established FCC software tools and frameworks, ensure long-term data preservation, 
and open the data for new physics analyses and educational projects. The project involves defining 
a robust schema translation, implementing converters, and validating the results against original 
DELPHI analyses to guarantee physics fidelity.

## Custom Data Model

This project extends EDM4hep with DELPHI-specific data types defined in `datamodel/delphi_edm4hep.yaml`:

- **delphi::EventHeader**: Extended event metadata including DELPHI-specific fields
- **delphi::RunHeader**: Run-level information with LEP beam parameters
- **delphi::TimeStamp**: Unix timestamp wrapper
- **delphi::Vector3f**: 3D vector for geometric data

The custom data model is automatically generated from the YAML schema during build.p

The project implements a conversion of DELPHI DST data into EDM4hep, enabling integration 
with FCC software frameworks, standardized event data access, and physics validation against 
legacy DELPHI analyses.

## Project Desciption

The goal of this project is to convert legacy DST (Data Summary Tape) data from the DELPHI 
experiment at LEP into the modern EDM4hep event data model adopted by the FCC and broader 
HEP community. By mapping DELPHI’s reconstructed event content into EDM4hep, we enable 
seamless use of established FCC software tools and frameworks, ensure long-term data preservation, 
and open the data for new physics analyses and educational projects. The project involves defining 
a robust schema translation, implementing converters, and validating the results against original 
DELPHI analyses to guarantee physics fidelity.
