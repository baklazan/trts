#include <formatted_writer.h>

FormattedWriter::FormattedWriter() = default;


void FormattedWriter::Reset(std::ostream *out) {
    out_ = out;
    block_depth_ = 0;
}

void FormattedWriter::EnterBlock() {
    block_depth_ ++;
}

void FormattedWriter::EscapeBlock() {
    block_depth_ --;
}

DebugWriter::DebugWriter() = default;

void DebugWriter::Reset(std::ostream *out) {
    FormattedWriter::Reset(out);
    line_start_ = true;
}

void DebugWriter::Int(int32_t x) {
    WriteIndent();
    (*out_) << x;
}

void DebugWriter::Char(int8_t x) {
    WriteIndent();
    out_->put(x);
}

void DebugWriter::Double(double x) {
    WriteIndent();
    (*out_) << x;
}

void DebugWriter::Token(std::string str) {
    WriteIndent();
    (*out_) << str;
}

void DebugWriter::String(std::string str) {
    WriteIndent();
    (*out_) << str << "\n";
    line_start_ = true;
}

void DebugWriter::MinorSeparator() {
    WriteIndent();
    out_->put(' ');
}

void DebugWriter::MajorSeparator() {
    WriteIndent();
    out_->put('\n');
    line_start_ = true;
}

void DebugWriter::Comment(std::string str) {
    WriteIndent();
    (*out_) << str;
}

void DebugWriter::WriteIndent() {
    if (line_start_) {
        (*out_) << std::string(block_depth_ * 2, ' ');
        line_start_ = false;
    }
}

