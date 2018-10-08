import numpy as np

matrix = np.array([ [1, 1, 1],
                    [2, 1, -1],
                    [3, 2, 0]], dtype='f')
matrixL = np.zeros((len(matrix), len(matrix)))

print(matrix)

# Initialize matrixL
for line in range(0, len(matrixL)):
    matrixL[line][line] = 1

def LU_factorization(matrix, matrixL):
    for line_base in range(0, len(matrix)-1):
        for line_zero in range(line_base + 1, len(matrix)):
            m = matrix [line_zero][line_base]/matrix[line_base][line_base]
            matrix[line_zero] = matrix [line_zero] - m * matrix[line_base]
            matrixL [line_zero] [line_base] = m
    return matrix, matrixL

matrixU, matrixL = LU_factorization(matrix, matrixL)

print(matrixU)
print(matrixL)
