# Conway's Game of Life

This is a small CLI application, which was created during the _High Performance Computing Architectures - Practical Course_ at Goethe University.

You can compile this project using `cmake` (assuming you are on a Unix based OS and `g++` installed):

```bash
mkdir -p build && cd build && cmake .. && make
```
...or if you like things a bit faster:

```bash
mkdir -p build && cd build && cmake -DCMAKE_CXX_FLAGS="-O3" -DCMAKE_BUILD_TYPE=Release .. && make
```

For further information please have a look at the [docs.pdf](docs.pdf).
