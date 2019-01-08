#include <mc_rbdyn_urdf/urdf.h>
#include <RBDyn/FK.h>
#include <RBDyn/Jacobian.h>
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

  // get joint index map
  auto joint_map = strRobot.mb.jointIndexByName();

  // get Body
  auto body = strRobot.mb.bodies();

  // set the Joint value & solve FK
  strRobot.mbc.q[joint_map["j0"]][0] = M_PI/2;
  strRobot.mbc.q[joint_map["j1"]][0] = M_PI/3;
  strRobot.mbc.q[joint_map["j2"]][0] = -M_PI/2;
  rbd::forwardKinematics(strRobot.mb, strRobot.mbc);
  
  // get Every Jacobian Matrix in every Body
  for(auto itr=body.begin(); itr!=body.end(); itr++){
    // Get Jacobian  
    rbd::Jacobian jac(strRobot.mb, itr->name());

    // Get Jacobian Matrix
    const Eigen::MatrixXd& jac_mat = jac.jacobian(strRobot.mb,strRobot.mbc);

    // Print the result
    std::cout << "== " << itr->name() << " Jacobian Matrix == " << std::endl;
    std::cout << jac_mat << std::endl;
  }
  
  return 0;
}
