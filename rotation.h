#pragma once
#include <math.h>
#include <array>

double __rot_computeX(std::array<double, 3> &pos, std::array<double, 3> &rot)
{
    return pos[1] * sin(rot[0]) * sin(rot[1]) * cos(rot[2]) - pos[2] * cos(rot[0]) * sin(rot[1]) * cos(rot[2]) +
           pos[1] * cos(rot[0]) * sin(rot[2]) + pos[2] * sin(rot[0]) * sin(rot[2]) + pos[0] * cos(rot[1]) * cos(rot[2]);
}

double __rot_computeY(std::array<double, 3> &pos, std::array<double, 3> &rot)
{
    return pos[1] * cos(rot[0]) * cos(rot[2]) + pos[2] * sin(rot[0]) * cos(rot[2]) -
           pos[1] * sin(rot[0]) * sin(rot[1]) * sin(rot[2]) + pos[2] * cos(rot[0]) * sin(rot[1]) * sin(rot[2]) -
           pos[0] * cos(rot[1]) * sin(rot[2]);
}

double __rot_computeZ(std::array<double, 3> &pos, std::array<double, 3> &rot)
{
    return pos[2] * cos(rot[0]) * cos(rot[1]) - pos[1] * sin(rot[0]) * cos(rot[1]) + pos[0] * sin(rot[1]);
}

std::array<double, 3> f_Rotate(std::array<double, 3> &pos, std::array<double, 3> &rot)
{
    std::array<double, 3> res;
    res[0] = __rot_computeX(pos, rot);
    res[1] = __rot_computeY(pos, rot);
    res[2] = __rot_computeZ(pos, rot);
    return res;
}