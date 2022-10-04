#include "sphere_intersect_valid.h"

Sphere_3 sphere_tocgal (sphere s) {
  // Convert a poaky sphere to a CGAL Sphere_3 object.
  Point_3 C(0.0, 0.0, s.R); // Sphere center.
  Sphere_3 cgal_s(C, s.R * s.R);
  return cgal_s;
}

Line_3 ray_tocgal (ray r) {
  // Convert a poaky ray to a CGAL Line_3 object.
  Point_3 P(r.p.x, r.p.y, r.p.z);
  Vector_3 V(r.v.l, r.v.m, r.v.n);
  Line_3 L(P, V);
  return L;
}

Point_3f intersection_to_point (CGAL::Object inter) {
  // Convert an intersection result to a 'normal' Point_3.
  // The intersection must designate a point result.
  Inter cpoint_pair = CGAL::object_cast <Inter>(inter);
  CPoint_3 cpoint = cpoint_pair.first;
  Point_3f point = Point_3f(to_double(cpoint.x()),
                            to_double(cpoint.y()),
                            to_double(cpoint.z()));
  return point;
}

bool is_closer_tolocalplane (Point_3f p1, Point_3f p2) {
  // Tell whether p1 is closer to the local plane than p2.
  return (std::abs(p1.z()) < std::abs(p2.z()));
}

ray foo (const sphere s, const ray r) {
  std::cout << "CGAL sphere intersection:" << std::endl;

  Sphere_3 S = sphere_tocgal(s);
  Line_3 L = ray_tocgal(r);
  
  // Intersection
  std::vector <CGAL::Object> intersecs;
  CGAL::intersection(S, L, std::back_inserter(intersecs));
  std::cout << "Number of intersections: " << intersecs.size() << std::endl;
 
  if (intersecs.size() == 2) {
    Point_3f p1p = intersection_to_point(intersecs[0]);
    Point_3f p2p = intersection_to_point(intersecs[1]);

    std::cout << "Point1: " << p1p << std::endl;
    std::cout << "Point2: " << p2p << std::endl;

    // Select the closest point to z=0.
    std::vector<Point_3f> v {p1p, p2p};
    auto pmin = std::min_element(v.begin(), v.end(), is_closer_tolocalplane);
    Point_3f p = *pmin;
    std::cout << "Point: " << p << std::endl;

    // Check for intersection beyond hemisphere.
    // TODO

    ray r_valid(Point3(p1p.x(), p1p.y(), p1p.z()),
              UVec3(r.v.l, r.v.m, r.v.n));
  return r_valid;
  } else {
    std::cout << "Error case: No intersection found." << std::endl;
    ray r_error = ray();
    r_error.code = 1;
    return r_error;
  }
}
