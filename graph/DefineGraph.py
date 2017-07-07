#! /usr/bin/python2
# coding: utf8

from Queue import Queue

class UnWeightedDigraph(dict):
    """define graph"""
    def __init__(self, vertexs, edges):
        super(UnWeightedDigraph, self).__init__()
        if isinstance(vertexs, list) and isinstance(edges, list):
            self.vertexs = vertexs
            self.edges = edges
            self.indegree = {}
        else:
            print('invalid vertexs or edges!')
            raise ValueError
        for vertex in self.vertexs:
            if vertex in self.keys():
                raise ValueError
            self[vertex] = []
            self.indegree[vertex] = 0
        for edge in edges:
            self[edge[0]].append(edge[1])
            self.indegree[edge[1]] += 1


def TopSort(graph):
    sort_list = []
    q = Queue(len(graph.vertexs))
    for vertex in graph.vertexs:
        if graph.indegree[vertex] == 0:
            q.put(vertex)
    while q.empty() is not True:
        vertex = q.get()
        sort_list.append(vertex)
        for v in graph[vertex]:
            graph.indegree[v] -= 1
            if graph.indegree[v] == 0:
                q.put(v)
    if len(sort_list) != len(graph.vertexs):
        print()
        raise ValueError
    return sort_list


if __name__ == '__main__':
    graph = UnWeightedDigraph([1, 2, 3, 4, 5, 6, 7],
                  [(1, 2), (1, 3), (2, 4), (2, 5), (3, 6), (4, 3),
                   (4, 6), (4, 7), (5, 4), (5, 7), (7, 6)])
    print(TopSort(graph))
