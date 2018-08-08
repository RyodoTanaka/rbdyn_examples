#include <mc_rbdyn_urdf/urdf.h>
#include <RBDyn/FK.h>
#include <SpaceVecAlg/Conversions.h>

#include <iostream>
#include <fstream>
#include <cmath>

int main(int argc, char** argv)
{
  if(argc==1){
    std::cout << "You need URDF file as an argument." << std::endl;
    return 1;
  }
  std::ifstream ifs(argv[1]);
  std::string urdf((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    
  auto strRobot = mc_rbdyn_urdf::rbdyn_from_urdf(urdf);
  
  strRobot.mbc.q[1][0] = M_PI/3;
  strRobot.mbc.q[2][0] = -M_PI/3;
  strRobot.mbc.q[3][0] = -M_PI/3;
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
