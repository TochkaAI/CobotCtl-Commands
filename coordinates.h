#pragma once

#include "pproto/commands/base.h"
#include "pproto/commands/time_spec.h"

#include "commands/cobot_pose.h"

namespace pproto {
namespace command {

//----------------------------- Список команд --------------------------------

/**
  Команда используется для получения/передачи координат камеры
*/
extern const QUuidEx Coordinates;

} // namespace command

//---------------- Структуры данных используемые в сообщениях ----------------

namespace data {

struct Coordinates : Data<&command::Coordinates,
                           Message::Type::Event>
{
    typedef container_ptr<Coordinates> Ptr;

    // Глобальные координаты TCP кобота. Формат: x, y, z, rx, ry, rz
    CobotPose globalPose;

    // Признак наличия локальных координат для TCP кобота. Параметр может
    // принимать значения 0, 1.
    quint8 localExists = {0};

    // Локальные координаты TCP кобота в пользовательской системе координат.
    // Формат: x, y, z, rx, ry, rz
    CobotPose localPose;

    // Время получения координат (UTC)
    data::TimeSpec time;

    DECLARE_B_SERIALIZE_FUNC
    DECLARE_J_SERIALIZE_FUNC
};

template<typename This, typename Packer>
Packer& Coordinates::jserialize(const This* ct, Packer& p)
{
    This* t = const_cast<This*>(ct);

    p.startObject();

    if (p.isWriter())
    {
        J_SERIALIZE_MAP_ITEM( "glp" , globalPose  )
        J_SERIALIZE_MAP_ITEM( "lce" , localExists )

        if (t->localExists)
            J_SERIALIZE_MAP_ITEM( "lcp" , localPose )

        J_SERIALIZE_MAP_ITEM( "time" , time )
    }
    else if (p.isReader())
    {
        J_SERIALIZE_MAP_ITEM( "glp"  , globalPose  )
        J_SERIALIZE_MAP_ITEM( "lce"  , localExists )
        J_SERIALIZE_MAP_OPT ( "lcp"  , localPose   )
        J_SERIALIZE_MAP_ITEM( "time" , time        )
    }
    return p.endObject();
}

} // namespace data
} // namespace pproto
