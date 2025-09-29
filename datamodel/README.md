# DELPHI EDM4hep Data Model

This directory contains the custom EDM4hep data model extension for DELPHI data conversion.

## Overview

The DELPHI EDM4hep data model extends the standard EDM4hep format with DELPHI-specific event and run metadata. This allows preserving all the original DELPHI information while maintaining compatibility with modern EDM4hep-based analysis frameworks.

## Files

- `delphi_edm4hep.yaml` - YAML schema defining the custom data types
- `CMakeLists.txt` - CMake configuration for generating C++ classes
- `delphi_edm4hepConfig.cmake.in` - CMake package configuration template

## Data Types

### delphi::EventHeader

Extended event header containing:
- Standard event identification (event number, run number, timestamp)
- DELPHI-specific metadata (file number, fill number, experiment number)
- Original DELPHI date/time formats for debugging
- Beam spot information
- Trigger and data quality information

### delphi::RunHeader

Run-level metadata including:
- Run identification and time span
- LEP beam energy and run type
- Detector status information
- Event counts

### Components

- `delphi::Vector3f` - 3D vector with float precision
- `delphi::TimeStamp` - Unix timestamp wrapper

## Usage

The data model is automatically generated from the YAML schema during the CMake build process. The generated C++ classes can be used as follows:

```cpp
#include <delphi_edm4hep/EventHeaderCollection.h>
#include <delphi_edm4hep/EventHeader.h>

// Create a collection
auto eventHeaders = delphi::EventHeaderCollection();

// Create an event header
auto header = eventHeaders.create();
header.setEventNumber(12345);
header.setRunNumber(67890);
header.setDelphiDate(941215);  // YYMMDD format
header.setDelphiTime(143052);  // HHMMSS format

// Set timestamp
delphi::TimeStamp timestamp;
timestamp.setUnixTime(timeval);
header.setTimeStamp(timestamp);
```

## Build Process

1. The YAML schema is processed by podio's data model generator
2. C++ header and source files are generated in `build/datamodel/generated/`
3. A shared library `libdelphi_edm4hep.so` is created
4. The library is linked to the main conversion executable

## Integration

The custom data model is integrated into the main project through:
1. CMake subdirectory inclusion in the main `CMakeLists.txt`
2. Library linkage in `src/CMakeLists.txt`
3. Header inclusion in the EDM4hep writer classes

This allows seamless use of DELPHI-specific data types alongside standard EDM4hep types.
