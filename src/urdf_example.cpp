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
  strRobot.mbc.q[1][0] = M_PI/4.;
  strRobot.mbc.q[2][0] = 0;
  strRobot.mbc.q[3][0] = -M_PI/4.;
  rbd::forwardKinematics(strRobot.mb, strRobot.mbc);

  auto jc = strRobot.mbc.jointConfig;
  std::cout << jc.size() << std::endl;

  for(auto itr = jc.begin(); itr!=jc.end(); itr++){
    auto affine = sva::conversions::toAffine(*itr,
                                             sva::conversions::LeftHanded);
    auto homogeneous = sva::conversions::toHomogeneous(*itr,
                                                       sva::conversions::LeftHanded);
    // std::cout << "== Affine ==" << std::endl;
    // std::cout << affine.translation() << std::endl;
    // std::cout << "=================" << std::endl;
    // std::cout << affine.rotation() << std::endl;

    std::cout << "== Homogeneous ==" << std::endl;
    std::cout << homogeneous << std::endl;

    
    
  }

  
  
  return 0;
}
