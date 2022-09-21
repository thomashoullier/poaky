#include <iostream>
#include "ray.h"
#include "plane.h"

int main(){
  ray ray1;
  plane plane1;

  plane1.intersect(ray1);

  std::cout << "Hello World " << ray1.p.x << std::endl;

  // TODO:
  // * Create very basic objects such as point in 3d, and lmn vector in 3d.
  //   this simplifies greatly the expression of computations.
  //   A ray is a point and lmn vector.
}