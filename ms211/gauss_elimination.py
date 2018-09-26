import numpy as np

matrix = np.array([ [7, 4, -2, 1, 14.308],
                    [3, 11, 4, -5, 25.744],
                    [-2, 3, 8, 2, -3.872],
                    [10, -5, 1, -3, 36.344]], dtype='f')

def triangle_matrix(matrix):
    for line_base in range(0, len(matrix)-1):
        for line_zero in range(line_base + 1, len(matrix)):
            m = matrix [line_zero][line_base]/matrix[line_base][line_base]
            matrix[line_zero] = matrix [line_zero] - m * matrix[line_base]
    return matrix

def calculate_solution(matrix):
    b_column = matrix.shape[1] - 1
    solution = []
    for line in reversed(range(0, len(matrix))):
        sum_resolved_x = 0
        for x in (range(line + 1, b_column)):
            sum_resolved_x = sum_resolved_x + matrix[line][x] * solution[x - (line + 1)]
        x = (matrix [line][b_column] - sum_resolved_x)/matrix[line][line]
        solution.insert(0, x)
    return solution

matrix = triangle_matrix (matrix)
solution = calculate_solution (matrix)

print (solution)
