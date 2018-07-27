// includes
// std
#include <tuple>

// RBDyn
#include "RBDyn/Body.h"
#include "RBDyn/Joint.h"
#include "RBDyn/MultiBody.h"
#include "RBDyn/MultiBodyConfig.h"
#include "RBDyn/MultiBodyGraph.h"

std::tuple<rbd::MultiBody, rbd::MultiBodyConfig, rbd::MultiBodyGraph> func(void)
{
  rbd::MultiBody mb;
  rbd::MultiBodyConfig mbc;
  rbd::MultiBodyGraph mbg;
  return std::make_tuple(mb, mbc, mbg);  
}

int main(void)
{
  using namespace Eigen;
  using namespace sva;
  using namespace rbd;

  rbd::MultiBodyGraph mbg;

  double mass = 1.;
  Eigen::Matrix3d I = Eigen::Matrix3d::Identity();
  Eigen::Vector3d h = Eigen::Vector3d::Zero();
  //Vector3d h = Vector3d(0, -0.25, 0);

  rbd::RBInertiad rbi(mass, h, I);

  rbd::Body b0(rbi, "b0");
  rbd::Body b1(rbi, "b1");
  rbd::Body b2(rbi, "b2");
  rbd::Body b3(rbi, "b3");

  mbg.addBody(b0);
  mbg.addBody(b1);
  mbg.addBody(b2);
  mbg.addBody(b3);

  rbd::Joint j0(Joint::RevX, true, "j0");
  rbd::Joint j1(Joint::RevX, true, "j1");
  rbd::Joint j2(Joint::RevX, true, "j2");

  mbg.addJoint(j0);
  mbg.addJoint(j1);
  mbg.addJoint(j2);

  //  Root     j0       j1     j2
  //  ---- b0 ---- b1 ---- b2 ----b3
  //  Base    RevX   RevX    RevX

  sva::PTransformd to(Eigen::Vector3d(0., 1., 0.));
  sva::PTransformd from(Eigen::Vector3d(0., 0., 0.));

  mbg.linkBodies("b0", from, "b1", from, "j0");
  mbg.linkBodies("b1", to, "b2", from, "j1");
  mbg.linkBodies("b2", to, "b3", from, "j2");

  MultiBody mb = mbg.makeMultiBody("b0", isFixed);

  MultiBodyConfig mbc(mb);
  mbc.zero(mb);

  return 0;
}
