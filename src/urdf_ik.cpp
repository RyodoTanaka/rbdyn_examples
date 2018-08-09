#include <mc_rbdyn_urdf/urdf.h>
#include <RBDyn/IK.h>
#include <SpaceVecAlg/Conversions.h>
#include <Eigen/Core>


#include <iostream>
#include <fstream>
#include <cmath>

Eigen::Affine3d RotationFromRPY(const double roll, const double pitch, const double yaw)
{
  using namespace Eigen;

  return Affine3d(  AngleAxisd(roll, Vector3d::UnitX())
                  * AngleAxisd(pitch, Vector3d::UnitY())
                  * AngleAxisd(yaw, Vector3d::UnitZ()) );
}


inline Eigen::Matrix4d setHomogeneous(const double x,
                                      const double y,
                                      const double z,
                                      const double roll,
                                      const double pitch,
                                      const double yaw)
{
  using namespace Eigen;
  
  Affine3d rotation = RotationFromRPY(roll,pitch,yaw);
  Affine3d transform(Translation3d(Vector3d(x,y,z)));

  return (transform * rotation).matrix();  
}

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

  // Set the Inverse Kinematics Class
  // End link index is 4 for zzz_arm
  rbd::InverseKinematics IK(strRobot.mb, 4);

  // Homogeneous matrix for end link
  Eigen::Matrix4d ef_homogeneous = setHomogeneous(1,1,0,0,0,M_PI/6);
  
  // Convert from Homogeneous matrix to PTransformed
  sva::PTransformd ef_target = sva::conversions::fromHomogeneous(ef_homogeneous,sva::conversions::RightHanded);
  
  // // // Solve the IK
  bool ik_result = IK.inverseKinematics(strRobot.mb, strRobot.mbc, ef_target);

  if(ik_result)
    std::cout << "== IK SOLVED ==" << std::endl;
  else
    std::cout << "== IK NOT SOLVED ==" << std::endl; 
  
  // get Body position in the world frame
  auto bpw = strRobot.mbc.bodyPosW;
  for(auto itr = bpw.begin(); itr!=bpw.end(); itr++){
    auto homogeneous = sva::conversions::toHomogeneous(*itr,sva::conversions::RightHanded);
    std::cout << "== Homogeneous matrix " << itr-bpw.begin() << " in world frame ==" << std::endl;
    std::cout << homogeneous << std::endl;
  }
  
  return 0;
}
