#ifndef TRTS_FORMATTED_READER_H
#define TRTS_FORMATTED_READER_H

#include <istream>

class FormattedReader {
protected:
    std::istream *in_;
    int block_depth_;
public:
    FormattedReader();
    virtual void Reset(std::istream *in);
    virtual int32_t Int() = 0;
    virtual int8_t Char() = 0;
    virtual double Double() = 0;
    virtual std::string Token() = 0;
    virtual std::string String() = 0;
    virtual void MinorSeparator() = 0;
    virtual void MajorSeparator() = 0;
    virtual void Comment(std::string str) = 0;
    virtual void EnterBlock();
    virtual void EscapeBlock();
};

class DebugReader : public FormattedReader {
private:
    bool line_start_;
    void ReadExactly(std::string str);
    void ReadIndent();
public:
    DebugReader();
    void Reset(std::istream *in) override;
    int32_t Int() override;
    int8_t Char() override;
    double Double() override;
    std::string Token() override;
    std::string String() override;
    void MinorSeparator() override;
    void MajorSeparator() override;
    void Comment(std::string str) override;
};

class BinaryReader : public FormattedReader {};

#endif
