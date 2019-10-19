#include "Util.h"

#include <fstream>
#include <sstream>

std::string ReadFile(std::string filename) {
  std::ifstream s(filename);
  std::stringstream buffer;
  buffer << s.rdbuf();
  return buffer.str();
}
