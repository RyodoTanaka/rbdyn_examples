#include <mc_rbdyn_urdf/urdf.h>
#include <RBDyn/FK.h>
#include <SpaceVecAlg/Conversions.h>
#include <Eigen/Core>

#include <iostream>
#include <fstream>
#include <cmath>

int main(int argc, char** argv)
{
  // Load the URDF file
  std::string filename;
  if(argc!=1)
    filename = argv[1];
  else
    filename = "urdf/zzz_arm.urdf";

  std::ifstream ifs(filename);
  std::string urdf((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

  // set ParsedResult from URDF file
  auto strRobot = mc_rbdyn_urdf::rbdyn_from_urdf(urdf);

  // set values for each joints
  strRobot.mbc.q[1][0] = M_PI/3;
  strRobot.mbc.q[2][0] = -M_PI/3;
  strRobot.mbc.q[3][0] = -M_PI/3;

  // Solve the FK
  rbd::forwardKinematics(strRobot.mb, strRobot.mbc);

  // get Body position in the world frame
  auto bpw = strRobot.mbc.bodyPosW;
  for(auto itr = bpw.begin(); itr!=bpw.end(); itr++){
    auto homogeneous = sva::conversions::toHomogeneous(*itr,sva::conversions::RightHanded);
    std::cout << "== Homogeneous matrix " << itr-bpw.begin() << " in world frame ==" << std::endl;
    std::cout << homogeneous << std::endl;
  }
  
  return 0;
}
