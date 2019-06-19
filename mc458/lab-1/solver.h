#ifndef SOLVER_H
#define SOLVER_H
#include <vector>
#include <map>
#include <cmath>
#include "point.h"
#include "instance.h"
#include <bits/stdc++.h>
#include <algorithm>
#include <chrono>

#define M 32

using namespace std;

double getDistance(Point p1, Point p2);
vector<int> solveBottomUp(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started);
vector<int> solveTopDown(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started);
double memoizationSolution(const vector<vector<double>>& points, int point, string notVisited, map<string, vector<tuple<double, int>>>& path);
vector<vector<double>> createGraph (Instance &instance);
void print(vector<int> const &input);
void printMatrix(vector<vector<double>> &matrix);
double getDistance(Point p1, Point p2);
vector<string> findSubSets(vector<int> arr);
map<string, vector<tuple<double, int>>> createMap (vector<string> subsets, int size);
bool findString (string s, int number);
string removeString (string s, int number);
vector<int> splitString(string str);
vector<int> recreatePath (map<string, vector<tuple<double, int>>>& path, string sequence, int pos);
#endif // SOLVER_H
