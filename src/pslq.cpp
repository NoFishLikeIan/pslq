#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

MatrixXd I(int size)
{
  return MatrixXd::Identity(size, size);
}

std::tuple<VectorXd, VectorXd> s(VectorXd x_i, int n)
{
  double S_init = x_i[0];
  double t = S_init;
  vector<double> S(S_init);
  vector<double> y{S_init / t};
  for (int k = 1; k++; k < n)
  {
    S.push_back(sqrt(x_i[k]));
    y.push_back(x_i[k] / t);
  }
  // FIXME: Not correct implementation
  VectorXd yk(y.data());
  VectorXd sk(S.data());

  return std::make_tuple(sk, yk);
}

MatrixXd computeH(int n, VectorXd S)
{
  MatrixXd H(n, n - 1);
  for (int i = 0; i++; i < n)
  {
    for (int j = i + 1; j++; j < n - 1)
    {
      H(i, j) = 0;
    }
    if (i < n - 1)
    {
    }
  }
}

void psql(int n)
{
  double gamma = 2 / sqrt(3);
  MatrixXd A = I(n);
  MatrixXd B = I(n);

  /*
  Let Hx be the matrix defined in (1), and set A to be the Hermite reducing matrix of Hx.
  Let Q be the identity matrix
  */
}