#include "commands.h"
#include "pproto/commands/pool.h"

namespace pproto {
namespace command {

#define REGISTRY_COMMAND_SINGLPROC(COMMAND, UUID) \
    const QUuidEx COMMAND = command::Pool::Registry{UUID, #COMMAND, false};

#define REGISTRY_COMMAND_MULTIPROC(COMMAND, UUID) \
    const QUuidEx COMMAND = command::Pool::Registry{UUID, #COMMAND, true};

REGISTRY_COMMAND_SINGLPROC(CobotPlanList,          "218cb243-25f6-4410-9afa-9b41245853fa")
REGISTRY_COMMAND_SINGLPROC(CobotActivePlan,        "24fdb409-ded4-4127-a17b-99090e62ca8c")
REGISTRY_COMMAND_SINGLPROC(CobotPlanInfo,          "567cddc9-be11-43c1-a434-6a106fa05638")
REGISTRY_COMMAND_SINGLPROC(CobotDynamicPlanInfo,   "cde0d2e8-b294-42e6-86fc-fc0339e30721")
REGISTRY_COMMAND_SINGLPROC(CobotDynamicPlanUpdate, "62485a2b-e9f1-429b-a2c7-b664101af3c3")
REGISTRY_COMMAND_SINGLPROC(CobotDynamicPlanRemove, "970ce725-489f-4586-8077-44621f413ec9")
REGISTRY_COMMAND_SINGLPROC(CobotExecutePlan,       "2b43d67c-26a2-4889-b55a-df787681a7c5")
REGISTRY_COMMAND_SINGLPROC(CobotStopExecution,     "f1f4b015-dc59-43ca-a352-205a6b0a4291")
REGISTRY_COMMAND_SINGLPROC(CobotPauseExecution,    "4f3a14d0-afb2-40f1-8a95-2de3466c7e79")
REGISTRY_COMMAND_SINGLPROC(CobotLastAction,        "b7b8e0b0-de01-4344-9d58-5bc48932be71")
REGISTRY_COMMAND_SINGLPROC(CobotPlanBegin,         "6df740aa-3715-4e9b-9f2f-5a4705001150")
REGISTRY_COMMAND_SINGLPROC(CobotPlanEnd,           "d346775f-e071-45c2-8f81-7504263c591e")
REGISTRY_COMMAND_SINGLPROC(CobotPlanAction,        "8f02448e-4020-4bdd-aa95-6f55b53ec5d6")
REGISTRY_COMMAND_SINGLPROC(CobotCurrentPose,       "58e3b0da-05ca-40b5-ae55-d4f58c079f7c")
REGISTRY_COMMAND_SINGLPROC(CobotPowerInfo,         "29f7a7c2-829f-44a6-a8b9-cfa911f1b534")
REGISTRY_COMMAND_SINGLPROC(CobotPowerOn,           "ff5c9604-b2ad-408d-a9e4-787c6a805d66")
REGISTRY_COMMAND_SINGLPROC(CobotPowerOff,          "8f64c764-80f0-45ac-b9ec-b1a207cd7135")

#undef REGISTRY_COMMAND_SINGLPROC
#undef REGISTRY_COMMAND_MULTIPROC

} // namespace command

namespace data {

void CobotPlanError::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1

    // Структуры унаследованные от MessageError сериализуются в особом порядке,
    // поэтому для них сериализация/десериализация базового класса не обязательна
    // stream << B_BASE_CLASS(MessageError);

    stream << identity;
    stream << activeIdentity;
    B_SERIALIZE_RETURN
}

void CobotPlanError::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)

    // Структуры унаследованные от MessageError сериализуются в особом порядке,
    // поэтому для них сериализация/десериализация базового класса не обязательна
    // stream >> B_BASE_CLASS(MessageError);

    stream >> identity;
    stream >> activeIdentity;
    B_DESERIALIZE_END
}

void CobotPlanListA::Item::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << identity;
    stream << descript;
    B_SERIALIZE_RETURN
}

void CobotPlanListA::Item::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> identity;
    stream >> descript;
    B_DESERIALIZE_END
}

void CobotPlanListA::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << plans;
    stream << dynamicPlans;
    B_SERIALIZE_RETURN
}

void CobotPlanListA::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> plans;
    stream >> dynamicPlans;
    B_DESERIALIZE_END
}

void CobotActivePlanA::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << identity;
    stream << descript;
    stream << dynamic;
    stream << paused;
    B_SERIALIZE_RETURN
}

void CobotActivePlanA::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> identity;
    stream >> descript;
    stream >> dynamic;
    stream >> paused;
    B_DESERIALIZE_END
}

void CobotExecutePlan::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << identity;
    stream << dynamic;
    B_SERIALIZE_RETURN
}

void CobotExecutePlan::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> identity;
    stream >> dynamic;
    B_DESERIALIZE_END
}

void CobotActionInfo::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << plan;
    stream << dynamic;
    stream << action;
    stream << state;
    stream << phase;
    stream << error;
    stream << indexAction;
    stream << totalActions;
    B_SERIALIZE_RETURN
}

void CobotActionInfo::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> plan;
    stream >> dynamic;
    stream >> action;
    stream >> state;
    stream >> phase;
    stream >> error;
    stream >> indexAction;
    stream >> totalActions;
    B_DESERIALIZE_END
}

void CobotPlanBegin::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << identity;
    stream << dynamic;
    B_SERIALIZE_RETURN
}

void CobotPlanBegin::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> identity;
    stream >> dynamic;
    B_DESERIALIZE_END
}

void CobotPlanEnd::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << identity;
    stream << dynamic;
    B_SERIALIZE_RETURN
}

void CobotPlanEnd::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> identity;
    stream >> dynamic;
    B_DESERIALIZE_END
}

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

void CobotDimension::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << millimeter;
    stream << degree;
    B_SERIALIZE_RETURN
}

void CobotDimension::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> millimeter;
    stream >> degree;
    B_DESERIALIZE_END
}

void CobotDynamics::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << speedFraction;
    stream << acceleration;
    stream << velocity;
    B_SERIALIZE_RETURN
}

void CobotDynamics::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> speedFraction;
    stream >> acceleration;
    stream >> velocity;
    B_DESERIALIZE_END
}

void CobotAction::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << stringType;
    stream << identity;
    B_SERIALIZE_RETURN
}

void CobotAction::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> stringType;
    stream >> identity;
    B_DESERIALIZE_END
}

void CobotSleepAction::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << B_BASE_CLASS(CobotAction);
    stream << time;
    B_SERIALIZE_RETURN
}

void CobotSleepAction::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> B_BASE_CLASS(CobotAction);
    stream >> time;
    B_DESERIALIZE_END
}

void CobotMoveJointAction::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << B_BASE_CLASS(CobotAction);
    stream << dimension;
    stream << dynamics;
    stream << joints;
    B_SERIALIZE_RETURN
}

void CobotMoveJointAction::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> B_BASE_CLASS(CobotAction);
    stream >> dimension;
    stream >> dynamics;
    stream >> joints;
    B_DESERIALIZE_END
}

void CobotMovePoseAction::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << B_BASE_CLASS(CobotAction);
    stream << dimension;
    stream << dynamics;
    stream << poses;
    stream << posesFilePath;
    B_SERIALIZE_RETURN
}

void CobotMovePoseAction::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> B_BASE_CLASS(CobotAction);
    stream >> dimension;
    stream >> dynamics;
    stream >> poses;
    stream >> posesFilePath;
    B_DESERIALIZE_END
}

void CobotMovePathAction::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << B_BASE_CLASS(CobotAction);
    stream << dimension;
    stream << dynamics;
    stream << poses;
    stream << posesFilePath;
    B_SERIALIZE_RETURN
}

void CobotMovePathAction::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> B_BASE_CLASS(CobotAction);
    stream >> dimension;
    stream >> dynamics;
    stream >> poses;
    stream >> posesFilePath;
    B_DESERIALIZE_END
}

void CobotUserCoordAction::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << B_BASE_CLASS(CobotAction);
    stream << dimension;
    stream << reset;
    stream << calibrate;
    stream << calibrateType;
    stream << calibratePoints;
    B_SERIALIZE_RETURN
}

void CobotUserCoordAction::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> B_BASE_CLASS(CobotAction);
    stream >> dimension;
    stream >> reset;
    stream >> calibrate;
    stream >> calibrateType;
    stream >> calibratePoints;
    B_DESERIALIZE_END
}

void CobotTcpOffsetAction::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << B_BASE_CLASS(CobotAction);
    stream << dimension;
    stream << offset;
    B_SERIALIZE_RETURN
}

void CobotTcpOffsetAction::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> B_BASE_CLASS(CobotAction);
    stream >> dimension;
    stream >> offset;
    B_DESERIALIZE_END
}

void CobotPlan::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << identity;
    stream << descript;
    stream << dynamic;
    stream << powerOff;

    QList<CobotAction::Type> types;
    for (CobotAction* action : actions)
    {
        if (action)
            types.append(action->type());
        else
            types.append(CobotAction::Type::Unknown);
    }
    stream << types;

    for (int i = 0; i < types.count(); ++i)
    {
        if (CobotAction::Type::Sleep == types[i])
        {
            CobotSleepAction* act = static_cast<CobotSleepAction*>(actions.item(i));
            stream << *act;
        }
        else if (CobotAction::Type::MoveJoint == types[i])
        {
            CobotMoveJointAction* act = static_cast<CobotMoveJointAction*>(actions.item(i));
            stream << *act;
        }
        else if (CobotAction::Type::MovePose == types[i])
        {
            CobotMovePoseAction* act = static_cast<CobotMovePoseAction*>(actions.item(i));
            stream << *act;
        }
        else if (CobotAction::Type::MoveLine == types[i])
        {
            CobotMoveLineAction* act = static_cast<CobotMoveLineAction*>(actions.item(i));
            stream << *act;
        }
        // else if (CobotAction::Type::MovePath == types[i])
        // {
        // }
        else if (CobotAction::Type::UserCoord == types[i])
        {
            CobotUserCoordAction* act = static_cast<CobotUserCoordAction*>(actions.item(i));
            stream << *act;
        }
        else if (CobotAction::Type::TcpOffset == types[i])
        {
            CobotTcpOffsetAction* act = static_cast<CobotTcpOffsetAction*>(actions.item(i));
            stream << *act;
        }
    }
    B_SERIALIZE_RETURN
}

void CobotPlan::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> identity;
    stream >> descript;
    stream >> dynamic;
    stream >> powerOff;

    QList<CobotAction::Type> types;
    stream >> types;

    for (int i = 0; i < types.count(); ++i)
    {
        if (CobotAction::Type::Sleep == types[i])
        {
            CobotSleepAction* act = new CobotSleepAction;
            stream >> *act;
            actions.add(act);
        }
        else if (CobotAction::Type::MoveJoint == types[i])
        {
            CobotMoveJointAction* act = new CobotMoveJointAction;
            stream >> *act;
            actions.add(act);
        }
        else if (CobotAction::Type::MovePose == types[i])
        {
            CobotMovePoseAction* act = new CobotMovePoseAction;
            stream >> *act;
            actions.add(act);
        }
        else if (CobotAction::Type::MoveLine == types[i])
        {
            CobotMoveLineAction* act = new CobotMoveLineAction;
            stream >> *act;
            actions.add(act);
        }
        // else if (CobotAction::Type::MovePath == types[i])
        // {
        // }
        else if (CobotAction::Type::UserCoord == types[i])
        {
            CobotUserCoordAction* act = new CobotUserCoordAction;
            stream >> *act;
            actions.add(act);
        }
        else if (CobotAction::Type::TcpOffset == types[i])
        {
            CobotTcpOffsetAction* act = new CobotTcpOffsetAction;
            stream >> *act;
            actions.add(act);
        }
        else
        {
            // Вычитываем и пропускаем неизвестное действие
            SByteArray ba; (void) ba;
            stream >> ba;
        }
    }
    B_DESERIALIZE_END
}

void CobotPlanInfo::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << identity;
    stream << plan;
    B_SERIALIZE_RETURN
}

void CobotPlanInfo::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> identity;
    stream >> plan;
    B_DESERIALIZE_END
}

void CobotDynamicPlanInfo::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << identity;
    stream << plan;
    B_SERIALIZE_RETURN
}

void CobotDynamicPlanInfo::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> identity;
    stream >> plan;
    B_DESERIALIZE_END
}

void CobotDynamicPlanUpdate::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << plan;
    B_SERIALIZE_RETURN
}

void CobotDynamicPlanUpdate::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> plan;
    B_DESERIALIZE_END
}

void CobotDynamicPlanUpdateA::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << identity;
    B_SERIALIZE_RETURN
}

void CobotDynamicPlanUpdateA::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> identity;
    B_DESERIALIZE_END
}

void CobotDynamicPlanRemove::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << identity;
    B_SERIALIZE_RETURN
}

void CobotDynamicPlanRemove::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> identity;
    B_DESERIALIZE_END
}

void CobotCurrentPose::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << dimension;
    B_SERIALIZE_RETURN
}

void CobotCurrentPose::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> dimension;
    B_DESERIALIZE_END
}

void CobotCurrentPoseA::toRaw(bserial::DataStream& stream) const
{
    B_SERIALIZE_V1
    stream << dimension;
    stream << joints;
    stream << tcpPose;
    B_SERIALIZE_RETURN
}

void CobotCurrentPoseA::fromRaw(const bserial::RawVector& vect)
{
    B_DESERIALIZE_V1(vect)
    stream >> dimension;
    stream >> joints;
    stream >> tcpPose;
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
