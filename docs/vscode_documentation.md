# Browsing Documentation in VS Code

Yes! You can absolutely browse the Doxygen documentation directly inside VS Code. Here are several convenient ways to do it:

## Quick Start

1. **Build and serve documentation in one command:**
   ```bash
   ./scripts/serve_docs.sh
   ```

2. **Open VS Code Simple Browser:**
   - Press `Ctrl+Shift+P` (Command Palette)
   - Type "Simple Browser" 
   - Select "Simple Browser: Open"
   - Enter URL: `http://localhost:8080`

## VS Code Tasks (Recommended)

Use the built-in VS Code task system:

1. **Press `Ctrl+Shift+P`** and type "Tasks: Run Task"
2. Choose from these available tasks:
   - **"Build Documentation"** - Generate docs only
   - **"Build and Serve Documentation"** - Build and start server
   - **"Serve Documentation"** - Start server (docs must exist)

## Manual Methods

### Method 1: Build and Serve
```bash
# Build documentation
cd build && make docs

# Serve documentation  
cd docs/html && python3 -m http.server 8080
```

### Method 2: Use the convenience script
```bash
# From project root
./scripts/serve_docs.sh [PORT]
```

## Accessing the Documentation

Once the server is running, you have several options:

### Option A: VS Code Simple Browser (Recommended)
- `Ctrl+Shift+P` → "Simple Browser: Open"
- URL: `http://localhost:8080`
- Benefits: Integrated with VS Code, side-by-side with code

### Option B: External Browser
- Open your regular browser
- Navigate to `http://localhost:8080`

### Option C: VS Code Preview
- Some HTML files can be previewed directly in VS Code
- Right-click on `build/docs/html/index.html` → "Open with Live Server"

## Documentation Features

The generated documentation includes:

- **Classes**: Full API documentation for `Analysis`, `ExampleAnalysis`
- **Files**: All header files with comprehensive documentation
- **Examples**: Code examples and usage patterns
- **Dependencies**: Include graphs and class inheritance diagrams
- **Search**: Full-text search functionality
- **Source Browser**: Click to view annotated source code

## Workflow Integration

### Auto-rebuild Documentation
The documentation automatically rebuilds when source files change:
```bash
make docs  # Only rebuilds if source files have changed
```

### Keep Server Running
The HTTP server can run in the background while you code:
- Documentation updates when you run `make docs`
- Refresh browser to see changes
- No need to restart the server

## Troubleshooting

### Server Port in Use
```bash
# Use a different port
./scripts/serve_docs.sh 8081
```

### Documentation Not Found
```bash
# Make sure documentation is built
cd build && make docs
```

### VS Code Simple Browser Issues
- Ensure the HTTP server is running (`netstat -an | grep 8080`)
- Try refreshing the browser tab
- Check the server is accessible: `curl http://localhost:8080`

## Tips

1. **Split View**: Open Simple Browser in a split pane alongside your code
2. **Bookmarks**: Bookmark frequently accessed documentation pages
3. **Search**: Use the documentation's built-in search feature
4. **Navigation**: Use breadcrumbs and class inheritance graphs
5. **Source Links**: Click on function names to jump to source code

## VS Code Extensions

Consider installing these extensions for better documentation experience:
- **Doxygen Documentation Generator**: Auto-generate doc comments
- **Live Server**: Alternative way to serve HTML files
- **HTML CSS Support**: Better HTML editing in documentation files

## Advanced Usage

### Custom Doxyfile
Edit `Doxyfile.in` to customize documentation generation, then:
```bash
cd build && cmake .. && make docs
```

### Integration with Build System
Documentation is integrated with CMake:
```bash
# Configure with documentation disabled
cmake -DBUILD_DOCS=OFF ..

# Install documentation
make install  # Installs docs to share/doc/delphi-edm4hep/
```