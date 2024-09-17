# Graph Generator

This folder contains a generator for MIS instances

## Requirements
```
python3
networkx
```

## Instructions

Generate a random unit disk graph
- `-x [int]`: width of lattice 
- `-y [int]`: length of lattice
- `-p [float]`: probability of edge
- `-o [file]`: place to write generated graph
- `-s`: plot graph

```python
# Simple example
python generate.py -x 4 -y 4 -p 0.5
```