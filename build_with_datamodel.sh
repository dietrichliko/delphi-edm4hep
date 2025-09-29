#!/bin/bash
# Build script for DELPHI EDM4hep project with custom data model

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}Building DELPHI EDM4hep project with custom data model...${NC}"

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    echo -e "${YELLOW}Creating build directory...${NC}"
    mkdir build
fi

cd build

# Configure with CMake
echo -e "${YELLOW}Configuring with CMake...${NC}"
cmake ..

# Build the project
echo -e "${YELLOW}Building the project...${NC}"
make -j$(nproc)

# Check if the custom data model library was created
if [ -f "datamodel/libdelphi_edm4hep.so" ]; then
    echo -e "${GREEN}✓ Custom data model library built successfully${NC}"
else
    echo -e "${RED}✗ Custom data model library not found${NC}"
    exit 1
fi

# Check if the main executables were created
if [ -f "src/delphi_edm4hep" ]; then
    echo -e "${GREEN}✓ DELPHI EDM4hep converter built successfully${NC}"
else
    echo -e "${RED}✗ DELPHI EDM4hep converter not found${NC}"
    exit 1
fi

if [ -f "src/delphi_phdst" ]; then
    echo -e "${GREEN}✓ DELPHI PHDST analyzer built successfully${NC}"
else
    echo -e "${RED}✗ DELPHI PHDST analyzer not found${NC}"
    exit 1
fi

echo -e "${GREEN}Build completed successfully!${NC}"
echo ""
echo "Generated files:"
echo "  - Custom data model: datamodel/libdelphi_edm4hep.so"
echo "  - Generated headers: datamodel/generated/include/delphi_edm4hep/"
echo "  - EDM4hep converter: src/delphi_edm4hep"
echo "  - PHDST analyzer: src/delphi_phdst"
