#include "commands/cobot_pose.h"

namespace pproto::data {

CobotPose::CobotPose(std::vector<double>&& v)
    : std::vector<double>(std::move(v))
{}

CobotPose::CobotPose(const std::vector<double>& v)
    : std::vector<double>(v)
{}

CobotPose& CobotPose::operator= (std::vector<double>&& v)
{
    std::vector<double>::operator= (std::move(v));
    return *this;
}

CobotPose& CobotPose::operator= (const std::vector<double>& v)
{
    std::vector<double>::operator= (v);
    return *this;
}

void CobotPose::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << quint32(size());
    for (auto it = begin(); it < end(); ++it)
        stream << *it;
    B_SERIALIZE_RETURN
}

void CobotPose::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    quint32 size;
    stream >> size;
    for (quint32 i = 0; i < size; ++i)
    {
        if (stream.atEnd())
            break;

        double value;
        stream >> value;
        push_back(value);
    }
    B_DESERIALIZE_END
}

} // namespace pproto::data
