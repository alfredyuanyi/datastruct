#! /usr/bin/python2
# coding: utf8

from Queue import Queue
from DefineGraph import UnWeightedDigraph

INFINITY = float('Inf')

def BFS(graph, distance, start):
    q = Queue(len(graph.vertexs))
    q.put(start)
    distance[start] = 0
    while not q.empty():
        current = q.get()
        for v in graph[current]:
            if distance[v] == INFINITY:
                distance[v] = distance[current] + 1
                q.put(v)
    return distance


if __name__ == '__main__':
    graph = UnWeightedDigraph([1, 2, 3, 4, 5, 6, 7],
                              [(1, 2), (1, 4), (2, 4), (2, 5), (3, 6), (4, 3), (4, 6),
                               (4, 6), (4, 7), (5, 7), (7, 6), (3, 1)])
    distance = {}
    for v in graph.vertexs:
        distance[v] = INFINITY
    print BFS(graph, distance, 3)
