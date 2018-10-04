import numpy as np
import copy

matrix = np.array([ [10, 2, 1, 7],
                    [1, 5, 1, -8],
                    [2, 3, 10, 6]], dtype='f')

x_aproximation = [0.7, -1.6, 0.6]

print (matrix)

def create_C_matrix (matrix):
    for i in range(0, len(matrix)):
        matrix [i] = matrix[i]/matrix[i][i]
        matrix[i][i] = 0
    return matrix

def next_solution_jacobi(matrix, x):
    x_new = []
    for i in range(0, len(matrix)):
        x_line = 0
        for j in range (0, len(matrix)):
            x_line = x_line - matrix[i][j] * x[j]
        x_line = x_line + matrix[i][len(matrix)]
        x_new.append(x_line)
    return x_new

def next_solution_seidel(matrix, x):
    for i in range(0, len(matrix)):
        x_line = 0
        for j in range (0, len(matrix)):
            x_line = x_line - matrix[i][j] * x[j]
        x_line = x_line + matrix[i][len(matrix)]
        x[i] = x_line
    return x

def get_diff_x (new_aproximation, old_aproximation):
    max_value = float("-inf")
    for i in range (0, len(new_aproximation)):
        if abs(new_aproximation[i] - old_aproximation[i]) > max_value:
            max_value = abs(new_aproximation[i] - old_aproximation[i])
    return max_value

def gauss_jacobi(matrix, x, iter, error):
    i = 0
    while i < iter:

        x_new = next_solution_jacobi(matrix, copy.deepcopy(x))
        if(get_diff_x(x_new, x) < error):
            break

        x = x_new
        i = i + 1

    return x

matrix = create_C_matrix(matrix)
print (matrix)
print (gauss_jacobi(matrix, x_aproximation, 3, 10**-5))