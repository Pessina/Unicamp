#include "solver.h"
#define VISITED -1
#define MAX_DISTANCE 2000000000

void print(std::vector<int> const &input)
{
	for (int i = 0; i < input.size(); i++) {
		std::cout << input.at(i) << ' ';
	}
}

void printMatrix(std::vector<vector<double>> &matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
				cout << matrix[i][j] << ' ';
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

	vector<vector<double>> points = createGraph(instance);
	vector<vector<double>> path(points.size(), vector<double>((1 << points.size()) - 1, MAX_DISTANCE));
	// The new idea is use a list with all the numbers, and remove each one in each step to recusevly check the minumun path
	// vector<int> visited (points.size(), 0);
	double minimumDistance = memoizationSolution(points, 0, 1, path);
	printMatrix (path);

  cout << "Distance: " << minimumDistance << endl;

	// g(i, S) = min {Cik + g(k, S - {k})}

	return solveBottomUp(instance, timelimit, started);
}

double memoizationSolution(const vector<vector<double>>& points, int point, int visited, vector<vector<double>>& path) {

		// Visited All cities return to start point
    if(visited == ((1 << points.size()) - 1))
        return points[point][0];

		// If the value on table is already updated just return
    if(path[point][visited] != MAX_DISTANCE)
        return path[point][visited];

		// Find minumun path
    for(int i = 0; i < points.size(); ++i) {
        if(i == point || (visited & (1 << i)))
            continue;

        double distance = points[point][i] + memoizationSolution(points, i, visited | (1 << i), path);
        if(distance < path[point][visited])
            path[point][visited] = distance;
    }

    return path[point][visited];
}


vector<vector<double>> createGraph (Instance &instance) {
		vector<vector<double>> matrix (instance.n + 1,vector<double>(instance.n + 1));
		for (int i = 0; i < instance.n + 1; i++) {
			for (int j = 0; j < instance.n + 1; j++) {
				// Create fake value that connects start to end with distance 0
				if (i == instance.n || j == instance.n) {
					matrix [i] [j] = MAX_DISTANCE;
					if (j == 0 || j == instance.n - 1 || i == 0 || i == instance.n - 1) {
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
