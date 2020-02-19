#include <mc_rbdyn_urdf/urdf.h>
#include <RBDyn/CoM.h>
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
        filename = "urdf/robot1.urdf";

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
    strRobot.mbc.q[joint_map["joint0x"]][0] = 1.0;
    strRobot.mbc.q[joint_map["joint0y"]][0] = 0.0;
    strRobot.mbc.q[joint_map["joint0z"]][0] = 2.0;
    strRobot.mbc.q[joint_map["joint1"]][0] = M_PI/4.;
    strRobot.mbc.q[joint_map["joint2"]][0] = -M_PI/4.;
    rbd::forwardKinematics(strRobot.mb, strRobot.mbc);

    for(auto i=strRobot.mbc.q.begin(); i!=strRobot.mbc.q.end(); i++){
        if(!i->size())
            std::cout << i-strRobot.mbc.q.begin() << " th is empty" << std::endl;
        else
            std::cout << i->at(0) << std::endl;
    }

    Eigen::Vector3d com = rbd::sComputeCoM(strRobot.mb, strRobot.mbc);

    std::cout << com.transpose() << std::endl;
    
    return 0;
}
