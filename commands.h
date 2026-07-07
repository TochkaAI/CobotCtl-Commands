#pragma once

#include "shared/container_ptr.h"
#include "pproto/commands/base.h"
#include "pproto/commands/time_spec.h"

namespace pproto {
namespace command {

//----------------------------- Список команд --------------------------------

/**
  Событие эмитируется в моменты начала и окончания обновления  состояния  меха-
  низмов ViDetect. Обновление механизмов  ViDetect  происходит  после  фиксации
  факта изменения конфигурационных файлов. Описание отслеживаемых конфиг-файлов
  смотри в структуре ConfChange
*/
extern const QUuidEx ConfigChanged;

} // namespace command

//---------------- Структуры данных используемые в сообщениях ----------------

namespace data {

struct ConfigChanged : Data<&command::ConfigChanged,
                             Message::Type::Event>
{
    // ConfChange::File  file  = {ConfChange::File::Unknown};
    // ConfChange::Phase phase = {ConfChange::Phase::Unknown};
    //
    // DECLARE_B_SERIALIZE_FUNC
    //
    // J_SERIALIZE_BEGIN
    //     J_SERIALIZE_MAP_ITEM( "file" , file  )
    //     J_SERIALIZE_MAP_OPT ( "phase", phase )
    // J_SERIALIZE_END
};

} // namespace data
} // namespace pproto
