#pragma once

#include "pproto/commands/base.h"
#include <vector>

namespace pproto::data {

struct CobotPose : std::vector<double>
{
    CobotPose() = default;
    CobotPose(CobotPose&&) = default;
    CobotPose(const CobotPose&) = default;

    CobotPose& operator= (CobotPose&&) = default;
    CobotPose& operator= (const CobotPose&) = default;

    CobotPose(std::vector<double>&&);
    CobotPose(const std::vector<double>&);

    CobotPose& operator= (std::vector<double>&&);
    CobotPose& operator= (const std::vector<double>&);

    DECLARE_B_SERIALIZE_FUNC
    DECLARE_J_SERIALIZE_FUNC
};

template<typename This, typename Packer>
Packer& CobotPose::jserialize(const This* ct, Packer& p)
{
    This* t = const_cast<This*>(ct);
    //p.startObject();
    std::vector<double> *v = t;
    p & *v;
    //return p.endObject();
    return p;
}

} // namespace pproto::data
