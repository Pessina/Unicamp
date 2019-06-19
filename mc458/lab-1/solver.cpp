#include "solver.h"
#define VISITED -1
#define MAX_DISTANCE 2000000000

struct compare {
    bool operator()(const std::string& first, const std::string& second) {
        return first.size() < second.size();
    }
};

vector<int> solveBottomUp(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started){
  // Inicizaliza a variável de caminhos possíveis
	vector<int> sequence(instance.n + 1);
	iota(begin(sequence), end(sequence), 0);
	sequence.erase(sequence.begin());
	vector<string> subsets;
	subsets = findSubSets(sequence);

  // Cria a estrutura usada na memoização
	map<string, vector<tuple<double, int>>> path;
	path = createMap(subsets, instance.n + 1);

  // Inicizaliza o grafo, na forma de uma matriz de adjacência
	vector<vector<double>> points = createGraph(instance);

  // Ordena os caminhos possíveis pelo tamanho, para primeiro percorrermos os casos menores na abordagem bottomUp
	compare c;
	sort(subsets.begin(), subsets.end(), c);

	for (string subset : subsets) {
		for (int i = 0; i < points.size(); i++) {
				tuple<double, int>& tuplePos = path.at(subset)[i];
				vector<int> splited;
				splited = splitString(subset);

        // Inicizaliza o caso base, onde só tem um elemento não visitado e apenas voltamos ao início
				if (subset.size() == 1) {
					get<0>(tuplePos) = points[i][splited[0]] + points[splited[0]][0];
					get<1>(tuplePos) = splited[0];
				}
        // Encontra o menor caminho, baseado na mesma lógica do topDown
        // g(i, S) = min {Cik + g(k, S - {k})}
        // i: ponto inicial. k: próximo ponto. S: conjunto de pontos não visitados. Cik: custo do ponto i para k
				else {
					double minimun = MAX_DISTANCE;
					int bestPos;
					for (int nextPos : splited) {
						string nextSequence = removeString(subset, nextPos);
						double distance =  points[i][nextPos] + get<0>(path.at(nextSequence)[nextPos]);
						if (distance < minimun) {
							minimun = distance;
							get<0>(tuplePos) = distance;
							get<1>(tuplePos) = nextPos;
						}
					}
			}
		}
	}

  vector<int> bestPath;
  bestPath = recreatePath(path, subsets[subsets.size()-1], 0);
  bestPath.pop_back();

	// for(int i = 1; i < instance.n - 1; i++){
	// 	sol.push_back(i);
  //
	// 	// get the time that has passed in seconds and check the timelimit
	// 	auto done = chrono::high_resolution_clock::now();
	// 	auto time = chrono::duration_cast<chrono::seconds>(done-started).count();
  //
	// 	if(time > timelimit){
	// 		break;
	// 	}
	// }

	return bestPath;
}

vector<int> solveTopDown(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started){
	// Inicizaliza a variável de caminhos possíveis
	vector<int> sequence(instance.n + 1);
	iota(begin(sequence), end(sequence), 0);
	vector<string> subsets;
	subsets = findSubSets(sequence);

  // Cria a estrutura de memoização
	map<string, vector<tuple<double, int>>> path;
	path = createMap(subsets, instance.n + 1);

  // Inicizaliza o grafo na forma de matriz de adjacência e os pontos visitados
	vector<vector<double>> points = createGraph(instance);
	ostringstream visited;
	copy(sequence.begin(), sequence.end(), ostream_iterator<int>(visited, ""));
	string sequenceStr = visited.str().c_str();

  // Remove o elemento 0, pois ele é o ponto de partida
	sequenceStr = removeString(sequenceStr, 0);

  // Calcula o melhor caminho
	double minimumDistance = memoizationSolution(points, 0, sequenceStr, path);

	vector<int> bestPath;
	bestPath = recreatePath(path, sequenceStr, 0);
	bestPath.pop_back();

	return bestPath;
}

double memoizationSolution(const vector<vector<double>>& points, int point, string notVisited, map<string, vector<tuple<double, int>>>& path) {

		tuple<double, int>& pointTuple = path.at(notVisited)[point];

    // Se visitou todos os pontos, apenas retorna ao início
    if(notVisited == "")
        return points[point][0];

    // Se o valor na estiver na memoização apenas retorna o valor
    if(get<0>(pointTuple) != MAX_DISTANCE)
        return get<0>(pointTuple);

    // Encontra o menor caminho baseado na seguinte recorrência
    // g(i, S) = min {Cik + g(k, S - {k})}
    // i: ponto inicial. k: próximo ponto. S: conjunto de pontos não visitados. Cik: custo do ponto i para k
    for(int i = 0; i < points.size(); ++i) {
        if(i == point || !findString(notVisited, i))
            continue;

				string newNotVisited =  removeString(notVisited, i);
        double distance = points[point][i] + memoizationSolution(points, i, newNotVisited, path);
        if(distance < get<0>(pointTuple)){
					get<0>(pointTuple) = distance;
					get<1>(pointTuple) = i;
				}
    }

    return get<0>(pointTuple);
}

// Cria um grafo na forma de matriz de adjacência, onde o peso das arestas é a distância.
// Para solucionarmos o problema do caixeiro viajante, mas considerando que ele parte de um ponto e finaliza em outro ponto.
// Adicionamos um ponto ao nosso grafo que liga o início ao fim com peso 0, o que força que nosso algorimo quando ele voltar ao início ele sempre irá conter a sequência
// fim - ponto adicional - começo. Retornando o valor certo para o nosso problema
vector<vector<double>> createGraph (Instance &instance) {
		vector<vector<double>> matrix (instance.n + 1,vector<double>(instance.n + 1));
		for (int i = 0; i < instance.n + 1; i++) {
			for (int j = 0; j < instance.n + 1; j++) {
        // Cria o ponto fake que liga o início ao fim com peso 0
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

void print(vector<int> const &input) {
	for (int i = 0; i < input.size(); i++) {
		std::cout << input.at(i) << " ";
	}
}

void printMatrix(vector<vector<double>> &matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
				cout << matrix[i][j] << ' ';
		}
		cout << " " << endl;
	}
}

double getDistance(Point p1, Point p2) {
	double delta_x = p1.x - p2.x;
	double delta_y = p1.y - p2.y;

	return sqrt(delta_x * delta_x + delta_y * delta_y);
}

// Cria todas as as combinações possiveis de caminhos, no caso são 2^n casos
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

// Cria a estrutura de dados usada em nossa resolução do problema, a chave é uma string que representa os pontos que não foram visitados
// O valor da chave, é um vetor com p posições, onde p é o número de pontos. Cada posição do vetor armazena a menor distância e o próximo ponto que minimiza o caminhos
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

// Verifica se o número está contido na string
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

// Remove um número de uma string
string removeString (string s, int number) {
	ostringstream aux;
	aux << number;
	string element = aux.str();
	s.erase(remove(s.begin(), s.end(), element[0]), s.end());

	return s;
}

// Transforma uma string em um vetor de inteiros
vector<int> splitString(string str) {
  vector<int> arr;

  for (int i = 0; i < str.size(); i++) {
    int n = (int) str[i] - 48;
    arr.push_back(n);
  }

	return arr;
}

// Reconstrói o melhor caminho, dada a estrutura de memoização
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
