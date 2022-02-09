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
    std::string input;
    std::getline(std::cin, input);

    std::stringstream inputStream(input);

    std::string command;
    inputStream >> command;

    std::string next;
    getline(inputStream, next, '"');
    
    std::cout << command << std::endl;
  }
  return 0;
}