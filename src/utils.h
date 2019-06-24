#ifndef UTILS_H
#define UTILS_H

using namespace Eigen;
using namespace std;

#include <eigen3/Eigen/Dense>

template <typename T>

std::vector<T> deque_to_vec(std::deque<T> q);
MatrixXd I(int size);
VectorXd push_item(VectorXd vector, int m);
MatrixXd push_row(MatrixXd L, int m);
MatrixXd push_column(MatrixXd L, int m);
double distance_squared(double a, double b);
#endif