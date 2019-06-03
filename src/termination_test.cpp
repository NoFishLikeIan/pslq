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

double gamma = sqrt(4 / 3);

/* -----
Find maximum magnitude over diagonal
----- */
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

void test_stop(Mx H, Mx A, Mx B, Vx y, int n)
{
  int m = find_max(H, n);
}