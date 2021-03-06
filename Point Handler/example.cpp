#define _SCL_SECURE_NO_WARNINGS

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/index/rtree.hpp>

// to store queries results
#include <vector>

// just for output
#include <iostream>
#include <boost/foreach.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::point<float, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;

int main()
{
	// create the rtree using default constructor
	bgi::rtree<point, bgi::quadratic<4>> rtree;

	// create some values
	for ( unsigned i = 0 ; i < 10 ; ++i )
	{
		// create a point
		point p(i, 0);
		// insert new value
		rtree.insert(p);
	}

	// find values intersecting some area defined by a box
	box query_box(point(0, 0), point(5, 0));
	std::vector<point> result_s;
	rtree.query(bgi::intersects(query_box), std::back_inserter(result_s));

	// find 5 nearest values to a point
	std::vector<point> result_n;
	rtree.query(bgi::nearest(point(0, 0), 5), std::back_inserter(result_n));

	// display results
	std::cout << "spatial query box:" << std::endl;
	std::cout << bg::wkt<box>(query_box) << std::endl;
	std::cout << "spatial query result:" << std::endl;
	BOOST_FOREACH(point v, result_s)
		std::cout << v.get<0>() << "," << v.get<1>() << std::endl;

	std::cout << std::endl;

	std::cout << "knn query point:" << std::endl;
	std::cout << bg::wkt<point>(point(0, 0)) << std::endl;
	std::cout << "knn query result:" << std::endl;
	BOOST_FOREACH(point v, result_n)
		std::cout << v.get<0>() << "," << v.get<1>() << std::endl;
}