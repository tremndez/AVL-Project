#include <iostream>
#include <sstream>
#include <string>

int main()
{
  int numOfLines;
  std::cin >> numOfLines;
  std::cout << numOfLines;
  for(int i = 0; i < numOfLines; i++)
  {
    std::string in;
    std::getline(std::cin, in);
    std::stringstream command;
    command << in;
    std::getline(command, in, "\"");
    std::cout << command.str() << std::endl;
  }
  return 0;
}