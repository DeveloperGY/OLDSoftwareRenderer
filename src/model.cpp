#include "model.h"

sr::Model::Model(std::string filename): pos{m3::vec4(0, 0, 0, 1)}, rot{m3::quat(0, 1, 0, 0)}, scl{m3::vec4(1, -1, 1, 0)}
{
    this->loadModel(filename);

    return;
}

m3::mat4 sr::Model::modelMatrix()
{
    m3::mat4 translation = m3::mat4::gen_translation(this->pos.x(), this->pos.y(), this->pos.z());
    m3::mat4 scale = m3::mat4::gen_scale(this->scl.x(), this->scl.y(), this->scl.z());

    return translation * this->rot * scale;
}

void sr::Model::rotate(double x, double y, double z)
{
    m3::quat rotX(x, m3::vec4(1, 0, 0, 0));
    m3::quat rotY(y, m3::vec4(0, 1, 0, 0));
    m3::quat rotZ(z, m3::vec4(0, 0, 1, 0));

    m3::quat rot = rotX * rotY * rotZ;

    this->rot = m3::quat::normalized(this->rot * rot);

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

void sr::Model::genTriangles()
{
    for (int i=0; i<this->indices.size(); i+=3)
    {
        int v0_index = this->indices.at(i);
        int v1_index = this->indices.at(i+1);
        int v2_index = this->indices.at(i+2);

        m3::vec4 v0 = this->vertices.at(v0_index);
        m3::vec4 v1 = this->vertices.at(v1_index);
        m3::vec4 v2 = this->vertices.at(v2_index);
        this->triangles.push_back(sr::Triangle(v0, v1, v2));
    }
}

int sr::Model::loadModel(std::string filename)
{
    std::fstream file;
    
    file.open(filename);

    if (!file.is_open())
    {
        return 0;
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

    this->genTriangles();
    return 1;
}