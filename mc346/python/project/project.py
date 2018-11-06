# Store all values from input related to graph construction
graph_input = []
# Store all values from input related to uber request
uber_input = []

flag_read_uber = 0

# Read input
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

# Create graph
graph = {}

for element in graph_input:
    element_splitted = element.split(' ')
    start_vertice = element_splitted [0]
    end_vertice = element_splitted [1]
    weight_edge = element_splitted [2]

    if start_vertice in graph:
        graph[start_vertice].append((end_vertice, weight_edge))
    else:
        graph[start_vertice] = [(end_vertice, weight_edge)]
