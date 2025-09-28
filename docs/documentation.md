# Documentation Generation

This project uses Doxygen to generate comprehensive API documentation from the source code comments.

## Prerequisites

To generate documentation, you need to have Doxygen installed:

```bash
# On Ubuntu/Debian
sudo apt-get install doxygen graphviz

# On CentOS/RHEL/Fedora
sudo yum install doxygen graphviz
# or
sudo dnf install doxygen graphviz

# On macOS with Homebrew
brew install doxygen graphviz
```

The `graphviz` package is optional but recommended for generating class diagrams and dependency graphs.

## Building Documentation

### Enable Documentation Generation

Documentation generation is enabled by default. To disable it:

```bash
cmake -DBUILD_DOCS=OFF ..
```

### Generate Documentation

There are two targets available for generating documentation:

```bash
# Generate documentation manually
make docs

# Or use the doxygen target
make doxygen
```

### Output Location

The generated documentation will be placed in:
```
build/docs/html/index.html
```

You can open this file in a web browser to view the documentation.

## Installation

To install the documentation along with the project:

```bash
make install
```

The documentation will be installed to:
```
<install_prefix>/share/doc/delphi-edm4hep/html/
```

## Configuration

The Doxygen configuration is controlled by the `Doxyfile.in` template, which is processed by CMake to create the final `Doxyfile`. Key settings include:

- **Input directories**: `include/` and `src/` directories are scanned
- **File patterns**: `*.hpp`, `*.cpp`, `*.h`, `*.c`, and `*.md` files
- **Output format**: HTML (LaTeX generation is disabled by default)
- **Features enabled**:
  - Source code browser
  - Class diagrams and collaboration graphs
  - Include dependency graphs
  - Alphabetical index
  - Search functionality

## Customization

To customize the documentation generation:

1. Edit `Doxyfile.in` to modify Doxygen settings
2. Reconfigure with CMake: `cmake ..`
3. Rebuild documentation: `make docs`

## Documentation Quality

The project uses extensive Doxygen comments throughout the codebase:

- **Classes**: Comprehensive class documentation with purpose and usage examples
- **Functions**: Parameter descriptions, return values, and behavior documentation
- **Common blocks**: PHDST Fortran integration with detailed variable descriptions
- **Examples**: Code examples demonstrating proper usage patterns

## Troubleshooting

### Doxygen Not Found
```
-- Doxygen not found - documentation will not be generated
```
**Solution**: Install the doxygen package for your system.

### Missing Graphs
If class diagrams or dependency graphs are missing, ensure `graphviz` is installed.

### Build Errors
If documentation generation fails, check:
1. Doxygen version compatibility (minimum version 1.8)
2. Source file permissions
3. Available disk space in the build directory