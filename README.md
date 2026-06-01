# Graph Creator

Menu-driven C++ program for a directed, weighted graph using an adjacency table.

## Features

- Add vertex
- Add directed weighted edge
- Remove vertex and all connected edges
- Remove directed edge
- Print adjacency table
- Find shortest path with Dijkstra's Algorithm

The program assumes no more than 20 vertices.

## Build

```bash
make
```

## Run

```bash
make run
```

Or:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o graph_creator
./graph_creator
```

## Example

```text
1. Add Vertex: A
1. Add Vertex: B
1. Add Vertex: C
2. Add Edge: A B 5
2. Add Edge: B C 3
2. Add Edge: A C 10
5. Find Shortest Path: A C
```

Expected shortest path:

```text
A -> B -> C
Total weight: 8
```
# GraphCreator
