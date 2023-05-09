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
        else if (word == "f")
        {
            std::string groups[3];
            ss >> groups[0] >> groups[1] >> groups[2];

            for (auto &group : groups)
            {
                std::istringstream gss(group);
                for (int i=0; i<3; i++)
                {
                    std::string vertex;
                    std::getline(gss, vertex, '/');
                    int index = std::stoi(vertex) - 1;

                    if (i == 0)
                    {
                        this->indices.push_back(index);
                    }
                }
            }
        }
    }

    return;
}

m3::mat4 sr::Model::modelMatrix()
{
    m3::mat4 translation = m3::mat4::gen_translation(this->pos.x(), this->pos.y(), this->pos.z());
    m3::quat rotation = m3::quat(this->rot.x(), m3::vec4(1, 0, 0, 0)) * m3::quat(this->rot.y(), m3::vec4(0, 1, 0, 0)) * m3::quat(this->rot.z(), m3::vec4(0, 0, 1, 0));
    m3::mat4 scale = m3::mat4::gen_scale(this->scl.x(), this->scl.y(), this->scl.z());

    return translation * rotation * scale;
}

void sr::Model::rotate(double x, double y, double z)
{
    this->rot.data[0] += x;
    this->rot.data[1] += y;
    this->rot.data[2] += z;

    this->rot.data[0] = std::fmod(this->rot.x(), 360.0);
    this->rot.data[1] = std::fmod(this->rot.y(), 360.0);
    this->rot.data[2] = std::fmod(this->rot.z(), 360.0);

    return;
}

void sr::Model::translate(double x, double y, double z)
{
    this->pos.data[0] += x;
    this->pos.data[1] += y;
    this->pos.data[2] += z;

    return;
}

void sr::Model::scale(double x, double y, double z)
{
    this->scl.data[0] += x;
    this->scl.data[1] += y;
    this->scl.data[2] += z;

    return;
}