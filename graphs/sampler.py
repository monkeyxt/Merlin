################################################################################
# File      sampler.py
# Date      July 12, 2024
#
# Random graph samplers
################################################################################
import random
import os
import networkx as nx
from networkx import erdos_renyi_graph, Graph
import argparse
import numpy as np
from abc import ABC, abstractmethod
from instance import Instance

################################################################################
# Abstract graph sampler
################################################################################
class GraphSampler(ABC):
    @abstractmethod
    def generate(self):
        pass

################################################################################
# Erdos Renyi graph generator
################################################################################
class ERGraphSampler(ABC):
    def __init__(self, min_n : int, max_n : int, p : float) -> None:
        self.min_n = min_n
        self.max_n = max_n
        self.p = p

    def __str__(self) -> str:	
        return f"ER_{self.min_n}_{self.max_n}_{self.p}"

    def generate(self):
        n = random.randint(self.min_n, self.max_n)
        points = np.array()
        graph = nx.erdos_renyi_graph(n, self.p)
        instance = Instance()
        instance.convert_from_networkx(graph)
        return points, instance

################################################################################
# King graph sampler
################################################################################
class KingGraphSampler:
    def __init__(self, x: int, y: int, p: float) -> None:
        self.x = x
        self.y = y
        self.p = p

    def __str__(self) -> str:
        return f"king_{self.x}_{self.y}_{self.p}"

    def generate(self):
        xx, yy = np.meshgrid(range(self.x), range(self.y))
        num_points = int(self.x * self.y * self.p)
        rand = np.random.default_rng()
        points = np.array([xx.flatten(),yy.flatten()]).T
        points = points[rand.permutation(self.x*self.y)[0:num_points],:]

        distances = np.sqrt((points[:,0] - points[:,0,None])**2 + 
                            (points[:,1] - points[:,1,None])**2)
        graph = nx.Graph(distances<np.sqrt(2)+1E-10)
        graph.remove_edges_from(nx.selfloop_edges(graph))
        instance = Instance()
        instance.convert_from_networkx(graph)
        return points, instance