#include <iostream>
#include <cmath>

#include "poaky.h"

int main(){
  ray ray1;
  ray1.p.x = 1;

  plane plane1;
  std::cout << plane1 << std::endl;
  
  sphere sphere1(4.5);
  std::cout << sphere1 << std::endl;

  plane1.intersect(ray1);
  UVec3 N_pl = plane1.normal(ray1);

  std::cout << "Plane normal: " << N_pl << std::endl;

  Point3 p(1.0, 2.0, 3.0);
  Point3 p2(p);
  p.x = 5.0;
  std::cout << p2 << std::endl;

  UVec3 v(0.2, 0.1, 0.8);
  std::cout << v << std::endl;

  double l = 0.01;
  double m = -0.005;
  double n = std::sqrt(1 - l*l - m*m);
  ray rtest(Point3(0.5, -0.32, 0), UVec3(l, m, n));
  sphere stest(5);
  
  std::cout << "Initial ray: " << rtest << std::endl;
  stest.intersect(rtest);
  std::cout << "After sphere intersection: " << rtest << std::endl;
  UVec3 N_s = stest.normal(rtest);
  std::cout << "Sphere normal: " << N_s << std::endl;
  reflect(rtest, N_s);
  std::cout << "Mirror reflection: " << rtest << std::endl;

  // TODO: solve this
  //Vec3 v1(0.5, 0, 0);
  //UVec3 v2 = 2 * v1;
}
