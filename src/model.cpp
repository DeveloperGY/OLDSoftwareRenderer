#include "model.h"

sr::Model::Model(std::string filename): pos{m3::vec4(0, 0, 0, 1)}, rot{m3::vec4(0, 0, 0, 0)}, scl{m3::vec4(1, 1, 1, 0)}
{
    std::fstream file;
    file.open(filename);

    if (!file.is_open())
    {
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream ss(line);

        std::string word;


        std::getline(ss, word, ' ');

        if (word == "v")
        {
            double x, y, z;

            ss >> x >> y >> z;

            this->vertices.push_back(m3::vec4(x, y, z, 1));
        }
    }

    return;
}