#pragma once

#include "shared/container_ptr.h"
#include "shared/logger/logger.h"

#include "pproto/commands/base.h"
#include "pproto/commands/identity.h"

#include <vector>

namespace pproto {
namespace command {

//----------------------------- Список команд --------------------------------

/**
  Команда возвращает информацию о доступных планах (статических/динамических)
*/
extern const QUuidEx CobotPlanList;

/**
  Команда возвращает информацию о текущем плане выполнения. Отсутствие контента
  в ответном сообщении говорит о том, что никакой план не выполняется
*/
extern const QUuidEx CobotActivePlan;

/**
  Команда возвращает информацию о статическом плане выполнения
*/
extern const QUuidEx CobotPlanInfo;

/**
  Команда возвращает информацию о динамическом плане выполнения
*/
extern const QUuidEx CobotDynamicPlanInfo;

/**
  Команда создает/обновляет динамический план выполнения
*/
extern const QUuidEx CobotDynamicPlanUpdate;

/**
  Команда удаляет динамический план выполнения
*/
extern const QUuidEx CobotDynamicPlanRemove;

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
  Команда возвращает информацию по последнему действию кобота
*/
extern const QUuidEx CobotLastAction;

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

/**
  Событие эмитируется в моменты, когда происходит движение кобота по координа-
  там траектории. Событие эмитируется на протяжении выполнения всего плана.
*/
extern const QUuidEx CobotMoveProgress;

/**
  Команда возвращает текущие координаты кобота
*/
extern const QUuidEx CobotCurrentPose;

/**
  Команда возвращает статус рабочего состояния кобота. В активном состоянии
  поле tag(0) будет содержать значения 1, в состоянии остановки поле tag(0)
  будет содержать 0.
*/
extern const QUuidEx CobotPowerInfo;

/**
  Команда переводит кобота в активное состояние
*/
extern const QUuidEx CobotPowerOn;

/**
  Команда переводит кобота в состояние остановки
*/
extern const QUuidEx CobotPowerOff;

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
    RuntimeStart = 13, // Запуск механизма API-RuntimeMachine
    RuntimeStop  = 14, // Остановка механизма API-RuntimeMachine
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

/**
  Структура с расширенной информацией об ошибке
*/
struct CobotPlanError : MessageError
{
    // Идентификатор плана
    IdentityS identity;

    // Идентификатор плана выполняющегося в текущий момент
    IdentityS activeIdentity;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_BASE( MessageError )
        J_SERIALIZE_MAP_ITEM( "identity"        , identity       )
        J_SERIALIZE_MAP_ITEM( "active_identity" , activeIdentity )
    J_SERIALIZE_END
};

struct CobotPlanListA : Data<&command::CobotPlanList,
                              Message::Type::Answer>
{
    struct Item
    {
        // Идентификатор плана
        IdentityS identity;

        // Описание плана
        QString descript;

        DECLARE_B_SERIALIZE_FUNC

        J_SERIALIZE_BEGIN
            J_SERIALIZE_MAP_ITEM( "identity" , identity )
            J_SERIALIZE_MAP_ITEM( "descript" , descript )
        J_SERIALIZE_END
    };

    // Список статических планов
    QList<Item> plans;

    // Список динамических планов
    QList<Item> dynamicPlans;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_ITEM( "plans"         , plans        )
        J_SERIALIZE_MAP_ITEM( "dynamic_plans" , dynamicPlans )
    J_SERIALIZE_END
};

struct CobotActivePlanA : Data<&command::CobotActivePlan,
                                Message::Type::Answer>
{
    typedef container_ptr<CobotActivePlanA> Ptr;

    // Идентификатор плана
    IdentityS identity;

    // Описание плана
    QString descript;

    // Признак динамического плана
    bool dynamic = {false};

    // Признак приостановки выполнения плана
    bool paused = {false};

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_ITEM( "identity" , identity )
        J_SERIALIZE_MAP_ITEM( "descript" , descript )
        J_SERIALIZE_MAP_ITEM( "dynamic"  , dynamic  )
        J_SERIALIZE_MAP_ITEM( "paused"   , paused   )
    J_SERIALIZE_END
};

struct CobotExecutePlan : Data<&command::CobotExecutePlan,
                                Message::Type::Command,
                                Message::Type::Answer>
{
    // Идентификатор плана
    IdentityS identity;

    // Признак динамического плана
    bool dynamic = {false};

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_ITEM( "identity" , identity )
        J_SERIALIZE_MAP_OPT ( "dynamic"  , dynamic  )
    J_SERIALIZE_END
};

/**
  Структура с расширенной информацией об ошибке для команды CobotExecutePlan
*/
struct CobotExecutePlanError : CobotPlanError, Data<&command::CobotExecutePlan,
                                                     Message::Type::Answer>
{};

struct CobotActionInfo
{
    // Идентификатор плана
    IdentityS plan;

    // Признак динамического плана
    bool dynamic = {false};

    // Идентификатор действия
    IdentityS action;

    // Индекс текущего исполняемого действия
    int indexAction = {-1};

    // Общее количество действий
    int totalActions = {-1};

    CobotActionState state = {CobotActionState::Unknown};
    CobotActionPhase phase = {CobotActionPhase::Unknown};

    ErrorInfo::Ptr error;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_ITEM( "plan"          , plan         )
        J_SERIALIZE_MAP_ITEM( "dynamic"       , dynamic      )
        J_SERIALIZE_MAP_ITEM( "action"        , action       )
        J_SERIALIZE_MAP_ITEM( "index_action"  , indexAction  )
        J_SERIALIZE_MAP_ITEM( "total_actions" , totalActions )
        J_SERIALIZE_MAP_ITEM( "state"         , state        )
        J_SERIALIZE_MAP_ITEM( "phase"         , phase        )
        J_SERIALIZE_MAP_ITEM( "error"         , error        )
    J_SERIALIZE_END
};

struct CobotLastAction : CobotActionInfo, Data<&command::CobotLastAction,
                                                Message::Type::Answer>
{};

struct CobotPlanBegin : Data<&command::CobotPlanBegin,
                              Message::Type::Event>
{
    // Идентификатор плана
    IdentityS identity;

    // Признак динамического плана
    bool dynamic = {false};

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_ITEM( "identity" , identity )
        J_SERIALIZE_MAP_OPT ( "dynamic"  , dynamic  )
    J_SERIALIZE_END
};

struct CobotPlanEnd : Data<&command::CobotPlanEnd,
                            Message::Type::Event>
{
    // Идентификатор плана
    IdentityS identity;

    // Признак динамического плана
    bool dynamic = {false};

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_ITEM( "identity" , identity )
        J_SERIALIZE_MAP_OPT ( "dynamic"  , dynamic  )
    J_SERIALIZE_END
};

struct CobotPlanAction : CobotActionInfo, Data<&command::CobotPlanAction,
                                                Message::Type::Event>
{};

struct CobotMoveProgress : Data<&command::CobotMoveProgress,
                                 Message::Type::Event>
{
    // Идентификатор плана
    IdentityS plan;

    // Признак динамического плана
    bool dynamic = {false};

    // Идентификатор действия
    IdentityS action;

    enum class Phase : quint32
    {
        Unknown = 0,
        Begin   = 1, // Событие эмитируется перед началом первого перемещения
        End     = 2, // Событие эмитируется после выполнения всех перемещений
        Move    = 3, // Событие эмитируется в момент текущего перемещения
    };
    Phase phase = {Phase::Unknown};

    // Индекс текущего перемещения
    int indexMove = {-1};

    // Общее количество перемещений в рамках выполняемого плана
    int totalMoves = {-1};

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_ITEM( "plan"        , plan       )
        J_SERIALIZE_MAP_ITEM( "dynamic"     , dynamic    )
        J_SERIALIZE_MAP_ITEM( "action"      , action     )
        J_SERIALIZE_MAP_ITEM( "phase"       , phase      )
        J_SERIALIZE_MAP_ITEM( "index_move"  , indexMove  )
        J_SERIALIZE_MAP_ITEM( "total_moves" , totalMoves )
    J_SERIALIZE_END
};

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

/**
  Содержит информацию по размерностям для линейных  и  угловых  координат.
  Линейные размеры могут быть представлены в метрах/миллиметрах, угловые -
  в радианах/градусах
*/
struct CobotDimension
{
    bool millimeter = {false};
    bool degree = {false};

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_OPT( "millimeter" , millimeter )
        J_SERIALIZE_MAP_OPT( "degree"     , degree     )
    J_SERIALIZE_END
};

/**
  Параметры определяющие динамику движений кобота. Для угловых перемещений
  (move_joint) параметры acceleration, velocity задаются  в градусах,  для
  линейных перемещений (move_line, move_pose) параметры acc, vel  задаются
  в метрах
*/
struct CobotDynamics
{
    double speedFraction = {0.3};
    double acceleration  = {3};
    double velocity      = {2};

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_OPT( "speed_fraction" , speedFraction )
        J_SERIALIZE_MAP_OPT( "acceleration"   , acceleration  )
        J_SERIALIZE_MAP_OPT( "velocity"       , velocity      )
    J_SERIALIZE_END
};

/**
  Базовая структура для действия
*/
struct CobotAction
{
    virtual ~CobotAction() = default;

    enum class Type : quint32
    {
        Unknown   = 0,
        Sleep     = 1,
        MoveJoint = 2,
        MovePose  = 3,
        MoveLine  = 4,
        MovePath  = 5,
        UserCoord = 6,
        TcpOffset = 7,
    };
    virtual Type type() const {return Type::Unknown;}

    QString stringType;
    IdentityS identity;

    typedef lst::List<CobotAction, lst::CompareItemDummy> List;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BASE_BEGIN
        J_SERIALIZE_MAP_ITEM( "string_type" , stringType )
        J_SERIALIZE_MAP_ITEM( "identity"    , identity   )
    J_SERIALIZE_BASE_END
};

struct CobotSleepAction : CobotAction
{
    Type type() const {return Type::Sleep;}

    // Время паузы (в миллисекундах)
    int time = {0};

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_BASE( CobotAction )
        J_SERIALIZE_MAP_ITEM( "time" , time )
    J_SERIALIZE_END
};

struct CobotMoveJointAction : CobotAction
{
    Type type() const {return Type::MoveJoint;}

    CobotDimension dimension;
    CobotDynamics  dynamics;

    // Углы суставов
    QList<CobotPose> joints;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_BASE( CobotAction )
        J_SERIALIZE_MAP_OPT ( "dimension", dimension )
        J_SERIALIZE_MAP_OPT ( "dynamics" , dynamics  )
        J_SERIALIZE_MAP_ITEM( "joints"   , joints    )
    J_SERIALIZE_END
};

struct CobotMovePoseAction : CobotAction
{
    Type type() const {return Type::MovePose;}

    CobotDimension dimension;
    CobotDynamics  dynamics;

    // Координаты TCP
    QList<CobotPose> poses;

    // Полный путь до файла с координатами. Используется для загрузки
    // координат из конфигурационного файла. Для API  параметр  носит
    // информационный характер
    QString posesFilePath;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_BASE( CobotAction )
        J_SERIALIZE_MAP_OPT ( "dimension"       , dimension     )
        J_SERIALIZE_MAP_OPT ( "dynamics"        , dynamics      )
        J_SERIALIZE_MAP_ITEM( "poses"           , poses         )
        J_SERIALIZE_MAP_OPT ( "poses_file_path" , posesFilePath )
    J_SERIALIZE_END
};

struct CobotMoveLineAction : CobotMovePoseAction
{
    Type type() const {return Type::MoveLine;}
};

struct CobotMovePathAction : CobotAction
{
    Type type() const {return Type::MovePath;}

    CobotDimension dimension;
    CobotDynamics  dynamics;

    // Координаты TCP
    QList<CobotPose> poses;

    // Полный путь до файла с координатами. Используется для загрузки
    // координат из конфигурационного файла. Для API  параметр  носит
    // информационный характер
    QString posesFilePath;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_BASE( CobotAction )
        J_SERIALIZE_MAP_OPT ( "dimension"       , dimension     )
        J_SERIALIZE_MAP_OPT ( "dynamics"        , dynamics      )
        J_SERIALIZE_MAP_ITEM( "poses"           , poses         )
        J_SERIALIZE_MAP_OPT ( "poses_file_path" , posesFilePath )
    J_SERIALIZE_END
};

struct CobotUserCoordAction : CobotAction
{
    Type type() const {return Type::UserCoord;}

    CobotDimension dimension;

    // Флаг сброса локальных координат к глобальным
    bool reset = {false};

    enum class Calibrate
    {
        ByCurrentPose = 0, // За нулевую точку пользовательской системы
                           // координат берется текущее положение TCP.
        ByThreePoints = 1  // Пользовательская система координат создается
                           // на основе трех точек.
    };

    Calibrate calibrate = {Calibrate::ByCurrentPose};

    // Type
    //   0 - oxy origin, +x axis, xy plane (+y direction)
    //   1 - oxz origin, +x axis, xz plane (+z direction)
    //   2 - oyz origin, +y axis, yz plane (+z direction)
    //   3 - oyx origin, +y axis, yx plane (+x direction)
    //   4 - ozx origin, +z axis, zx plane (+x direction)
    //   5 - ozy origin, +z axis, zy plane (+y direction)
    int calibrateType = {0};

    // Три точки для создания пользовательской системы координат
    QList<CobotPose> calibratePoints;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_BASE( CobotAction )
        J_SERIALIZE_MAP_OPT( "dimension"        , dimension       )
        J_SERIALIZE_MAP_OPT( "reset"            , reset           )
        J_SERIALIZE_MAP_OPT( "calibrate"        , calibrate       )
        J_SERIALIZE_MAP_OPT( "calibrate_type"   , calibrateType   )
        J_SERIALIZE_MAP_OPT( "calibrate_points" , calibratePoints )
    J_SERIALIZE_END
};

struct CobotTcpOffsetAction : CobotAction
{
    Type type() const {return Type::TcpOffset;}

    CobotDimension dimension;

    // Смещение TCP
    CobotPose offset;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_BASE( CobotAction )
        J_SERIALIZE_MAP_OPT( "dimension" , dimension )
        J_SERIALIZE_MAP_OPT( "offset"    , offset    )
    J_SERIALIZE_END
};

struct CobotPlan : clife_base
{
    typedef clife_ptr<CobotPlan> Ptr;

    IdentityS identity;
    QString   descript;

    // Признак динамического плана
    bool dynamic = {false};

    // Отключение питание на коботе после выполнения плана
    bool powerOff = {false};

    CobotAction::List actions;

    typedef Identity::Compare<CobotPlan, Identity::CompareField::NameIndex> CobotPlanCompare;
    typedef lst::List<CobotPlan, CobotPlanCompare, clife_alloc<CobotPlan>> List;

    // Вспомогательная структура для сериализации гетерогенного списка действий
    struct ActionSerialize
    {
        CobotAction::Type type = {CobotAction::Type::Unknown};
        SByteArray data;

        J_SERIALIZE_BEGIN
            J_SERIALIZE_ITEM( type )
            J_SERIALIZE_ITEM( data )
        J_SERIALIZE_END
    };

    DECLARE_B_SERIALIZE_FUNC
    DECLARE_J_SERIALIZE_FUNC
};

struct CobotPlanInfo : Data<&command::CobotPlanInfo,
                             Message::Type::Command,
                             Message::Type::Answer>
{
    // Идентификатор плана
    IdentityS identity;

    // Информация о плане
    CobotPlan::Ptr plan;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_ITEM( "identity" , identity )
        J_SERIALIZE_MAP_OPT ( "plan"     , plan     )
    J_SERIALIZE_END
};

/**
  Структура с расширенной информацией об ошибке для команды CobotPlanInfo
*/
struct CobotPlanInfoError : CobotPlanError, Data<&command::CobotPlanInfo,
                                                  Message::Type::Answer>
{};

struct CobotDynamicPlanInfo : Data<&command::CobotDynamicPlanInfo,
                                    Message::Type::Command,
                                    Message::Type::Answer>
{
    // Идентификатор плана
    IdentityS identity;

    // Информация о плане
    CobotPlan::Ptr plan;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_ITEM( "identity" , identity )
        J_SERIALIZE_MAP_OPT ( "plan"     , plan     )
    J_SERIALIZE_END
};

/**
  Структура с расширенной информацией об ошибке для команды CobotDynamicPlanInfo
*/
struct CobotDynamicPlanInfoError : CobotPlanError,
                                   Data<&command::CobotDynamicPlanInfo,
                                         Message::Type::Answer>
{};

struct CobotDynamicPlanUpdate : Data<&command::CobotDynamicPlanUpdate,
                                      Message::Type::Command>
{
    CobotPlan::Ptr plan;

    DECLARE_B_SERIALIZE_FUNC
    J_SERIALIZE_MAP_ONE( "plan" , plan )
};

struct CobotDynamicPlanUpdateA : Data<&command::CobotDynamicPlanUpdate,
                                       Message::Type::Answer>
{
    // Идентификатор обновленного плана
    IdentityS identity;

    DECLARE_B_SERIALIZE_FUNC
    J_SERIALIZE_MAP_ONE( "identity" , identity )
};

struct CobotDynamicPlanRemove : Data<&command::CobotDynamicPlanRemove,
                                      Message::Type::Command,
                                      Message::Type::Answer>
{
    // Идентификатор плана
    IdentityS identity;

    DECLARE_B_SERIALIZE_FUNC
    J_SERIALIZE_MAP_ONE( "identity" , identity )
};

/**
  Структура с расширенной информацией об ошибке для команды CobotDynamicPlanRemove
*/
struct CobotDynamicPlanRemoveError : CobotPlanError,
                                     Data<&command::CobotDynamicPlanRemove,
                                           Message::Type::Answer>
{};

struct CobotCurrentPose : Data<&command::CobotCurrentPose,
                                Message::Type::Command>
{
    CobotDimension dimension;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_OPT( "dimension" , dimension )
    J_SERIALIZE_END
};

struct CobotCurrentPoseA : Data<&command::CobotCurrentPose,
                                 Message::Type::Answer>
{
    CobotDimension dimension;

    // Текущие углы суставов кобота
    CobotPose joints;

    // Текущее положение TCP в декартовых координатах
    CobotPose tcpPose;

    DECLARE_B_SERIALIZE_FUNC

    J_SERIALIZE_BEGIN
        J_SERIALIZE_MAP_OPT( "dimension" , dimension )
        J_SERIALIZE_MAP_OPT( "joints"    , joints    )
        J_SERIALIZE_MAP_OPT( "tcp_pose"  , tcpPose   )
    J_SERIALIZE_END
};

//------------------------ Функции json-сериализации -------------------------

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

template<typename This, typename Packer>
Packer& CobotPlan::jserialize(const This* ct, Packer& p)
{
    This* t = const_cast<This*>(ct);

    p.startObject();

    J_SERIALIZE_MAP_ITEM( "identity"  , identity )
    J_SERIALIZE_MAP_OPT ( "descript"  , descript )
    J_SERIALIZE_MAP_OPT ( "dynamic"   , dynamic  )
    J_SERIALIZE_MAP_OPT ( "power_off" , powerOff )

    if (p.isWriter())
    {
        QList<ActionSerialize> serializeActions;
        for (CobotAction* action : t->actions)
        {
            ActionSerialize serialize;
            if (CobotSleepAction* act = dynamic_cast<CobotSleepAction*>(action))
            {
                serialize.type = act->type();
                serialize.data = act->toJson();
                serializeActions.append(serialize);
            }
            else if (CobotMoveJointAction* act = dynamic_cast<CobotMoveJointAction*>(action))
            {
                serialize.type = act->type();
                serialize.data = act->toJson();
                serializeActions.append(serialize);
            }
            else if (CobotMovePoseAction* act = dynamic_cast<CobotMovePoseAction*>(action))
            {
                serialize.type = act->type();
                serialize.data = act->toJson();
                serializeActions.append(serialize);
            }
            else if (CobotMoveLineAction* act = dynamic_cast<CobotMoveLineAction*>(action))
            {
                serialize.type = act->type();
                serialize.data = act->toJson();
                serializeActions.append(serialize);
            }
            // else if (CobotMovePathAction* act = dynamic_cast<CobotMovePathAction*>(action))
            // {
            // }
            else if (CobotUserCoordAction* act = dynamic_cast<CobotUserCoordAction*>(action))
            {
                serialize.type = act->type();
                serialize.data = act->toJson();
                serializeActions.append(serialize);
            }
            else if (CobotTcpOffsetAction* act = dynamic_cast<CobotTcpOffsetAction*>(action))
            {
                serialize.type = act->type();
                serialize.data = act->toJson();
                serializeActions.append(serialize);
            }
        }
        p.member("actions") & serializeActions;
    }

    if (p.isReader())
    {
        QList<ActionSerialize> serializeActions;
        p.member("actions", true /*optional*/) & serializeActions;

        for (const ActionSerialize& serialize : serializeActions)
        {
            if (CobotAction::Type::Sleep == serialize.type)
            {
                CobotSleepAction* act = new CobotSleepAction;
                act->fromJson(serialize.data);
                t->actions.add(act);
            }
            else if (CobotAction::Type::MoveJoint == serialize.type)
            {
                CobotMoveJointAction* act = new CobotMoveJointAction;
                act->fromJson(serialize.data);
                t->actions.add(act);
            }
            else if (CobotAction::Type::MovePose == serialize.type)
            {
                CobotMovePoseAction* act = new CobotMovePoseAction;
                act->fromJson(serialize.data);
                t->actions.add(act);
            }
            else if (CobotAction::Type::MoveLine == serialize.type)
            {
                CobotMoveLineAction* act = new CobotMoveLineAction;
                act->fromJson(serialize.data);
                t->actions.add(act);
            }
            // else if (CobotAction::Type::MovePath == serialize.type)
            // {
            // }
            else if (CobotAction::Type::UserCoord == serialize.type)
            {
                CobotUserCoordAction* act = new CobotUserCoordAction;
                act->fromJson(serialize.data);
                t->actions.add(act);
            }
            else if (CobotAction::Type::TcpOffset == serialize.type)
            {
                CobotTcpOffsetAction* act = new CobotTcpOffsetAction;
                act->fromJson(serialize.data);
                t->actions.add(act);
            }
        }
    }
    return p.endObject();
}

} // namespace data
} // namespace pproto

namespace alog {

Line& operator<< (Line&, const pproto::CobotActionState&);
Line& operator<< (Line&, const pproto::CobotActionPhase&);

} // namespace alog

