#include <mc_rbdyn_urdf/urdf.h>
#include <RBDyn/FK.h>
#include <RBDyn/FV.h>
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

  // set the Joint velocity & solve FV (Forward Velocity)
  strRobot.mbc.alpha[joint_map["j0"]][0] = M_PI/12;
  strRobot.mbc.alpha[joint_map["j1"]][0] = -M_PI/6;
  strRobot.mbc.alpha[joint_map["j2"]][0] = M_PI/24;
  rbd::forwardVelocity(strRobot.mb, strRobot.mbc);
  
  // get Every Jacobian Matrix in every Body
  for(auto itr=body.begin(); itr!=body.end(); itr++){
    // Get Jacobian
    rbd::Jacobian jac(strRobot.mb, itr->name());
    // Get Kinematics Jacobian  
    const Eigen::MatrixXd& jacO = jac.jacobian(strRobot.mb, strRobot.mbc);
    const Eigen::MatrixXd& jacB = jac.bodyJacobian(strRobot.mb, strRobot.mbc);
    // Get FullJacobian
    Eigen::MatrixXd sparseJacO(6,body.size());
    Eigen::MatrixXd sparseJacB(6,body.size());

    jac.fullJacobian(strRobot.mb, jacO, sparseJacO);
    jac.fullJacobian(strRobot.mb, jacB, sparseJacB);
    
    // Print the result
    std::cout << "===============================================" << std::endl;
    std::cout << "== " << itr->name() << " Jacobian Matrix == " << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "== Dense Jacobian in Origin frame orientation of " <<  itr->name() << " ==" << std::endl;
    std::cout << jacO << std::endl;
    std::cout << "== Full Jacobian in Origin frame orientation of " <<  itr->name() << " ==" << std::endl;
    std::cout << sparseJacO << std::endl;
    std::cout << "== Dense Jacobian in body frame orientation of " <<  itr->name() << " ==" << std::endl;
    std::cout << jacB << std::endl;
    std::cout << "== Full Jacobian in body frame of " <<  itr->name() << " ==" << std::endl;
    std::cout << sparseJacB << std::endl;

    // Get Velocity
    auto velO = jac.velocity(strRobot.mb, strRobot.mbc);
    auto velB = jac.bodyVelocity(strRobot.mb, strRobot.mbc);

    std::cout << "== Body Velocity in Origin frame orientation of " <<  itr->name() << " ==" << std::endl;
    std::cout << velO << std::endl;
    std::cout << "== Body Velocity in body frame orientation of " <<  itr->name() << " ==" << std::endl;
    std::cout << velB << std::endl;
  }
  
  return 0;
}
