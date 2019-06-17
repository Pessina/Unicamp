#include "solver.h"
#define VISITED -1
#define MAX_DISTANCE 2147483647

void print(std::vector<int> const &input)
{
	for (int i = 0; i < input.size(); i++) {
		std::cout << input.at(i) << ' ';
	}
}

void printMatrix(std::vector<vector<double>> &matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {
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

	vector<vector<double>> cities = createGraph(instance);
	vector<vector<double>> state(cities.size());

    for(auto& neighbors : state)
        neighbors = vector<double>((1 << cities.size()) - 1, MAX_DISTANCE);

    cout << "minimum: " << tsp(cities, 0, 1, state) << endl;

	// g(i, S) = min {Cik + g(k, S - {k})}

	return solveBottomUp(instance, timelimit, started);
}

double tsp(const vector<vector<double>>& cities, int pos, int visited, vector<vector<double>>& state)
{
    if(visited == ((1 << cities.size()) - 1))
        return cities[pos][0]; // return to starting city

    if(state[pos][visited] != MAX_DISTANCE)
        return state[pos][visited];

    for(int i = 0; i < cities.size(); ++i)
    {
        // can't visit ourselves unless we're ending & skip if already visited
        if(i == pos || (visited & (1 << i)))
            continue;

        double distance = cities[pos][i] + tsp(cities, i, visited | (1 << i), state);
        if(distance < state[pos][visited])
            state[pos][visited] = distance;
    }

    return state[pos][visited];
}


vector<vector<double>> createGraph (Instance &instance) {
		vector<vector<double>> matrix (instance.n + 1 ,vector<double>(instance.n + 1));
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
