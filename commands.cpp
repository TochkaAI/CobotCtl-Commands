#include "commands.h"
#include "pproto/commands/pool.h"

namespace pproto {
namespace command {

#define REGISTRY_COMMAND_SINGLPROC(COMMAND, UUID) \
    const QUuidEx COMMAND = command::Pool::Registry{UUID, #COMMAND, false};

#define REGISTRY_COMMAND_MULTIPROC(COMMAND, UUID) \
    const QUuidEx COMMAND = command::Pool::Registry{UUID, #COMMAND, true};

REGISTRY_COMMAND_SINGLPROC(ConfigChanged,   "686660f5-bdda-49b7-9484-e16bf907ff7f")

#undef REGISTRY_COMMAND_SINGLPROC
#undef REGISTRY_COMMAND_MULTIPROC

} // namespace command

namespace data {

// void ConfigChanged::toRaw(bserial::DataStream& stream) const
// {
//     B_SERIALIZE_V1
//     stream << file;
//     stream << phase;
//     B_SERIALIZE_RETURN
// }
//
// void ConfigChanged::fromRaw(const bserial::RawVector& vect)
// {
//     B_DESERIALIZE_V1(vect)
//     stream >> file;
//     stream >> phase;
//     B_DESERIALIZE_END
// }

} // namespace data
} // namespace pproto
