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

vector<string> findSubSets(vector<int> arr) {
    vector<string> list;

		for (int i = 0; i < pow(2, arr.size()); i++) {
        string subset;
        for (int j = 0; j < arr.size(); j++) {
            if ((i & (1 << j)) != 0)
                subset = subset +  std::to_string(arr[j]);
        }
        list.push_back(subset);
    }

  return list;
}

map<string, vector<tuple<double, int>>> createMap (vector<string> subsets, int size) {
	map<string, vector<tuple<double, int>>> dictionary;

	for (string subset : subsets) {
		vector<tuple<double, int>> tuples (size);
		for (tuple<double, int>& element : tuples) {
			element = {MAX_DISTANCE, -1};
		}
		dictionary.insert({subset, tuples});
	}

	return dictionary;
}

bool findString (string s, int number) {
	ostringstream aux;
	aux << number;
	string element = aux.str();
	if (s.find(element) != string::npos) {
		return true;
	}else {
		return false;
	}
}

string removeString (string s, int number) {
	ostringstream aux;
	aux << number;
	string element = aux.str();
	s.erase(remove(s.begin(), s.end(), element[0]), s.end());

	return s;
}

vector<int> recreatePath (map<string, vector<tuple<double, int>>>& path, string sequence, int pos) {
	vector<int> bestPath;

	if (sequence == "") {
		vector<int> v = {0};
		return v;
	}

	int nextPos = get<1>(path.at(sequence)[pos]);
	string nextSequence = removeString(sequence, nextPos);
	bestPath = recreatePath(path, nextSequence, nextPos);
	bestPath.insert(bestPath.begin(), pos);

	return bestPath;
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
	// Create all path subsets
	vector<int> sequence(instance.n + 1);
	iota(begin(sequence), end(sequence), 0);
	vector<string> subsets;
	subsets = findSubSets(sequence);

	// Create memoization datastructure
	// The key is the subset sequence (eq 123), it stores a list of tuples with the best distance and path
	map<string, vector<tuple<double, int>>> path;
	path = createMap(subsets, instance.n + 1);

	// Initialize graph and visited points
	vector<vector<double>> points = createGraph(instance);
	ostringstream visited;
	copy(sequence.begin(), sequence.end(), ostream_iterator<int>(visited, ""));

	// The new idea is use a list with all the numbers, and remove each one in each step to recusevly check the minumun path
	string sequenceStr = visited.str().c_str();
	sequenceStr = removeString(sequenceStr, 0);
	double minimumDistance = memoizationSolution(points, 0, sequenceStr, path);

  cout << "Distance: " << minimumDistance << endl;

	vector<int> bestPath;
	bestPath = recreatePath(path, sequenceStr, 0);
	bestPath.pop_back();
	print(bestPath);
	// g(i, S) = min {Cik + g(k, S - {k})}

	return bestPath;
}

double memoizationSolution(const vector<vector<double>>& points, int point, string visited, map<string, vector<tuple<double, int>>>& path) {

		tuple<double, int>& pointTuple = path.at(visited)[point];

		// Visited All cities return to start point
    if(visited == "")
        return points[point][0];

		// If the value on table is already updated just return
    if(get<0>(pointTuple) != MAX_DISTANCE)
        return get<0>(pointTuple);

		// Find minumun path
    for(int i = 0; i < points.size(); ++i) {
        if(i == point || !findString(visited, i))
            continue;

				string newVisited =  removeString(visited, i);
        double distance = points[point][i] + memoizationSolution(points, i, newVisited, path);
        if(distance < get<0>(pointTuple)){
					get<0>(pointTuple) = distance;
					get<1>(pointTuple) = i;
				}
    }

    return get<0>(pointTuple);
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
