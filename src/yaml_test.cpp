#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

int main(int argc, char** argv)
{
  // Load the YAML file
  std::string filename;
  if(argc!=1)
    filename = argv[1];
  else
    filename = "yaml/test.yaml";

  std::ifstream ifs(filename);
  std::string yaml((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
  
  YAML::Node doc = YAML::Load(yaml);

  if (doc.IsMap()) {
    std::cout << "The file is map" << std::endl;

    std::cout << doc.size() << std::endl;
    
    std::cout << doc["name"].as<std::string>() << std::endl;
    std::cout << doc["what"] << std::endl;
    std::cout << doc["likes"][0].as<std::string>() << std::endl;
    std::cout << doc["likes"][1].as<double>() << std::endl;
    std::cout << doc["likes"][2].as<int>() << std::endl;

    std::cout << doc["obstacle1"].size() << std::endl;
    std::cout << doc["obstacle1"]["type"].as<std::string>() << std::endl;
    std::cout << doc["obstacle2"].size() << std::endl;
    std::cout << doc["obstacle2"]["from"].size() << std::endl;
    std::cout << doc["obstacle2"]["from"][1].as<double>() << std::endl;
  }
  
  return 0;
}
