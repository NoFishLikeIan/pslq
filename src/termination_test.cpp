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
#include <algorithm>
#include "utils.h"

using Mx = MatrixXd;
using Vx = VectorXd;

double gamma = sqrt(4 / 3);

/*
Find maximum magnitude over diagonal
 */
int find_max(Mx H, int n)
{
  double max_gamma = 0;
  int max_i = 0;

  for (int i = 0; i < n - 1; i++)
  {
    double magn = abs(H(i, i)) * gamma;
    if (magn > max_gamma)
    {
      max_gamma = magn;
      max_i = i;
    }
  }

  return max_i;
}

void updated_h(Mx &H, int m, int n)
{
  double t0 = distance_squared(H(m, m), H(m, m + 1));
  double t1 = H(m, m) / t0;
  double t2 = H(m, m + 1) / t0;
  for (int i = m; i < n; i++)
  {
    double t3 = H(i, m);
    double t4 = H(i, m + 1);
    H(i, m) = t1 * t3 + t2 * t4;
    H(i, m + 1) = -t2 * t3 + t1 * t4;
  }
}

bool test_stop(Mx H, Mx A, Mx B, Vx y, int n)
{

  // Select m such that gamma(abs(H_i,j)) is maximal when i = m.
  int m = find_max(H, n);

  // Exchange entries m and m + 1
  // of y,
  Vx y_prime = push_item(y, m);
  // corresponding rows of A and H,
  Mx A_prime = push_row(A, m);
  Mx H_prime = push_row(H, m);
  // and corresponding columns of B.
  Mx B_prime = push_column(A, m);

  if (m <= n - 2)
  {
    updated_h(H_prime, m, n);
  }

  return false;
}