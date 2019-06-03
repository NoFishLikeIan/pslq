using namespace Eigen;
using namespace std;

#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <deque>
#include <string>
#include <tuple>
#include <eigen3/Eigen/Dense>
#include "utils.h"

using Mx = MatrixXd;
using Vx = VectorXd;
/* ----------
This function should return two vectors, s_k and y_k where:
s_k = sqrt( Σ_k->n x_j * x_j ) / s_1
y_k = x_k / t, ∀_k->n
---------- */
std::tuple<Vx, Vx> init_vectors(Vx x_i, int n)
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

  Vx y_k(deque_to_vec(y).data());
  Vx summatory(deque_to_vec(S).data());
  Vx s_k = 1 / t * summatory;

  return std::make_tuple(s_k, y_k);
}

/* ------
Construct the matrix H such that, the n − 1 columns of Hx are orthogonal.
Furthermore, they are orthogonal to x
and therefore form a basis for the relations of x
------ */
Mx init_H(int n, Vx S, Vx Y)
{
  Mx H(n, n - 1);
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

/* ------
Applies simple matrix reduction and update A, B and y
------ */
std::tuple<Mx, Mx, Mx, Vx> full_reduction(Mx H, Mx A, Mx B, Vx y, int n)
{
  for (int i = 2; i < n; i++)
  {
    for (int j = i - 1; i > 1; i--)
    {
      int t = round(H(i, j) / H(j, j));
      y(j) = y(j) + t * y(i);
      for (int k = 1; k < j; k++)
      {
        H(i, k) = H(i, k) - t * H(j, k);
      }
      for (int k = 1; k < n; k++)
      {
        A(i, k) = A(i, k) - t * A(j, k);
        B(k, j) = B(k, j) - t * B(k, i);
      }
    }
  }
  return std::make_tuple(H, A, B, y);
}

void psql(Vx x)
{
  int n = x.size();
  double gamma = 2 / sqrt(3);
  Mx A = I(n);
  Mx B = I(n);

  std::tuple<Vx, Vx> init_v = init_vectors(x, n);
  Vx s = std::get<0>(init_v);
  Vx y = std::get<1>(init_v);

  Mx H = init_H(n, s, y);

  std::tuple<Mx, Mx, Mx, Vx> reducted = full_reduction(H, A, B, y, n);
  Vx H = std::get<0>(reducted);
  Vx A = std::get<1>(reducted);
  Vx B = std::get<2>(reducted);
  Vx y = std::get<3>(reducted);

  /*
  Let Hx be the matrix defined in (1), and set A to be the Hermite reducing matrix of Hx.
  Let Q be the identity matrix
  */
}