#include "commands.h"
#include "pproto/commands/pool.h"

namespace pproto {
namespace command {

#define REGISTRY_COMMAND_SINGLPROC(COMMAND, UUID) \
    const QUuidEx COMMAND = command::Pool::Registry{UUID, #COMMAND, false};

#define REGISTRY_COMMAND_MULTIPROC(COMMAND, UUID) \
    const QUuidEx COMMAND = command::Pool::Registry{UUID, #COMMAND, true};

REGISTRY_COMMAND_SINGLPROC(CobotPlanInfo,        "24fdb409-ded4-4127-a17b-99090e62ca8c")
REGISTRY_COMMAND_SINGLPROC(CobotExecutePlan,     "2b43d67c-26a2-4889-b55a-df787681a7c5")
REGISTRY_COMMAND_SINGLPROC(CobotStopExecution,   "f1f4b015-dc59-43ca-a352-205a6b0a4291")
REGISTRY_COMMAND_SINGLPROC(CobotPauseExecution,  "4f3a14d0-afb2-40f1-8a95-2de3466c7e79")
//REGISTRY_COMMAND_SINGLPROC(CobotPauseChanged,  "83925428-6c97-468e-9c3d-7994e11b83ec")
REGISTRY_COMMAND_SINGLPROC(CobotLastPlanAction,  "b7b8e0b0-de01-4344-9d58-5bc48932be71")
REGISTRY_COMMAND_SINGLPROC(CobotPlanBegin,       "6df740aa-3715-4e9b-9f2f-5a4705001150")
REGISTRY_COMMAND_SINGLPROC(CobotPlanEnd,         "d346775f-e071-45c2-8f81-7504263c591e")
REGISTRY_COMMAND_SINGLPROC(CobotPlanAction,      "8f02448e-4020-4bdd-aa95-6f55b53ec5d6")
REGISTRY_COMMAND_SINGLPROC(CobotPlanExecuting,   "3a284743-7a31-456a-8bbc-db698af9bc3e")

#undef REGISTRY_COMMAND_SINGLPROC
#undef REGISTRY_COMMAND_MULTIPROC

} // namespace command

namespace data {

void CobotPlanInfoA::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << identity;
    stream << paused;
    B_SERIALIZE_RETURN
}

void CobotPlanInfoA::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> identity;
    stream >> paused;
    B_DESERIALIZE_END
}

void CobotExecutePlan::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << identity;
    B_SERIALIZE_RETURN
}

void CobotExecutePlan::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> identity;
    B_DESERIALIZE_END
}

void CobotExecutePlanError::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1

    // Структуры унаследованные от MessageError сериализуются в особом порядке,
    // поэтому для них сериализация/десериализация базового класса не обязательна
    // stream << B_BASE_CLASS(MessageError);

    stream << identity;
    stream << activeIdentity;
    B_SERIALIZE_RETURN
}

void CobotExecutePlanError::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)

    // Структуры унаследованные от MessageError сериализуются в особом порядке,
    // поэтому для них сериализация/десериализация базового класса не обязательна
    // stream >> B_BASE_CLASS(MessageError);

    stream >> identity;
    stream >> activeIdentity;
    B_DESERIALIZE_END
}

void CobotActionInfo::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << plan;
    stream << action;
    stream << state;
    stream << phase;
    stream << error;
    B_SERIALIZE_RETURN
}

void CobotActionInfo::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> plan;
    stream >> action;
    stream >> state;
    stream >> phase;
    stream >> error;
    B_DESERIALIZE_END
}

void CobotPlanBegin::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << identity;
    B_SERIALIZE_RETURN
}

void CobotPlanBegin::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> identity;
    B_DESERIALIZE_END
}

void CobotPlanEnd::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << identity;
    B_SERIALIZE_RETURN
}

void CobotPlanEnd::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> identity;
    B_DESERIALIZE_END
}

} // namespace data
} // namespace pproto

namespace alog {

Line& operator<< (Line& line, const pproto::CobotActionState& actionState)
{
    if (line.toLogger())
    {
        switch (actionState)
        {
            case pproto::CobotActionState::Unknown      : line << "Unknown";      break;
            case pproto::CobotActionState::Idle         : line << "Idle";         break;
            case pproto::CobotActionState::Connection   : line << "Connection";   break;
            case pproto::CobotActionState::Disconnect   : line << "Disconnect";   break;
            case pproto::CobotActionState::PowerOn      : line << "PowerOn";      break;
            case pproto::CobotActionState::PowerOff     : line << "PowerOff";     break;
            case pproto::CobotActionState::Sleep        : line << "Sleep";        break;
            case pproto::CobotActionState::MoveJoint    : line << "MoveJoint";    break;
            case pproto::CobotActionState::MovePose     : line << "MovePose";     break;
            case pproto::CobotActionState::MoveLine     : line << "MoveLine";     break;
            case pproto::CobotActionState::MovePath     : line << "MovePath";     break;
            case pproto::CobotActionState::UserCoord    : line << "UserCoord";    break;
            case pproto::CobotActionState::TcpOffset    : line << "TcpOffset";    break;
            case pproto::CobotActionState::RuntimeStart : line << "RuntimeStart"; break;
            case pproto::CobotActionState::RuntimeStop  : line << "RuntimeStop";  break;
        }
    }
    return line;
}

Line& operator<< (Line& line, const pproto::CobotActionPhase& actionPhase)
{
    if (line.toLogger())
    {
        switch (actionPhase)
        {
            case pproto::CobotActionPhase::Unknown : line << "Unknown"; break;
            case pproto::CobotActionPhase::Begin   : line << "Begin";   break;
            case pproto::CobotActionPhase::End     : line << "End";     break;
            case pproto::CobotActionPhase::Break   : line << "Break";   break;
            case pproto::CobotActionPhase::Stop    : line << "Stop";    break;
        }
    }
    return line;
}

} // namespace alog
