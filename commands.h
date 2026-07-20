#pragma once

#include "shared/container_ptr.h"
#include "shared/logger/logger.h"
#include "pproto/commands/base.h"
#include "qutils/commands/identity.h"

namespace pproto {
namespace command {

//----------------------------- Список команд --------------------------------

/**
  Выполнить план перемещений
*/
extern const QUuidEx CobotExecutePlan;

/**
  Остановить выполнение текущего плана
*/
extern const QUuidEx CobotStopExecute;

/**
  Команда возвращает информацию по последнему действию кобота
*/
extern const QUuidEx CobotLastPlanAction;

/**
  Событие эмитируется в момент начала выполнения cobot-плана
*/
extern const QUuidEx CobotPlanBegin;

/**
  Событие эмитируется в момент окончания выполнения cobot-плана
*/
extern const QUuidEx CobotPlanEnd;

/**
  Событие эмитируется в момент начала и окончания выполнения действия в рамках
  выполнения cobot-плана
*/
extern const QUuidEx CobotPlanAction;

} // namespace command

/**
  Определяет состояние в котором находится кобот в текущий момент
*/
enum class CobotActionState : quint32
{
    Unknown     = 0,
    Idle        = 1,
    Connection  = 2,  // Подключение к API кобота
    Disconnect  = 3,  // Отключение от API
    PowerOn     = 4,  // Включение питания на коботе
    PowerOff    = 5,  // Выключение питания на коботе
    Sleep       = 6,  // Выполнение действия/action "Пауза"
    MoveJoint   = 7,  // Установка заданных углов суставов
    MovePose    = 8,  // Перемещение в заданную позицию
    MoveLine    = 9,  // Перемещение в заданную позицию по линии
    MovePath    = 10, // Перемещение по заданной траектории
    UserCoord   = 11, // Установка пользовательских координат
};

/**
  Фазы перехода между состояниями кобота
*/
enum class CobotActionPhase : quint32
{
    Unknown = 0,
    Begin   = 1, // Фаза перехода к новому состоянию плана или действия.
    End     = 2, // Фаза выхода из текущего состояния плана или действия.
    Break   = 3, // Выход из текущего действия в результате возникновения
                 // ошибки выполнения.
    Stop    = 4, // Выход из текущего  действия  в результате  остановки
                 // выполнения плана пользователем  или  при  завершении
                 // работы сервиса
};

//---------------- Структуры данных используемые в сообщениях ----------------

namespace data {

struct CobotExecutePlan : Data<&command::CobotExecutePlan,
                                Message::Type::Command,
                                Message::Type::Answer>
{
    // Идентификатор плана
    Identity plan;

    DECLARE_B_SERIALIZE_FUNC
    J_SERIALIZE_MAP_ONE( "plan" , plan )
};

/**
  Структура с расширенной информацией об ошибке для команды ExecuteCobotPlan
*/
struct CobotExecutePlanError : MessageError, Data<&command::CobotExecutePlan,
                                                   Message::Type::Answer>
{
    // Идентификатор плана
    Identity plan;

    // Идентификатор плана выполняющегося в текущий момент
    Identity activePlan;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_BASE( MessageError )
        J_SERIALIZE_MAP_ITEM( "plan"        , plan       )
        J_SERIALIZE_MAP_ITEM( "active_plan" , activePlan )
    J_SERIALIZE_END
};

struct CobotActionInfo
{
    Identity plan;
    Identity action;

    CobotActionState state = {CobotActionState::Unknown};
    CobotActionPhase phase = {CobotActionPhase::Unknown};

    ErrorInfo::Ptr error;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_ITEM( "plan"   , plan   )
        J_SERIALIZE_MAP_ITEM( "action" , action )
        J_SERIALIZE_MAP_ITEM( "state"  , state  )
        J_SERIALIZE_MAP_ITEM( "phase"  , phase  )
        J_SERIALIZE_MAP_ITEM( "error"  , error  )
    J_SERIALIZE_END
};

struct CobotLastPlanAction : CobotActionInfo, Data<&command::CobotLastPlanAction,
                                                    Message::Type::Answer>
{};

struct CobotPlanBegin : Data<&command::CobotPlanBegin,
                              Message::Type::Event>
{
    // Идентификатор плана
    Identity plan;

    DECLARE_B_SERIALIZE_FUNC
    J_SERIALIZE_MAP_ONE( "plan" , plan )
};

struct CobotPlanEnd : Data<&command::CobotPlanEnd,
                            Message::Type::Event>
{
    // Идентификатор плана
    Identity plan;

    DECLARE_B_SERIALIZE_FUNC
    J_SERIALIZE_MAP_ONE( "plan" , plan )
};

struct CobotPlanAction : CobotActionInfo, Data<&command::CobotPlanAction,
                                                Message::Type::Event>
{};

} // namespace data
} // namespace pproto

namespace alog {

Line& operator<< (Line&, const pproto::CobotActionState&);
Line& operator<< (Line&, const pproto::CobotActionPhase&);

} // namespace alog

