import numpy as np

matrix = np.array([ [4, 0, -3, -2],
                    [1, 2, 2, 3],
                    [3, -4, 1, 9]], dtype='f')

print(matrix)

def triagle_matrix(matrix):
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

matrix = triagle_matrix(matrix)
solution = calculate_solution (matrix)

print (matrix)
print (solution)
