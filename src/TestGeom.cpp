/*
 * TestGeom.cpp
 *
 *  Created on: 05.02.2014
 *      Author: bzfvierh
 */

#include "TestGeom.h"
#include <math.h>

namespace SDgeom {

TestGeom::TestGeom(SCIP* _scip) :
      scip_(_scip)
      ,nSuccess_(0)
      ,eps_(1e-9)
	  ,ndim_(0)

{ }

TestGeom::~TestGeom()
{
   // TODO Auto-generated destructor stub
}

HyperCube TestGeom::unitCube() const {
   HyperCube cube;
   for (int i = 0; i<ndim_; ++i)
      cube.addDim(0, 1.0);
   return cube;
}



void TestGeom::testEqual(double a, double b) {
   // std::cout << "testing equality of " << a << " and " << b << std::endl;
   if (SCIPisEQ(scip_,a,b))
      ++nSuccess_;
   else {
      std::cout << "Test " << nSuccess_ + 1 << " failed." << std::endl;
      assert(false);
   }
}




void TestGeom::testContains() {
   std::cout << "-- Testing cube.contains(vector)" << std::endl;
   HyperCube cube;
   cube = unitCube();
   Vector vec(ndim_);
   /* Not contained */
   vec.setComponent(0,2.0);
   test(cube.contains(scip_,vec) == false);
   /* Contained */
   vec.setComponent(0,0.5);
   test(cube.contains(scip_,vec) == true);
   /* Still contained */
   vec.setComponent(1,1 + 1e-10);
   test(cube.contains(scip_,vec) == true);
   /* Not contained anymore */
   vec.setComponent(1,1 + 2e-9);
   test(cube.contains(scip_,vec) == false);
}

void TestGeom::testIsOnFace() {
   std::cout << "-- Testing cube.isOnFace(vector)" << std::endl;
   HyperCube cube;
   cube = unitCube();
   Vector vec(ndim_);
   for (int i = 0; i< ndim_; ++i) {
      vec.setComponent(i,0.5);
   }

   for (int i = 0; i< ndim_; ++i) {
      /* On face */
      vec.setComponent(i,1.0);
      test(cube.isOnFace(scip_,vec) == true);
      /* Still On face */
      vec.setComponent(i,1.0 + 1e-10);
      test(cube.isOnFace(scip_,vec) == true);
      /* No longer on face */
      vec.setComponent(i,1.0 + 2e-9);
      test(cube.isOnFace(scip_,vec) == false);
      /* contained, not on  face */
      vec.setComponent(i,0.5);
      test(cube.isOnFace(scip_,vec) == false);
   }
}

void TestGeom::testIsOnVertex() {
   std::cout << "-- Testing cube.isOnVertex(vector)" << std::endl;
   HyperCube cube;
   cube = unitCube();
   Vector vec(ndim_);
   for (int i = 0; i< ndim_; ++i) {
      vec.setComponent(i,1);
   }

   for (int i = 0; i< ndim_; ++i) {
      /* On vertex */
      test(cube.isOnVertex(scip_,vec) == true);
      /* Still On vertex */
      vec.setComponent(i,1.0 + 1e-10);
      test(cube.isOnVertex(scip_,vec) == true);
      /* No longer on vertex */
      vec.setComponent(i,1.0 + 2e-9);
      test(cube.isOnVertex(scip_,vec) == false);
      /* contained, not on  vertex */
      vec.setComponent(i,0.5);
      test(cube.isOnVertex(scip_,vec) == false);
      /* Reset */
      vec.setComponent(i,1);
   }
}




void TestGeom::testFindSeveredVertex() {
      std::cout << "-- Testing cube.findSeveredVertex(plane)" << std::endl;
      {
         HyperCube cube;
         cube = unitCube();

         SDgeom::Vector vec, point;
         for (int i = 0; i < ndim_; ++i) {
            vec.addDim(1.0);
            point.addDim(0.9);
         }
         HyperPlane plane(vec,point);
         SDgeom::HyperCube::VertexIntersectionsPair pair = cube.findSeveredVertex(&plane);
         SDgeom::Orthant orth(pair.first);
         std::vector<SDgeom::Vector> intersections(pair.second);
        for (int i = 0; i < ndim_; ++i) {
           test(orth.getHalfSpace(i) == true);
         }
        test(intersections.size() == (unsigned int) ndim_);

        for (int i = 0; i < ndim_; ++i) {
           for (int j = 0; j < ndim_; ++j) {
              if (i == j)
                 testEqual(intersections[i].getComponent(j),1 - ndim_*0.1);
              else
                 testEqual(intersections[i].getComponent(j),1);
           }
        }
      }
      {
         HyperCube cube;
         SDgeom::Vector vec, point;

         for (int i = 0; i < ndim_; ++i) {
            vec.addDim(1.0);
            point.addDim(1.9);
            cube.addDim(0,2.0);
         }
         HyperPlane plane(vec,point);

         SDgeom::HyperCube::VertexIntersectionsPair pair = cube.findSeveredVertex(&plane);
         SDgeom::Orthant orth(pair.first);
         std::vector<SDgeom::Vector> intersections(pair.second);

        for (int i = 0; i < ndim_; ++i) {
           test(orth.getHalfSpace(i) == true);
         }

        test(intersections.size() == (unsigned int) ndim_);

        for (int i = 0; i < ndim_; ++i) {
           for (int j = 0; j < ndim_; ++j) {
              if (i == j)
                 testEqual(intersections[i].getComponent(j),2 - ndim_*0.1);
              else
                 testEqual(intersections[i].getComponent(j),2);
           }
        }
      }
      return;
}

void TestGeom::testVectorOperators() {
   std::cout << "-- Testing Vector operators " << std::endl;
   {
      SDgeom::Vector a(1,2,3);
      SDgeom::Vector b(-1,-2,-3);
      SDgeom::Vector c;

      //SDgeom::Vector c(a+b);
      a += b;
      c = b + (-1.0)*b;

      for (int i = 0; i < 3 ; ++i) {
         test(a.getComponent(i) == 0);
         test(c.getComponent(i) == 0);
      }
   }
   {
      SDgeom::Vector a(1,2,3);
      SDgeom::Vector b(-1,-2,3);
      double s = a*b;
      test(s == 4);
   }

}

void TestGeom::testIntersection() {
   std::cout << "-- Testing line::intersection(plane)" << std::endl;
   {
      SDgeom::Line line(SDgeom::Vector(0,1.0),SDgeom::Vector(2,1.0));
      SDgeom::HyperPlane plane(SDgeom::Vector(0,1.0),SDgeom::Vector(2,1.0));
      SDgeom::Vector i(line.intersection(&plane));
      test(i.getDim() == 0);
   }
   {
      SDgeom::Line line(SDgeom::Vector(0,1.0),SDgeom::Vector(2,1.0));
      SDgeom::HyperPlane plane(SDgeom::Vector(1,0),SDgeom::Vector(1,0));
      SDgeom::Vector i(line.intersection(&plane));
      test(i.getComponent(0) == 1);
      test(i.getComponent(1) == 1);
   }
   {
      HyperPlane plane(SDgeom::Vector(1.0,1.0),SDgeom::Vector(0.99999,0.99999));
      Line line(Vector(0.0,1.0),Vector(2.0,1.0));
      SDgeom::Vector intersection(line.intersection(&plane));
      for (int i = 0; i < intersection.getDim(); ++i)
         test(intersection.getComponent(i) > 0.9999 && intersection.getComponent(i) <= 1.0);
   }

}


void TestGeom::testGetSeparatedVolume() {
      std::cout << "-- Testing cube.getSeparatedVolume(plane)" << std::endl;
      if (true) {
         HyperCube cube;
         cube = unitCube();
         SDgeom::Vector vec, point;
         for (int i = 0; i < ndim_; ++i) {
            vec.addDim(1.0);
            point.addDim(0.9);
         }
         HyperPlane plane(vec,point);
         double vol(cube.getSeparatedVolume(&plane));
         testEqual(vol,pow((ndim_*0.1),ndim_) / ndim_);

      }
      {
         HyperCube cube;
         cube = unitCube();
         SDgeom::Vector vec, point;
         for (int i = 0; i < ndim_; ++i) {
            vec.addDim(1.0);
            point.addDim(0.75);
         }
         HyperPlane plane(vec,point);
         double vol(cube.getSeparatedVolume(&plane));
         //std::cout << "Volume is " << vol << std::endl;
         vol = cube.getRelativeSeparatedVolume(&plane);
         //std::cout << "Rel. Volume is " << vol << std::endl;
         test(vol >= 0.125 || (ndim_ >= 5 && vol == 0 && cube.intersects(plane)));
         //std::cout << "Relative Volume is " << vol << std::endl;
      }

      {
         HyperCube cube;
         SDgeom::Vector vec, point;
         for (int i = 0; i < ndim_; ++i) {
            vec.addDim(1.0);
            point.addDim(0.5);
            cube.addDim(-100.0,1.0);
         }
         HyperPlane plane(vec,point);
         //double vol(cube.getSeparatedVolume(&plane));
         //std::cout << "Volume is " << vol << std::endl;
         //vol = cube.getRelativeSeparatedVolume(&plane);
         //std::cout << "Relative Volume is " << vol << std::endl;
      }

}

void TestGeom::testHyperCubeIntersects() {
   std::cout << "-- Testing cube.intersects(plane)" << std::endl;
   HyperCube cube;
   cube = unitCube();
   {
      SDgeom::Vector vec, point;
      for (int i = 0; i < ndim_; ++i) {
         vec.addDim(1.0);
         point.addDim(0.9);
      }
      HyperPlane plane(vec,point);
      test(cube.intersects(plane));
   }
   {
      SDgeom::Vector vec, point;
      for (int i = 0; i < ndim_; ++i) {
         vec.addDim(1.0);
         point.addDim(1.0);
      }
      HyperPlane plane(vec,point);
      test(cube.intersects(plane));
   }
   {
      SDgeom::Vector vec, point;
      for (int i = 0; i < ndim_; ++i) {
         vec.addDim(1.0);
         point.addDim(1.1);
      }
      HyperPlane plane(vec,point);
      test(!cube.intersects(plane));
   }
   {
      SDgeom::Vector vec, point;
      for (int i = 0; i < ndim_; ++i) {
         vec.addDim(1.0);
         point.addDim(-0.1);
      }
      HyperPlane plane(vec,point);
      test(!cube.intersects(plane));
   }
   {
      SDgeom::Vector vec, point;
      for (int i = 0; i < ndim_; ++i) {
         vec.addDim(-1.0);
         point.addDim(-0.1);
      }
      HyperPlane plane(vec,point);
      test(!cube.intersects(plane));
   }
}

void TestGeom::testVectorLength() {
   std::cout << "-- Testing Vector Length" << std::endl;
   {
      SDgeom::Vector a(1,2,3);
      SDgeom::Vector b(-1,-2,-3);
      SDgeom::Vector c(4,5);

      //SDgeom::Vector c(a+b);
      testEqual(a.length(),sqrt(1 + 4 + 9));
      testEqual(b.length(),sqrt(1 + 4 + 9));
      testEqual(c.length(),sqrt(16 + 25));
   }
}




void TestGeom::runAll() {
   for (int ndim = 2; ndim <= 5; ++ndim) {
      std::cout << "Running tests for d = " << ndim << std::endl;
      ndim_ = ndim;
      testContains();
      testIsOnFace();
      testIsOnVertex();
      testVectorOperators();
      testIntersection();
      testHyperCubeIntersects();
      testFindSeveredVertex();
      testGetSeparatedVolume();
      std::cout << "All tests for D=" << ndim_ << " finished" << std::endl;
   }
}



void TestGeom::runCurrent() {
   ndim_ = 3;
   testVectorLength();

   std::cout << "Current tests finished" << std::endl;

}


}

