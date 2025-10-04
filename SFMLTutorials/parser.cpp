#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector<std::vector<int>> LoadWorldFromFile(const std::string& filename)
{
    std::vector<std::vector<int>> worldData;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open level file: " << filename << std::endl;
        return worldData;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<int> row;
        for (char tileChar : line)
        {
            row.push_back(tileChar - '0');
        }
        worldData.push_back(row);
    }
    file.close();
    return worldData;
}