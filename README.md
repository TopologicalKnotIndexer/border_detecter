# Border Detecter

Detect connected borders in integer matrices.

## Installation

Build the `src/main.cpp` program with a C++17 compiler. See `data/test_all.py` for a batch validation example.

## Quick start

Build the `src/main.cpp` program with a C++17 compiler. See `data/test_all.py` for a batch validation example.

PD codes are lists of four-entry crossings. Each arc label must occur exactly twice. Functions validate their inputs and do not mutate caller-owned PD-code lists unless explicitly documented.

## Development

Use Python 3.10 or newer for Python packages. Build distributions with `poetry build`. Run the package's tests or examples before publishing. C++ projects require a modern standards-compliant compiler.

## License

MIT. See `LICENSE`.
