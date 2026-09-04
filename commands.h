#pragma once

#include "shared/container_ptr.h"
#include "shared/logger/logger.h"
#include "pproto/commands/base.h"
#include "qutils/commands/identity.h"

namespace pproto {
namespace command {

//----------------------------- Список команд --------------------------------

/**
  Команда возвращает информацию о текущем плане выполнения. Отсутствие контента
  в ответном сообщении говорит о том, что никакой план не выполняется
*/
extern const QUuidEx CobotPlanInfo;

/**
  Выполнить план перемещений
*/
extern const QUuidEx CobotExecutePlan;

/**
  Остановить выполнение текущего плана
*/
extern const QUuidEx CobotStopExecution;

/**
  Команда останавливает/возобновляет выполнение текущего  плана.  Остановка
  осуществляется через передачу в поле tag(0) значения 1. Для возобновления
  выполнения плана надо передать в tag(0) значения 0
*/
extern const QUuidEx CobotPauseExecution;

/**
  Событие эмитируется в момент постановки на паузу текущего плана. Поле tag(0)
  содержит состояние флага паузы
*/
//extern const QUuidEx CobotPauseChanged;

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
    Unknown      = 0,
    Idle         = 1,
    Connection   = 2,  // Подключение к API кобота
    Disconnect   = 3,  // Отключение от API
    PowerOn      = 4,  // Включение питания на коботе
    PowerOff     = 5,  // Выключение питания на коботе
    Sleep        = 6,  // Выполнение действия/action "Пауза"
    MoveJoint    = 7,  // Установка заданных углов суставов
    MovePose     = 8,  // Перемещение в заданную позицию
    MoveLine     = 9,  // Перемещение в заданную позицию по линии
    MovePath     = 10, // Перемещение по заданной траектории
    UserCoord    = 11, // Установка пользовательских координат
    TcpOffset    = 12, // Смещение координаты TCP
    RuntimeStart = 13,
    RuntimeStop  = 14,
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

struct CobotPlanInfoA : Data<&command::CobotPlanInfo,
                              Message::Type::Answer>
{
    // Идентификатор плана
    Identity identity;

    // Признак приостановки выполнения плана
    bool paused = {false};

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_ITEM( "identity" , identity )
        J_SERIALIZE_MAP_ITEM( "paused"   , paused   )
    J_SERIALIZE_END
};

struct CobotExecutePlan : Data<&command::CobotExecutePlan,
                                Message::Type::Command,
                                Message::Type::Answer>
{
    // Идентификатор плана
    Identity identity;

    DECLARE_B_SERIALIZE_FUNC
    J_SERIALIZE_MAP_ONE( "identity" , identity )
};

/**
  Структура с расширенной информацией об ошибке для команды ExecuteCobotPlan
*/
struct CobotExecutePlanError : MessageError, Data<&command::CobotExecutePlan,
                                                   Message::Type::Answer>
{
    // Идентификатор плана
    Identity identity;

    // Идентификатор плана выполняющегося в текущий момент
    Identity activeIdentity;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_BASE( MessageError )
        J_SERIALIZE_MAP_ITEM( "identity"        , identity       )
        J_SERIALIZE_MAP_ITEM( "active_identity" , activeIdentity )
    J_SERIALIZE_END
};

struct CobotActionInfo
{
    Identity plan;   // Идентификатор плана
    Identity action; // Идентификатор действия

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
    Identity identity;

    DECLARE_B_SERIALIZE_FUNC
    J_SERIALIZE_MAP_ONE( "identity" , identity )
};

struct CobotPlanEnd : Data<&command::CobotPlanEnd,
                            Message::Type::Event>
{
    // Идентификатор плана
    Identity identity;

    DECLARE_B_SERIALIZE_FUNC
    J_SERIALIZE_MAP_ONE( "identity" , identity )
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

