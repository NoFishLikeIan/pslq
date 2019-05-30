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

/* ----------
This function should return two vectors, s_k and y_k where:
s_k = sqrt( Σ_k->n x_j * x_j ) / s_1
y_k = x_k / t, ∀_k->n
---------- */
std::tuple<VectorXd, VectorXd> s(VectorXd x_i, int n)
{
  double s_0 = x_i[0];
  double t = s_0;
  double running_sum = s_0 * s_0;

  vector<double> S{sqrt(s_0 * s_0)};
  vector<double> y{s_0 / t};

  for (int k = 1; k++; k < n)
  {
    double toAdd = x_i[k] * x_i[k];
    double newSum = toAdd + running_sum;

    running_sum = newSum;

    S.push_back(newSum);
    y.push_back(x_i[k] / t);
  }

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