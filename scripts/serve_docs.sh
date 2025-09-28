#!/bin/bash
# Script to build and serve Doxygen documentation locally

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}DELPHI-EDM4hep Documentation Server${NC}"
echo "=================================="

# Check if we're in the right directory
if [ ! -f "CMakeLists.txt" ]; then
    echo -e "${RED}Error: Please run this script from the project root directory${NC}"
    exit 1
fi

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    echo -e "${YELLOW}Creating build directory...${NC}"
    mkdir build
fi

# Build documentation
echo -e "${YELLOW}Building documentation...${NC}"
cd build

# Configure if needed
if [ ! -f "Makefile" ]; then
    echo -e "${YELLOW}Configuring project...${NC}"
    cmake ..
fi

# Build docs
make docs

# Check if documentation was generated
if [ ! -f "docs/html/index.html" ]; then
    echo -e "${RED}Error: Documentation was not generated successfully${NC}"
    exit 1
fi

echo -e "${GREEN}Documentation built successfully!${NC}"

# Start HTTP server
PORT=${1:-8080}
echo -e "${YELLOW}Starting HTTP server on port ${PORT}...${NC}"
echo -e "${GREEN}Open VS Code Simple Browser to: http://localhost:${PORT}${NC}"
echo -e "${YELLOW}Press Ctrl+C to stop the server${NC}"
echo ""

cd docs/html
python3 -m http.server $PORT