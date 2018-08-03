#include <mc_rbdyn_urdf/urdf.h>

#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
  std::ifstream ifs(argv[1]);
  std::string urdf((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
  
  auto strRobt = mc_rbdyn_urdf::rbdyn_from_urdf(urdf);
  
  return 0;
}
