from FlowEdge import FlowEdge
import random

class FlowNetwork:
    """
    Initializes an empty flow network with
    V vertices and 0 edges.
    """
    def __init__(self, V):
        #print("init")
        self.__V = V
        self.__E = 0
        self.__adj = []
        for v in range(V):
            self.__adj.append([])

    """
    Create a random flow network with
    V vertices and E edges.
    """
    @classmethod
    def RandomNetwork(class_object, V, E):
        tmp = class_object(V)
        if (E < 0):
            raise Exception("Number of edges must be nonnegative")

        for i in range(E):
            v = random.randint(0,V-1)
            w = random.randint(0,V-1)
            capacity = random.randint(0,99)
            tmpE = FlowEdge(v, w, capacity)
            tmp.addEdge(tmpE)
            
        return tmp

    def V(self):
        return self.__V

    def E(self):
        return self.__E

    def __validateVertex(self,v):
        if (v < 0 or v >= self.__V):
            raise Exception("vertex " + str(v) + " is not between 0 and " + str(self.__V-1))

    def addEdge(self,e):
        v = e.From()
        w = e.To()
        self.__validateVertex(v)
        self.__validateVertex(w)
        self.__adj[v].append(e)
        self.__adj[w].append(e)
        self.__E += 1

    def adj(self,v):
        self.__validateVertex(v)
        return self.__adj[v]

    def edges(self):
        edgeList = []
        for v in range(self.__V):
            for e in self.__adj(v):
                if (e.To() != v):
                    edgeList.append(e)
        return edgeList

    def __str__(self):
        s = str(self.__V)+" "+str(self.__E)+"\n"
        for v in range(self.__V):
            s += str(v)+": "
            for e in self.__adj[v]:
                if (e.To() != v):
                    s += str(e)+" "
            s += "\n"
        return s 
