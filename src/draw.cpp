#include "draw.h"

int sr::width = 0, sr::height = 0;
float sr::vfov_degrees = 0.0f;

int sr::init(int width, int height, float vfov)
{
    if (!td_initialize(width, height))
    {
        return 0;
    }

    sr::width = width;
    sr::height = height;
    sr::vfov_degrees = vfov;

    return 1;
}

void sr::clean()
{
    td_terminate(1);

    return;
}

void sr::display()
{
    td_display();

    return;
}

m3::mat4 perspectiveMatrix()
{
    double near = 0.01;
    double far = 100;
    double top = near * std::tan(sr::vfov_degrees / 2 * (M3_PI / 180.0));
    double bottom = -top;
    double right = top * ((double)sr::width / (double)sr::height);
    double left = -right;

    double m00 = (2 * near) / (right - left);
    double m02 = (right + left) / (right - left);
    double m11 = (2 * near) / (top - bottom);
    double m12 = (top + bottom) / (top - bottom);
    double m22 = (-(far + near)) / (far - near);
    double m23 = (-2 * far * near) / (far - near);

    m3::vec4 rows[4] = {
        m3::vec4(m00, 0, m02, 0),
        m3::vec4(0, m11, m12, 0),
        m3::vec4(0, 0, m22, m23),
        m3::vec4(0, 0, -1, 0)
    };

    return m3::mat4(rows);
}

void sr::draw(sr::Model m, sr::Camera c)
{
    std::vector<m3::vec4> vertices;

    m3::mat4 modelMatrix = m.modelMatrix();
    m3::mat4 view_matrix = c.viewMatrix();
    m3::mat4 perspective_matrix = perspectiveMatrix();

    double hw = sr::width / 2;
    double hh = sr::height / 2;

    for (auto &v : m.vertices)
    {
        m3::vec4 v0 = perspective_matrix * view_matrix * modelMatrix * v;

        double x = hw + ((v0.x() / v0.w()) * hw);
        double y = hh + ((v0.y() / v0.w()) * hh);
        double z = v0.z() / v0.w();
        double w = v0.w();

        m3::vec4 v1(x, y, z, 1);

        vertices.push_back(v1);
    }

    if (m.indices.size() % 3 == 0)
    {
        for (unsigned long i = 0; i < m.indices.size(); i += 3)
        {
            int indices[3];

            indices[0] = m.indices[i];
            indices[1] = m.indices[i + 1];
            indices[2] = m.indices[i + 2];

            m3::vec4 v0 = vertices.at(indices[0]);
            m3::vec4 v1 = vertices.at(indices[1]);
            m3::vec4 v2 = vertices.at(indices[2]);

            bool v0_b = false;
            bool v1_b = false;
            bool v2_b = false;

            // near plane, abbr. for formulas
            double n = 0;

            if (v0.w() < n || v1.w() < n || v2.w() < n)
            {
                continue;
            }

            if ((v0.x() < 0 || v0.x() >= sr::width) || (v0.y() < 0 || v0.y() >= sr::height))
            {
                v0_b = true;
            }
            if ((v1.x() < 0 || v1.x() >= sr::width) || (v1.y() < 0 || v1.y() >= sr::height))
            {
                v1_b = true;
            }
            if ((v2.x() < 0 || v2.x() >= sr::width) || (v2.y() < 0 || v2.y() >= sr::height))
            {
                v2_b = true;
            }

            if (v0_b && v1_b && v2_b)
            {
                continue;
            }

            if (!(v0_b && v1_b))
            {
                td_drawLine(v0.x(), v0.y(), v1.x(), v1.y(), '*', TD_COLOR_RED, TD_COLOR_DEFAULT);
            }

            if (!(v1_b && v2_b))
            {
                td_drawLine(v1.x(), v1.y(), v2.x(), v2.y(), '*', TD_COLOR_GREEN, TD_COLOR_DEFAULT);
            }

            if (!(v0_b && v1_b))
            {
                td_drawLine(v2.x(), v2.y(), v0.x(), v0.y(), '*', TD_COLOR_BLUE, TD_COLOR_DEFAULT);
            }
        }
    }

    for (auto &v : vertices)
    {
        if (v.w() < 0)
        {
            continue;
        }

        td_drawPoint(v.x(), v.y(), '*', TD_COLOR_DEFAULT, TD_COLOR_DEFAULT);
    }

    return;
}