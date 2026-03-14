#pragma once
#include <cstdint>
#include <istream>
#include <ostream>
#include <optional>

class Marshaller
{
public:
    std::optional<uint8_t> ReadU8(std::istream& msg);
    std::optional<uint16_t> ReadU16(std::istream& msg);
    std::optional<uint32_t> ReadU32(std::istream& msg);
    std::optional<uint64_t> ReadU64(std::istream& msg);
    std::optional<float_t> ReadFloat(std::istream& msg);
    std::optional<double_t> ReadDouble(std::istream& msg);
    std::optional<std::string> ReadString(std::istream& msg);
    bool ReadCharArray(std::istream& msg, char* charArray, size_t length);

    bool WriteU8(std::ostream& msg, uint8_t val);
    bool WriteU16(std::ostream& msg, uint16_t val);
    bool WriteU32(std::ostream& msg, uint32_t val);
    bool WriteU64(std::ostream& msg, uint64_t val);
    bool WriteFloat(std::ostream& msg, float_t val);
    bool WriteDouble(std::ostream& msg, double_t val);
    bool WriteString(std::ostream& msg, std::string val);
    bool WriteCharArray(std::ostream& msg, char* charArray, size_t length);
};
