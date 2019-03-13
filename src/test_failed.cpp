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

    // -----------------
    // // Load the URDF file
    // std::string filename;
    // if(argc!=1)
    //     filename = argv[1];
    // else
    //     filename = "urdf/robot.urdf";

    // std::ifstream ifs(filename);
    // std::string urdf((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    // set ParsedResult from URDF file
    // auto strRobot = mc_rbdyn_urdf::rbdyn_from_urdf(urdf);

    // -------------------


    // Make a simple robot
    using namespace Eigen;
	using namespace sva;
	using namespace rbd;


    MultiBodyGraph mbg;

    double mass = 1.;
    Matrix3d I = Matrix3d::Identity();
    Vector3d h = Vector3d::Zero();

    RBInertiad rbi(mass, h, I);

    Body world(rbi, "world");
    Body link0x(rbi, "link0x");
    Body link0y(rbi, "link0y");
    Body link0(rbi, "link0");
    Body link1(rbi, "link1");
    Body link2(rbi, "link2");

    mbg.addBody(world);
    mbg.addBody(link0x);
    mbg.addBody(link0y);
    mbg.addBody(link0);
    mbg.addBody(link1);
    mbg.addBody(link2);

    Joint joint0x(Joint::PrismX, true, "joint0x");
    Joint joint0y(Joint::PrismY, true, "joint0y");
    Joint joint0(Joint::Fixed, true, "joint0");
    Joint joint1(Joint::RevZ, true, "joint1");
    Joint joint2(Joint::Fixed, true, "joint2");

    mbg.addJoint(joint0x);
    mbg.addJoint(joint0y);
    mbg.addJoint(joint0);
    mbg.addJoint(joint1);
    mbg.addJoint(joint2);

    PTransformd to(Vector3d(0., -2., 0.));
    PTransformd from(Vector3d(0., 0., 0.));
    
    mbg.linkBodies("world", from, "link0x", from, "jonit0x");
    mbg.linkBodies("link0x", from, "link0y", from, "jonit0y");
    mbg.linkBodies("link0y", from, "link0", from, "jonit0");
    mbg.linkBodies("link0", from, "link1", from, "jonit1");
    mbg.linkBodies("link1", to, "link2", from, "jonit2");


    MultiBody mb = mbg.makeMultiBody("world", true);

    MultiBodyConfig mbc(mb);
    // mbc.zero(mb);
    
    // get joint index map
    // auto joint_map = mb.jointIndexByName();
  
    // // get Body
    // auto body = mb.bodies();

    // set the Joint value & solve FK
    // mbc.q[joint_map["joint0"]] = std::vector<double>{1,0,0,0,0,0,0};
    // mbc.q[joint_map["joint0x"]][0] = 4.0;
    // mbc.q[joint_map["joint0y"]][0] = 9.0;
    // mbc.q[joint_map["joint1"]][0] = M_PI/4.;
    // // mbc.q[joint_map["joint2a"]][0] = -M_PI/4.;
    // // mbc.q[joint_map["joint3"]][0] = -M_PI/6.;
    // rbd::forwardKinematics(mb, mbc);

    // for(auto i=mbc.q.begin(); i!=mbc.q.end(); i++){
    //     if(!i->size())
    //         std::cout << i-mbc.q.begin() << " th is empty" << std::endl;
    //     else
    //         std::cout << i->at(0) << std::endl;
    // }


  
    // // get Every Jacobian Matrix in every Body
    // for(auto itr=body.begin(); itr!=body.end(); itr++){
    //   // Get Jacobian
    //   rbd::Jacobian jac(mb, itr->name());
    //   // Get Kinematics Jacobian  
    //   const Eigen::MatrixXd& jacO = jac.jacobian(mb, mbc);
    //   const Eigen::MatrixXd& jacB = jac.bodyJacobian(mb, mbc);

    //   // get PTransform
    //   sva::PTransformd X_O_b = mbc.bodyPosW[itr-body.begin()];
    //   sva::PTransformd X_b_p = sva::PTransformd(jac.point());
    //   sva::PTransformd X_O_p = X_b_p*X_O_b;
      
    //   const Eigen::MatrixXd &body_jac = jac.jacobian(mb, mbc, X_O_p);
      
    //   // Print the result
    //   std::cout << "===============================================" << std::endl;
    //   std::cout << "== " << itr->name() << " Jacobian Matrix == " << std::endl;
    //   std::cout << "===============================================" << std::endl;
    //   std::cout << "== Dense Jacobian in Origin frame orientation of " <<  itr->name() << " ==" << std::endl;
    //   std::cout << jacO << std::endl;
    //   // std::cout << "== Full Jacobian in Origin frame orientation of " <<  itr->name() << " ==" << std::endl;
    //   // std::cout << sparseJacO << std::endl;
    //   std::cout << "== Dense Jacobian in body frame orientation of " <<  itr->name() << " ==" << std::endl;
    //   std::cout << jacB << std::endl;
    //   // std::cout << "== Full Jacobian in body frame of " <<  itr->name() << " ==" << std::endl;
    //   // std::cout << sparseJacB << std::endl;
      
    //   std::cout << "== Body Jacobian ==" << std::endl;
    //   std::cout << body_jac << std::endl;
    // }
  
    return 0;
}
