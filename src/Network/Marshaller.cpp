#include "Marshaller.h"

std::optional<uint8_t> Marshaller::ReadU8(std::istream& msg)
{
    uint8_t val;
    if (msg.read(reinterpret_cast<char*>(&val), sizeof(val)).gcount() != sizeof(val))
    {
        return std::nullopt;
    }
    return val;
}

std::optional<uint16_t> Marshaller::ReadU16(std::istream& msg)
{
    uint16_t val;
    if (msg.read(reinterpret_cast<char*>(&val), sizeof(val)).gcount() != sizeof(val))
    {
        return std::nullopt;
    }
    return val;
}

std::optional<uint32_t> Marshaller::ReadU32(std::istream& msg)
{
    uint32_t val;
    if (msg.read(reinterpret_cast<char*>(&val), sizeof(val)).gcount() != sizeof(val))
    {
        return std::nullopt;
    }
    return val;
}

std::optional<uint64_t> Marshaller::ReadU64(std::istream& msg)
{
    uint64_t val;
    if (msg.read(reinterpret_cast<char*>(&val), sizeof(val)).gcount() != sizeof(val))
    {
        return std::nullopt;
    }
    return val;
}

std::optional<float_t> Marshaller::ReadFloat(std::istream& msg)
{
    float_t val;
    if (msg.read(reinterpret_cast<char*>(&val), sizeof(val)).gcount() != sizeof(val))
    {
        return std::nullopt;
    }
    return val;
}

std::optional<double_t> Marshaller::ReadDouble(std::istream& msg)
{
    double_t val;
    if (msg.read(reinterpret_cast<char*>(&val), sizeof(val)).gcount() != sizeof(val))
    {
        return std::nullopt;
    }
    return val;
}

std::optional<std::string> Marshaller::ReadString(std::istream& msg)
{
    std::string val;
    if (msg.read(reinterpret_cast<char*>(&val), sizeof(val)).gcount() != sizeof(val))
    {
        return std::nullopt;
    }
    return val;
}

bool Marshaller::ReadCharArray(std::istream& msg, char* charArray, size_t length)
{
    if (msg.read(charArray, length).gcount() != length)
    {
        return false;
    }
    return true;
}

bool WriteU8(std::ostream& msg, uint8_t val)
{
    if (msg.write(reinterpret_cast<char*>(&val), sizeof(val)).fail())
    {
        return false;
    }
    return true;
}

bool WriteU16(std::ostream& msg, uint16_t val)
{
    if (msg.write(reinterpret_cast<char*>(&val), sizeof(val)).fail())
    {
        return false;
    }
    return true;
}

bool WriteU32(std::ostream& msg, uint32_t val)
{
    if (msg.write(reinterpret_cast<char*>(&val), sizeof(val)).fail())
    {
        return false;
    }
    return true;
}

bool WriteU64(std::ostream& msg, uint64_t val)
{
    if (msg.write(reinterpret_cast<char*>(&val), sizeof(val)).fail())
    {
        return false;
    }
    return true;
}

bool WriteFloat(std::ostream& msg, float_t val)
{
    if (msg.write(reinterpret_cast<char*>(&val), sizeof(val)).fail())
    {
        return false;
    }
    return true;
}

bool WriteDouble(std::ostream& msg, double_t val)
{
    if (msg.write(reinterpret_cast<char*>(&val), sizeof(val)).fail())
    {
        return false;
    }
    return true;
}

bool WriteString(std::ostream& msg, std::string val)
{
    if (msg.write(reinterpret_cast<char*>(&val), sizeof(val)).fail())
    {
        return false;
    }
    return true;
}

bool WriteCharArray(std::ostream& msg, char* charArray, size_t length)
{
    if (msg.write(charArray, length).fail())
    {
        return false;
    }
    return true;
}
