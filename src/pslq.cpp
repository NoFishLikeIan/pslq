using namespace Eigen;
using namespace std;

#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <deque>
#include <eigen3/Eigen/Dense>
#include "utils.h"

/* ----------
This function should return two vectors, s_k and y_k where:
s_k = sqrt( Σ_k->n x_j * x_j ) / s_1
y_k = x_k / t, ∀_k->n
---------- */
std::tuple<VectorXd, VectorXd> s(VectorXd x_i, int n)
{
  double s_n = x_i[n - 1];
  double t = s_n;
  double backward_running_sum = s_n * s_n;

  deque<double> S{sqrt(backward_running_sum)};
  deque<double> y{s_n / t};

  for (int k = n; k > 0; k--)
  {
    double toAdd = x_i[k] * x_i[k];
    double newSum = toAdd + backward_running_sum;

    backward_running_sum = newSum;

    S.push_front(newSum);
    y.push_front(x_i[k] / t);
  }

  VectorXd y_k(deque_to_vec(y).data());
  VectorXd summatory(deque_to_vec(S).data());
  VectorXd s_k = 1 / t * summatory;

  return std::make_tuple(s_k, y_k);
}

/* ------
Construct the matrix H such that, the n − 1 columns of Hx are orthogonal.
Furthermore, they are orthogonal to x
and therefore form a basis for the relations of x
------ */
MatrixXd computeH(int n, VectorXd S, VectorXd Y)
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
      H(i, i) = S(i + 1) / S(i);
    }
    for (int j = 1; j++; j < i - 1)
    {
      H(i, j) = -(Y(i) * Y(j)) / (S(j) + S(j + 1));
    }
  }

  return H;
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