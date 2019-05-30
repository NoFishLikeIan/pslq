using namespace std;
using namespace Eigen;

#include <eigen3/Eigen/Dense>

template <typename T>

std::vector<T> deque_to_vec(std::deque<T> q)
{
  return std::vector<T> v(std::make_move_iterator(q.begin()),
                          std::make_move_iterator(q.end()));
}

MatrixXd I(int size)
{
  return MatrixXd::Identity(size, size);
}
