################################################################################
# File      generate.py
# Date      July 12, 2024
#
# Command interface to generate MIS instances
################################################################################

import argparse
import os
import sys
from sampler import GraphSampler, ERGraphSampler, KingGraphSampler
from instance import Instance
import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

def plot(ax, graph: nx.Graph, positions, node_colors = "#6437FF") -> None:
    """
    Visualize a graph using networkx
    ax          - matplotlib axis to draw on
    graph       - networkx graph of vertices and edges, with vertex labels as integers
    positions   - Positions of each vertex
    node_colors - Color of nodes. Either a string, or list of strings, one for each vertex
    """
    ax.set_aspect('equal')
    ax.axis('off')
    pos_dict = {a:positions[a] for a in range(positions.shape[0])}
    nx.draw_networkx_edges(graph,pos_dict,width=10/np.sqrt(len(graph.nodes)))
    nx.draw_networkx_nodes(graph,pos_dict,node_size=1225/np.sqrt(len(graph.nodes)),node_color=node_colors)

def main():
    parser = argparse.ArgumentParser(
        prog = "generate.py",
        description="Generates an random instance of a unit disk graph"
    )

    parser.add_argument("-x", type = int, required=True, help="xdim of lattice")
    parser.add_argument("-y", type = int, required=True, help="ydim of lattice")   
    parser.add_argument("-p", 
                        "--probability", 
                        type=float,
                        required=True,
                        default=0,
                        help="The seed used to generate the graph")

    args = parser.parse_args()
    x = args.x
    y = args.y
    p = args.probability

    pos, instance = KingGraphSampler(x, y, p).generate()
    fig = plt.figure()
    ax = plt.subplot(1,1,1)
    plot(ax, instance.get_networkx_graph(), pos)
    plt.show()

if __name__ == "__main__":
    main()