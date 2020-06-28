#include <formatted_reader.h>
#include <iostream>

FormattedReader::FormattedReader() = default;

void FormattedReader::Reset(std::istream *in) {
    in_ = in;
    block_depth_ = 0;
}

void FormattedReader::EnterBlock() {
    block_depth_++;
}

void FormattedReader::EscapeBlock() {
    block_depth_--;
}

DebugReader::DebugReader() = default;

void DebugReader::Reset(std::istream *in) {
    FormattedReader::Reset(in);
    line_start_ = true;
}

int32_t DebugReader::Int() {
    ReadIndent();
    if (!in_->good()) std::cerr << "bad stream Int start :(" << std::endl;
    int32_t result;
    (*in_) >> result;
    if (in_->eof()) std::cerr << "EOF Int end :(" << std::endl;
    if (!in_->good()) std::cerr << "bad stream Int end :(" << std::endl;
    return result;
}

int8_t DebugReader::Char() {
    ReadIndent();
    return in_->get();
}

double DebugReader::Double() {
    ReadIndent();
    double result;
    (*in_) >> result;
    return result;
}

std::string DebugReader::Token() {
    ReadIndent();
    std::string result;
    (*in_) >> result;
    return result;
}

std::string DebugReader::String() {
    ReadIndent();
    std::string result;
    getline(*in_, result);
    line_start_ = true;
    return result;
}

void DebugReader::MinorSeparator() {
    ReadIndent();
    ReadExactly(" ");
}

void DebugReader::MajorSeparator() {
    ReadIndent();
    ReadExactly("\n");
    line_start_ = true;
}

void DebugReader::Comment(std::string str) {
    ReadIndent();
    ReadExactly(str);
}


void DebugReader::ReadExactly(std::string str) {
    for (int i = 0; i < str.size(); i++) {
        char c = in_->get();
        if (!in_->good()) std::cerr << "bad stream :(" << std::endl;
        if (c != str[i]) {
        std::cerr << "expected " << str[i] << " (as " << i
                  << "-th character of \"" << str << "\"), got " << c
                  << std::endl;
        }
    }
}

void DebugReader::ReadIndent() {
    if (line_start_) {
        ReadExactly(std::string(block_depth_ * 2, ' '));
        line_start_ = false;
    }
}




