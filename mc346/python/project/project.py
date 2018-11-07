import numpy as np

def read_input():
    graph_input = []
    uber_input = []
    flag_read_uber = 0

    while True:
        # Read iput until EOF
        try:
            string = input ()

            # Check if we reach the end of graph input
            if string == '':
                flag_read_uber = 1
                continue

            if flag_read_uber == 0:
                graph_input.append(string)
            if flag_read_uber == 1:
                uber_input.append(string)
        except:
            break

    return graph_input, uber_input

def getMaxEdgeValue (graph_input):
    max_index = 0
    for element in graph_input:
        element = element.split(' ')
        start_vertice = int(element[0])
        end_vertice = int(element[1])
        if start_vertice > max_index:
            max_index = start_vertice
        if end_vertice > max_index:
            max_index = end_vertice
    return max_index + 1

def createGraph (max_index, graph_input):
    graph = np.zeros((max_index,max_index))

    for element in graph_input:
        element = element.split(' ')
        start_vertice = int(element[0])
        end_vertice = int(element[1])
        edge_weight = float(element[2])
        graph[start_vertice] [end_vertice] = edge_weight
    return graph


def floydWarshallWithPathReconstruction (graph):
    v = len(graph)
    p = np.zeros(graph.shape)
    for i in range(0,v):
        for j in range(0,v):
            p[i,j] = i
            if (i != j and graph[i,j] == 0):
                p[i,j] = -30000
                graph[i,j] = 30000 # set zeros to any large number which is bigger then the longest way

    for k in range(0,v):
        for i in range(0,v):
            for j in range(0,v):
                if graph[i,j] > graph[i,k] + graph[k,j]:
                    graph[i,j] = graph[i,k] + graph[k,j]
                    p[i,j] = p[k,j]

    return graph, p

def constructPath(p, i, j, path=[]):
    i,j = int(i), int(j)
    if(i==j):
      path.append(i)
    elif(p[i,j] == -30000):
      path = None
    else:
      constructPath(p, i, p[i,j], path);
      path.append(j)
    return path

def uberPool(uber_input):
    

graph_input, uber_input = read_input()
graph = createGraph(getMaxEdgeValue(graph_input), graph_input)
minPathGraph, minPathNextEdgeGraph = floydWarshallWithPathReconstruction(graph)
path = constructPath(minPathNextEdgeGraph,0,2)








#
