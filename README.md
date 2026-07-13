# Border Detecter

Detect border pixels and connected regions in integer matrices.

## Installation

Clone the repository and compile `src/main.cpp` with a C++17 compiler.

## Usage example

```bash
g++ -std=c++17 -O3 src/main.cpp -o border_detecter
./border_detecter < input.txt
```

## Algorithm

The program wraps the input as an integer matrix, derives a zero/one mask, and builds a graph over neighboring active cells. Breadth-first search labels connected components. Border masks then retain cells adjacent to the background or matrix boundary. The implementation uses compact matrix and adjacency abstractions so the same traversal can be reused by diagram-layout code.

## Input conventions

A PD code is represented as a list of four-entry crossings. Arc labels normally occur exactly twice. Public functions validate inputs and return new values rather than mutating caller-owned data unless their API explicitly says otherwise.

## External software

- A C++17 compiler such as GCC, Clang, or recent MSVC.
- Python is optional and is only needed for the scripts under `data/`.

## Development

Run examples and package checks before release. Python packages require Python 3.10 or newer. Build PyPI artifacts with:

```bash
poetry check
poetry build
```

## License

MIT. See `LICENSE`.
