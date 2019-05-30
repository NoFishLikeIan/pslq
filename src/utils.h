#ifndef UTILS_H
#define UTILS_H

using namespace Eigen;
using namespace std;

#include <eigen3/Eigen/Dense>

template <typename T>

std::vector<T> deque_to_vec(std::deque<T> q);
MatrixXd I(int size);

#endif