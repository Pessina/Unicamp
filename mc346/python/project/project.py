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

            string_splitted = string.split(' ')
            if string_splitted [0] == '':
                string = ''.join([str(x) for x in string[1:]])

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
    graph = np.zeros((max_index,max_index), dtype='f')

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
                p[i,j] = -float('Inf')
                graph[i,j] = float('Inf') # set zeros to any large number which is bigger then the longest way

    for k in range(0,v):
        for i in range(0,v):
            for j in range(0,v):
                if graph[i,j] > graph[i,k] + graph[k,j]:
                    graph[i,j] = graph[i,k] + graph[k,j]
                    p[i,j] = p[k,j]

    return graph, p

# Get all vertices of the path between i and j
def constructPath(p, i, j, path):
    i,j = int(i), int(j)
    if(i==j):
      path.append(i)
    elif(p[i,j] == -float('Inf')):
      path = None
    else:
      constructPath(p, i, p[i,j], path);
      path.append(j)
    return path

def calculateInconvenience (first, second, path_graph, path_next_graph):
    first = first.split(' ')
    second = second.split(' ')
    path = []
    inconvenience_1 = None
    inconvenience_2 = None

    # If the passenger is on travel
    # We use calculate the alredy made path, and use the remaining path to
    # calculate inconvenience
    if len(first) == 3:
        first[0] = first[2]

    # Assing value to the path edges
    A = int(first [0])
    B = int(first [1])
    C = int(second [0])
    D = int(second [1])

    # We assume that we have a possible path between A and B
    # It means travel time is no inf
    first_travel_time = path_graph[A][B]
    second_travel_time = path_graph[C][D]

    if path_graph[A][C] == float('inf') or path_graph[C][B] == float('inf'):
        return 1.5, []

    # Possible paths A C B D or A C D B
    first_time_with_passenger_1 = path_graph[A][C] + path_graph[C][B]
    second_time_with_passenger_1 = path_graph[C][B] + path_graph [B][D]
    first_inconvenience_1 = first_time_with_passenger_1/first_travel_time
    second_inconvenience_1 = second_time_with_passenger_1/second_travel_time
    inconvenience_1 = max([first_inconvenience_1, second_inconvenience_1])

    first_time_with_passenger_2 = path_graph[A][C] + path_graph[C][D] + path_graph[D][B]
    second_time_with_passenger_2 = path_graph[C][D]
    first_inconvenience_2 = first_time_with_passenger_2/first_travel_time
    second_inconvenience_2 = second_time_with_passenger_2/second_travel_time
    inconvenience_2 = max([first_inconvenience_2, second_inconvenience_2])

    # Return the smaller inconvenience if some of than is smaller than 1.4
    if inconvenience_1 < inconvenience_2:
        path += [A, C, B, D]
        return inconvenience_1, path
    else:
        if inconvenience_2 < 1.4:
            path += [A, C, D, B]
            return inconvenience_2, path
        else:
            return 1.5, []

# Iterate throw all pairs possibilities to find the pair with the smallest inconvenience
# If the smaller inconvenience is smaller than 1.4 they share the uber, otherwise they do their on paths
def uberPool(uber_input, min_path_graph, min_path_next_edge_graph):
    min_inconvenience = 1.4
    best_path = []
    passenger1 = None
    passenger2 = None
    for first_passenger in uber_input:
        for second_passenger in uber_input:
            if first_passenger == None or second_passenger == None:
                continue
            if len(second_passenger.split(' ')) == 3 or first_passenger == second_passenger:
                continue
            else:
                inconvenience, path = calculateInconvenience (first_passenger, second_passenger, min_path_graph, min_path_next_edge_graph)
                if inconvenience < min_inconvenience:
                    passenger1 = first_passenger
                    passenger2 = second_passenger
                    min_inconvenience = inconvenience
                    best_path = path

    if best_path != []:
        passenger1 = uber_input.index(passenger1)
        uber_input [passenger1] = None
        passenger1 += 1
        passenger2 = uber_input.index(passenger2)
        uber_input [passenger2] = None
        passenger2 += 1

    return best_path, uber_input, [passenger1, passenger2]

graph_input, uber_input = read_input()
graph = createGraph(getMaxEdgeValue(graph_input), graph_input)
min_path_graph, min_path_next_edge_graph = floydWarshallWithPathReconstruction(graph)

path_list = []

# Calculate the pair with inconvenience smaller than 1.4
while True:
    path, uber_input, passengers = uberPool(uber_input, min_path_graph, min_path_next_edge_graph)
    if (path != []):
        path_list.append((path, passengers))
    else:
        break

# Append other uber requests, without pairs
if (uber_input != []):
    for element in uber_input:
        if element == None:
            continue
        index = uber_input.index(element)
        element = element.split(' ')
        path = []
        if len(element) == 3:
            path += [element[0], element[1]]
            path_list.append((path, [index + 1]))
        else:
            path += [element[0], element[1]]
            path_list.append((path, [index + 1]))

for element in path_list:
    if len(element[1]) == 1:
        print ("passageiro: {0} ".format(' '.join([str(x) for x in element[1]])), end='')
        print ("percurso:", end='')
    else:
        print ("passageiros: {0} ".format(' '.join([str(x) for x in element[1]])), end='')
        print ("percurso: ", end='')
    for vertice in element[0]:
        print(" {0}".format(str(vertice)), end='')
    print('')
