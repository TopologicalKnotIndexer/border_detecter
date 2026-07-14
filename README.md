# Border Detector

Determine whether the diagram component containing arc label `1` touches the
exterior background of a routed integer matrix.

## Build and run

```bash
g++ -std=c++17 -O2 src/main.cpp -o border_detecter
./border_detecter matrix.txt
```

The program prints `AC` when the target component is exposed to the exterior
and `WA` when it is enclosed. Invalid input is reported on standard error with
a nonzero exit status.

## Matrix format

Input is a non-empty rectangular whitespace-separated integer matrix:

- `0` is background;
- positive integers are arc labels;
- negative cells are crossings, and their four orthogonal neighbors must be
  positive arc labels.

The top-left cell must be `0`, providing an exterior-background seed. The
diagram graph must contain arc label `1`, which selects the component being
tested.

Example with an exposed one-crossing component:

```text
0 1 0
2 -1 2
0 1 0
```

## Algorithm

A four-neighbor breadth-first search marks exterior zero cells. The boundary
mask selects non-background cells adjacent to that exterior region. A separate
union-find traversal connects opposite arc labels at every crossing. The final
test intersects the exterior label set with the connected component containing
label `1`.

## Development

A C++17 compiler is required. Python 3.10 or newer runs the compile-and-execute
regression tests:

```bash
python -m unittest discover -s tests -v
```

This standalone C++ repository has no PyPI publication step and no nested Git
dependency.

## License

MIT. See [`LICENSE`](LICENSE).

## Citation

If you use this repository in academic work, please cite it as:

```bibtex
@software{topologicalknotindexer_border_detecter,
  author = {{TopologicalKnotIndexer contributors}},
  title = {{border\_detecter}},
  year = {2026},
  url = {https://github.com/TopologicalKnotIndexer/border_detecter}
}
```
