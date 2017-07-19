from sys import maxint

class Edge:
    
    def __init__(self, source, target, capacity, revEdge = None):
        self.source = source
        self.target = target
        self.flow = 0
        self.capacity = capacity
        self.revEdge = revEdge

    def __repr__(self):
        return 'source={}, target={}, flow={}, capacity={}'.format(self.source, self.target, self.flow, self.capacity)

    def residualCapacity(self):
        return self.capacity - self.flow

    def increaseFlow(self, delta):
        self.flow = self.flow + delta
        self.revEdge.flow = self.revEdge.flow - delta


class VertexSeperator():

    def __init__( self, graph ):
        self.graph = {}

        for node in graph:
            self.graph[self._getNodeName(node, in_node = True)] = []
            self.graph[self._getNodeName(node, in_node = False)] = []
            e1 = Edge( self._getNodeName(node, in_node = True), self._getNodeName(node, in_node = False), 1 )
            e2 = Edge( self._getNodeName(node, in_node = False), self._getNodeName(node, in_node = True), 0 )
            e1.revEdge = e2
            e2.revEdge = e1
            self.graph[self._getNodeName(node, in_node = True)].append(e1)
            self.graph[self._getNodeName(node, in_node = False)].append(e2)

        for source in graph:
            for target in graph[source]:
                self._addEdge(source, target)

    def __repr__(self):
        for node in self.graph:
            print 'Node=' + node
            for e in self.graph[node]:
                print '  ' + str(e)              

    def minimumVertexSeperator( self, S = [], T = [] ):
        from copy import copy

        S = [ self._getNodeName(x, in_node = False) for x in S]
        T = [ self._getNodeName(x, in_node = True)  for x in T]
        maxFlow = self._maxFlow(S,T)
        
        visited = {}
        
        for node in self.graph:
            visited[node] = False
        for node in S:
            visited[node] = True
            visited[self._getNodeName(node.split('#')[0], in_node = True)] = True
        for node in T:
            visited[self._getNodeName(node.split('#')[0], in_node = False)] = True

        touchedNodes = []
        queue = copy(S)
        while queue:
            node = queue.pop(0)
            touchedNodes.append(node)

            for e in self.graph[node]:
                if not visited[e.target] and e.residualCapacity() > 0:
                    visited[e.target] = True
                    queue.append(e.target)

        vertexSeperator = []
        for node in touchedNodes:
            name = node.split('#')
            if name[1] == 'in' and self._getNodeName(name[0], in_node = False) not in touchedNodes:
                vertexSeperator.append(name[0])

        return vertexSeperator

    def _maxFlow( self, S = [], T = []):
        maxFlow = 0
        while True:
            found, sink, parent = self._bfs(S,T)
            if not found:
                break
            maxFlow = maxFlow + self._augment(sink, parent)

        return maxFlow

    def _bfs( self, S, T ):
        from copy import copy
        parent = {}
        visited = {}
        for source in S:
            parent[source] = None
        
        for node in self.graph:
            visited[node] = False
        for node in S:
            visited[node] = True
            visited[self._getNodeName(node.split('#')[0], in_node = True)] = True
        for node in T:
            visited[self._getNodeName(node.split('#')[0], in_node = False)] = True

        sink = 'INVALID'
        found = False
        queue = copy(S)
        while queue:
            node = queue.pop(0)

            if node in T:
                found = True
                sink = node
                break

            for e in self.graph[node]:
                if not visited[e.target] and e.residualCapacity() > 0:
                    parent[e.target] = e
                    visited[e.target] = True
                    queue.append(e.target)

        return found, sink, parent

    def _augment(self, node, parent, minFlow = maxint):
        e = parent[node]
        if not e:
            return minFlow
        deltaFlow = self._augment( e.source, parent, min( e.residualCapacity(), minFlow ) )
        e.increaseFlow(deltaFlow)
        return deltaFlow

    def _addEdge(self, source, target, ):
        e1 = Edge(self._getNodeName(source, in_node = False), self._getNodeName(target, in_node = True), maxint)
        e2 = Edge(self._getNodeName(target, in_node = True), self._getNodeName(source, in_node = False), 0)
        e1.revEdge = e2
        e2.revEdge = e1
        self.graph[self._getNodeName(source, in_node = False)].append(e1)
        self.graph[self._getNodeName(target, in_node = True)].append(e2)

    def _getNodeName( self, node, in_node = True ):
        if in_node:
            return node + '#in'
        else:
            return node + '#out'

def construct_test_graph1():
    graph = {}
    graph['A'] = ['B', 'C', 'D', 'E']
    graph['B'] = ['F', 'G']
    graph['C'] = ['F', 'G']
    graph['D'] = ['F', 'G']
    graph['E'] = ['F', 'G']
    graph['F'] = ['H']
    graph['G'] = ['H']
    graph['H'] = []
    return graph

def construct_test_graph2():
    graph = {}
    graph['A'] = ['B', 'C', 'D']
    graph['B'] = ['E']
    graph['C'] = ['E']
    graph['D'] = ['E',]
    graph['E'] = ['F', 'G']
    graph['F'] = ['H']
    graph['G'] = ['H']
    graph['H'] = []
    return graph
