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

/*
Swaps m element of a vector for the m+1 and return copy
*/
VectorXd push_item(VectorXd vector, int m)
{
  VectorXd newVector(vector.size());
  if (m == vector.size())
  {
    newVector << vector;
  }
  else
  {

    newVector << vector(0, m - 1), vector(m + 1), vector(m), vector(m + 2, vector.size());
  }

  return newVector;
}

/*
Swap row "m" of matrix for row "m+1"
*/
MatrixXd push_row(MatrixXd L, int m)
{
  MatrixXd L_prime(L.size());
  if (m == L.rows())
  {
    L_prime << L;
  }
  else
  {
    L_prime << L.bottomRows(m - 1), L.row(m + 1), L.row(m), L.topRows(m + 2);
  }
  return L_prime;
}

/*
Swap column "m" of matrix for column "m+1"
*/
MatrixXd push_column(MatrixXd L, int m)
{
  MatrixXd L_prime(L.size());
  if (m == L.cols())
  {
    L_prime << L;
  }
  else
  {
    L_prime << L.leftCols(m - 1), L.col(m + 1), L.col(m), L.rightCols(m + 2);
  }
  return L_prime;
}

/*
Compute the squared distance of two values
 */
double distance_squared(double a, double b)
{
  return sqrt(a * a + b * b);
}
