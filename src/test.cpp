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
        filename = "urdf/robot.urdf";

    std::ifstream ifs(filename);
    std::string urdf((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    // set ParsedResult from URDF file
    auto strRobot = mc_rbdyn_urdf::rbdyn_from_urdf(urdf);

    // get joint index map
    auto joint_map = strRobot.mb.jointIndexByName();
  
    // get Body
    auto body = strRobot.mb.bodies();

    // set the Joint value & solve FK
    // strRobot.mbc.q[joint_map["joint0"]] = std::vector<double>{1,0,0,0,0,0,0};
    strRobot.mbc.q[joint_map["joint0x"]][0] = 0.0;
    strRobot.mbc.q[joint_map["joint0y"]][0] = 0.0;
    strRobot.mbc.q[joint_map["joint1"]][0] = M_PI/8.;
    strRobot.mbc.q[joint_map["joint2a"]][0] = M_PI/8.;
    // strRobot.mbc.q[joint_map["joint3"]][0] = -M_PI/6.;
    rbd::forwardKinematics(strRobot.mb, strRobot.mbc);

    for(auto i=strRobot.mbc.q.begin(); i!=strRobot.mbc.q.end(); i++){
        if(!i->size())
            std::cout << i-strRobot.mbc.q.begin() << " th is empty" << std::endl;
        else
            std::cout << i->at(0) << std::endl;
    }


  
    // get Every Jacobian Matrix in every Body
    for(auto itr=body.begin(); itr!=body.end(); itr++){
      // Get Jacobian
      rbd::Jacobian jac(strRobot.mb, itr->name());
      // Get Kinematics Jacobian  
      const Eigen::MatrixXd& jacO = jac.jacobian(strRobot.mb, strRobot.mbc);
      const Eigen::MatrixXd& jacB = jac.bodyJacobian(strRobot.mb, strRobot.mbc);

      // get PTransform
      sva::PTransformd X_O_b = strRobot.mbc.bodyPosW[itr-body.begin()];
      sva::PTransformd X_b_p = sva::PTransformd(jac.point());
      sva::PTransformd X_O_p = X_b_p*X_O_b;
      
      const Eigen::MatrixXd &body_jac = jac.jacobian(strRobot.mb, strRobot.mbc, X_O_p);
      
      // Print the result
      std::cout << "===============================================" << std::endl;
      std::cout << "== " << itr->name() << " Jacobian Matrix == " << std::endl;
      std::cout << "===============================================" << std::endl;
      std::cout << "== Dense Jacobian in Origin frame orientation of " <<  itr->name() << " ==" << std::endl;
      std::cout << jacO << std::endl;
      // std::cout << "== Full Jacobian in Origin frame orientation of " <<  itr->name() << " ==" << std::endl;
      // std::cout << sparseJacO << std::endl;
      std::cout << "== Dense Jacobian in body frame orientation of " <<  itr->name() << " ==" << std::endl;
      std::cout << jacB << std::endl;
      // std::cout << "== Full Jacobian in body frame of " <<  itr->name() << " ==" << std::endl;
      // std::cout << sparseJacB << std::endl;
      
      std::cout << "== Body Jacobian ==" << std::endl;
      std::cout << body_jac << std::endl;
    }
  
    return 0;
}
