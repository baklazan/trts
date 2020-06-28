#include <command.h>

void Command::Write(std::shared_ptr <FormattedWriter> writer) const {
    writer->Comment("ability_id=");
    writer->Int(ability_id_);
    writer->MinorSeparator();
    WriteInternals(writer);
}

Command::Command(AbilityIDType ability_id) : ability_id_(ability_id) {}
