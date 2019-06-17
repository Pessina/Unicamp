#include "solver.h"

void print(std::vector<int> const &input)
{
	for (int i = 0; i < input.size(); i++) {
		std::cout << input.at(i) << ' ';
	}
}

void printMatrix(std::vector<vector<int>> &matrix, Instance &instance) {
	for (int i = 0; i < instance.n + 1; i++) {
		for (int j = 0; j < instance.n + 1; j++) {
			std::cout << matrix[i][j] << ' ';
		}
		cout << " " << endl;
	}
}

double getDistance(Point p1, Point p2){
	double delta_x = p1.x - p2.x;
	double delta_y = p1.y - p2.y;

	return sqrt(delta_x * delta_x + delta_y * delta_y);
}

vector<int> solveBottomUp(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started){
	vector<int> sol;

	// generate index vector, to select subsets
	// vector<int> vindex(instance.n);
  // iota(vindex.begin(), vindex.end(), 0);
	// findSubSets(vindex, instance.n);
	vector<vector<int>> matrix = createGraph(instance);
	// printMatrix(matrix, instance);


	// g(i, S) = min {Cik + g(k, S - {k})}

	for(int i = 1; i < instance.n - 1; i++){
		sol.push_back(i);

		// get the time that has passed in seconds and check the timelimit
		auto done = chrono::high_resolution_clock::now();
		auto time = chrono::duration_cast<chrono::seconds>(done-started).count();

		if(time > timelimit){
			break;
		}
	}

	return sol;
}

vector<int> solveTopDown(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started){
	return solveBottomUp(instance, timelimit, started);
}

vector<vector<int>> findSubSets(vector<int> arr, int n) {
    vector<vector<int>> list;

		for (int i = 0; i < (int) pow(2, n); i++) {
        vector<int> subset;

        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) != 0)
                subset.push_back(arr[j]);
        }

        list.push_back(subset);
    }

		// consider every subset
    for (vector<int> subset : list)
    {
        // split the subset and print its elements
        for (int str: subset)
            cout << str << " ";
        cout << endl;
    }
  return list;
}

vector<vector<int>> createGraph (Instance &instance) {
		vector<vector<int>> matrix (instance.n + 1 ,vector<int>(instance.n + 1));
		for (int i = 0; i < instance.n + 1; i++) {
			for (int j = 0; j < instance.n + 1; j++) {
				// Create fake value that connects start to end
				if (i == instance.n) {
					matrix [i] [j] = std::numeric_limits<int>::max();;
					if (j == 0 || j == instance.n - 1) {
						matrix [i] [j] = 0;
					}
				}
				else if (j == instance.n) {
					matrix [i] [j] = std::numeric_limits<int>::max();;
					if (i == 0 || i == instance.n - 1) {
						matrix [i] [j] = 0;
					}
				}
				else {
					matrix [i] [j] = getDistance(instance.points[i], instance.points[j]);
				}
			}
		}

		return matrix;
}
