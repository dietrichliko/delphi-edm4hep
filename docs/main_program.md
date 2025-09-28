# PHDST Analysis Program

This main program demonstrates how to use the DELPHI-EDM4hep PHDST Analysis framework with colored logging and command-line argument parsing.

## Usage

```bash
./delphi_phdst [OPTIONS] [FILE ...]
```

### Arguments
- `FILE...`: Optional DELPHI DST input files to process. If not specified, input will be read from a PDLINPUT file.

### Options
- `-h, --help`: Show help message and exit
- `--version`: Show program version and exit
- `-n, --max-events N`: Maximum number of events to process (0 = unlimited, default: 0)
- `-l, --log-level LEVEL`: Set log level (trace, debug, info, warn, error, critical, default: info)
- `-v, --verbose`: Enable verbose logging (equivalent to --log-level debug)

## Examples

### Basic usage with one file
```bash
./delphi_phdst input.dst
```

### Use PDLINPUT file (no command-line files)
```bash
./delphi_phdst
```

### Process multiple files with event limit
```bash
./delphi_phdst --max-events 1000 file1.dst file2.dst file3.dst
```

### Enable debug logging
```bash
./delphi_phdst --verbose input.dst
```

### Set specific log level
```bash
./delphi_phdst --log-level warn input.dst
```

## Log Levels

The program supports different log levels with colored output:
- **TRACE**: Very detailed debugging information
- **DEBUG**: Detailed debugging information (enabled with --verbose)
- **INFO**: General information about program execution (default)
- **WARN**: Warning messages
- **ERROR**: Error messages
- **CRITICAL**: Critical error messages

## Output

The program uses colored console output with timestamps:
```
[2025-01-10 14:30:45.123] [info] DELPHI-EDM4hep PHDST Analysis Starting
[2025-01-10 14:30:45.124] [info] Configuration:
[2025-01-10 14:30:45.124] [info]   Input files: 2 files
[2025-01-10 14:30:45.125] [info]     1: file1.dst
[2025-01-10 14:30:45.125] [info]     2: file2.dst
[2025-01-10 14:30:45.126] [info]   Max events:  1000
[2025-01-10 14:30:45.126] [info]   Log level:   info
```

## Building

Make sure the project is built with CMake:
```bash
mkdir build
cd build
cmake ..
make
```

The executable will be created as `build/src/delphi_phdst`.

## Analysis Implementation

The main program uses an `ExampleAnalysis` class that demonstrates:
- Custom initialization in `user00()`
- Event selection in `user01()`
- Event processing in `user02()`
- Finalization in `user99()`

You can modify this class or create your own analysis class by inheriting from `phdst::Analysis`.