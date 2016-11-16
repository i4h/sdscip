/*
 * TestGeom.cpp
 *
 *  Created on: 05.02.2014
 *      Author: bzfvierh
 */

#include "TestGeom.h"
#include <math.h>

namespace sdscip {

TestGeom::TestGeom(SCIP* _scip) :
      SDSCIPtest(_scip)
      ,eps_(1e-9)
      ,ndim_(0)
{ }

TestGeom::~TestGeom()
{
   // TODO Auto-generated destructor stub
}

std::ostream& TestGeom::toString(std::ostream& strm) const {
  return strm << "TestGeom";
}


HyperCube TestGeom::unitCube() const {
   HyperCube cube;
   for (int i = 0; i<ndim_; ++i)
      cube.addDim(0, 1.0);
   return cube;
}



void TestGeom::testContains() {
   SCIPdebugMessage("   Testing cube.contains(vector)
");
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
   SCIPdebugMessage("   Testing cube.isOnFace(vector)
");
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
   SCIPdebugMessage("   Testing cube.isOnVertex(vector)
");
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
      SCIPdebugMessage("   Testing cube.findSeveredVertex(plane)
");
      {
         HyperCube cube;
         cube = unitCube();

         sdscip::Vector vec, point;
         for (int i = 0; i < ndim_; ++i) {
            vec.addDim(1.0);
            point.addDim(0.9);
         }
         HyperPlane plane(vec,point);
         sdscip::HyperCube::VertexIntersectionsPair pair = cube.findSeveredVertex(&plane);
         sdscip::Orthant orth(pair.first);
         std::vector<sdscip::Vector> intersections(pair.second);
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
         sdscip::Vector vec, point;

         for (int i = 0; i < ndim_; ++i) {
            vec.addDim(1.0);
            point.addDim(1.9);
            cube.addDim(0,2.0);
         }
         HyperPlane plane(vec,point);

         sdscip::HyperCube::VertexIntersectionsPair pair = cube.findSeveredVertex(&plane);
         sdscip::Orthant orth(pair.first);
         std::vector<sdscip::Vector> intersections(pair.second);

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
   SCIPdebugMessage("   Testing Vector operators 
");
   {
      sdscip::Vector a(1,2,3);
      sdscip::Vector b(-1,-2,-3);
      sdscip::Vector c;

      //sdscip::Vector c(a+b);
      a += b;
      c = b + (-1.0)*b;

      for (int i = 0; i < 3 ; ++i) {
         test(a.getComponent(i) == 0);
         test(c.getComponent(i) == 0);
      }
   }
   {
      sdscip::Vector a(1,2,3);
      sdscip::Vector b(-1,-2,3);
      double s = a*b;
      test(s == 4);
   }

}

void TestGeom::testIntersection() {
   SCIPdebugMessage("   Testing line::intersection(plane)
");
   {
      sdscip::Line line(sdscip::Vector(0,1.0),sdscip::Vector(2,1.0));
      sdscip::HyperPlane plane(sdscip::Vector(0,1.0),sdscip::Vector(2,1.0));
      sdscip::Vector i(line.intersection(&plane));
      test(i.getDim() == 0);
   }
   {
      sdscip::Line line(sdscip::Vector(0,1.0),sdscip::Vector(2,1.0));
      sdscip::HyperPlane plane(sdscip::Vector(1,0),sdscip::Vector(1,0));
      sdscip::Vector i(line.intersection(&plane));
      test(i.getComponent(0) == 1);
      test(i.getComponent(1) == 1);
   }
   {
      HyperPlane plane(sdscip::Vector(1.0,1.0),sdscip::Vector(0.99999,0.99999));
      Line line(Vector(0.0,1.0),Vector(2.0,1.0));
      sdscip::Vector intersection(line.intersection(&plane));
      for (int i = 0; i < intersection.getDim(); ++i)
         test(intersection.getComponent(i) > 0.9999 && intersection.getComponent(i) <= 1.0);
   }

}


void TestGeom::testGetSeparatedVolume() {
      SCIPdebugMessage("   Testing cube.getSeparatedVolume(plane)
");
      if (true) {
         HyperCube cube;
         cube = unitCube();
         sdscip::Vector vec, point;
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
         sdscip::Vector vec, point;
         for (int i = 0; i < ndim_; ++i) {
            vec.addDim(1.0);
            point.addDim(0.75);
         }
         HyperPlane plane(vec,point);
         double vol(cube.getSeparatedVolume(&plane));
         //SCIPdebugMessage("Volume is " << vol << std::endl;
         vol = cube.getRelativeSeparatedVolume(&plane);
         //SCIPdebugMessage("Rel. Volume is " << vol << std::endl;
         test(vol >= 0.125 || (ndim_ >= 5 && vol == 0 && cube.intersects(plane)));
         //SCIPdebugMessage("Relative Volume is " << vol << std::endl;
      }

      {
         HyperCube cube;
         sdscip::Vector vec, point;
         for (int i = 0; i < ndim_; ++i) {
            vec.addDim(1.0);
            point.addDim(0.5);
            cube.addDim(-100.0,1.0);
         }
         HyperPlane plane(vec,point);
         //double vol(cube.getSeparatedVolume(&plane));
         //SCIPdebugMessage("Volume is " << vol << std::endl;
         //vol = cube.getRelativeSeparatedVolume(&plane);
         //SCIPdebugMessage("Relative Volume is " << vol << std::endl;
      }

}

void TestGeom::testHyperCubeIntersects() {
   SCIPdebugMessage("   Testing cube.intersects(plane)
");
   HyperCube cube;
   cube = unitCube();
   {
      sdscip::Vector vec, point;
      for (int i = 0; i < ndim_; ++i) {
         vec.addDim(1.0);
         point.addDim(0.9);
      }
      HyperPlane plane(vec,point);
      test(cube.intersects(plane));
   }
   {
      sdscip::Vector vec, point;
      for (int i = 0; i < ndim_; ++i) {
         vec.addDim(1.0);
         point.addDim(1.0);
      }
      HyperPlane plane(vec,point);
      test(cube.intersects(plane));
   }
   {
      sdscip::Vector vec, point;
      for (int i = 0; i < ndim_; ++i) {
         vec.addDim(1.0);
         point.addDim(1.1);
      }
      HyperPlane plane(vec,point);
      test(!cube.intersects(plane));
   }
   {
      sdscip::Vector vec, point;
      for (int i = 0; i < ndim_; ++i) {
         vec.addDim(1.0);
         point.addDim(-0.1);
      }
      HyperPlane plane(vec,point);
      test(!cube.intersects(plane));
   }
   {
      sdscip::Vector vec, point;
      for (int i = 0; i < ndim_; ++i) {
         vec.addDim(-1.0);
         point.addDim(-0.1);
      }
      HyperPlane plane(vec,point);
      test(!cube.intersects(plane));
   }
}

void TestGeom::testVectorLength() {
   SCIPdebugMessage("   Testing Vector Length
");
   {
      sdscip::Vector a(1,2,3);
      sdscip::Vector b(-1,-2,-3);
      sdscip::Vector c(4,5);

      //sdscip::Vector c(a+b);
      testEqual(a.length(),sqrt(1 + 4 + 9));
      testEqual(b.length(),sqrt(1 + 4 + 9));
      testEqual(c.length(),sqrt(16 + 25));
   }
}




void TestGeom::runAll() {

   out_ << "Running all";
   return;
   for (int ndim = 2; ndim <= 5; ++ndim) {
      SCIPdebugMessage("  Running tests for D = " << ndim << std::endl;
      ndim_ = ndim;

      testContains();
      nExecutedTests_++;

      testIsOnFace();
      nExecutedTests_++;

      testIsOnVertex();
      nExecutedTests_++;

      testFindSeveredVertex();
      nExecutedTests_++;

      testVectorOperators();
      nExecutedTests_++;

      testIntersection();
      nExecutedTests_++;

      testGetSeparatedVolume();
      nExecutedTests_++;

      testHyperCubeIntersects();
      nExecutedTests_++;

      SCIPdebugMessage("All tests for D =" << ndim_ << " finished
");
   }
}





void TestGeom::runCurrent() {
   ndim_ = 3;
   testVectorLength();

   SCIPdebugMessage("Current tests finished
");

}


}

