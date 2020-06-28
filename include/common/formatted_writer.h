#ifndef TRTS_FORMATTED_WRITER_H
#define TRTS_FORMATTED_WRITER_H

#include <ostream>

class FormattedWriter {
protected:
    std::ostream *out_;
    int block_depth_;
public:
    FormattedWriter();
    virtual void Reset(std::ostream *out);
    virtual void Int(int32_t x) = 0;
    virtual void Char(int8_t x) = 0;
    virtual void Double(double x) = 0;
    virtual void Token(std::string str) = 0;
    virtual void String(std::string str) = 0;
    virtual void MinorSeparator() = 0;
    virtual void MajorSeparator() = 0;
    virtual void Comment(std::string str) = 0;
    virtual void EnterBlock();
    virtual void EscapeBlock();
};

class DebugWriter : public FormattedWriter {
private:
    bool line_start_;
    void WriteIndent();
public:
    DebugWriter();
    void Reset(std::ostream *out) override;
    void Int(int32_t x) override;
    void Char(int8_t x) override;
    void Double(double x) override;
    void Token(std::string str) override;
    void String(std::string str) override;
    void MinorSeparator() override;
    void MajorSeparator() override;
    void Comment(std::string str) override;
};

class BinaryWriter : public FormattedWriter {};

#endif
