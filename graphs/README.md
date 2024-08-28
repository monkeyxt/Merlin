# Graph Generator

This folder contains a generator for MIS instances

## Requirements
```
python3
networkx
```

## Instructions

Generate a random unit disk graph
- `x`: width of lattice 
- `y`: length of lattice
- `p`: probability of edge

```python
# Simple example
python generate -x 4 -y 4 -p 0.5
```