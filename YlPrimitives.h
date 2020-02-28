#ifndef YL_PRIMITIVES_H
#define YL_PRIMITIVES_H

#include <cstdint>
#include <string>
#include <ostream>

enum YlObjectType
{
    Nonprimitive,
    None,
    Integer,
    Bool
};

class YlObject
{
protected:
    YlObjectType m_type;

public:
    YlObject(YlObjectType t)
        : m_type(t) {}
    YlObject(YlObject&&)      = default;
    YlObject(const YlObject&) = default;
    virtual ~YlObject()       = default;
    virtual inline std::size_t id() const { return reinterpret_cast<std::size_t>(this); }
    virtual inline std::string to_string() const { return std::string("<Object ") + std::to_string(id()) + ">"; }

    virtual inline bool operator==(const YlObject& rhs) const { return id() == rhs.id(); }
    virtual inline bool operator!=(const YlObject& rhs) const { return !(*this == rhs); }

    virtual inline bool equals(const YlObject& rhs) const { return *this == rhs; }

    inline bool         type_equals(const YlObject& rhs) const { return m_type == rhs.m_type; }
    inline YlObjectType type() const { return m_type; }
};

class YlInteger : public YlObject
{
    int m_i;

public:
    YlInteger(int i)
        : YlObject(Integer)
        , m_i(i) {}

    virtual inline std::string to_string() const { return std::to_string(m_i); }
    virtual inline bool        equals(const YlObject& rhs) const {
        return type() == rhs.type() && m_i == dynamic_cast<const YlInteger&>(rhs).m_i;
    }
};

class YlBool : public YlObject
{
    bool m_b;

public:
    YlBool(bool b)
        : YlObject(Bool)
        , m_b(b) {}

    virtual inline std::string to_string() const { return m_b ? "true" : "false"; }
    virtual inline bool        equals(const YlObject& rhs) const {
        return type() == rhs.type() && m_b == dynamic_cast<const YlBool&>(rhs).m_b;
    }
};

class YlNone : public YlObject
{
public:
    YlNone()
        : YlObject(None) {}
    virtual std::size_t        id() const { return 0; }
    virtual inline std::string to_string() const { return "None"; }
    virtual inline bool        equals(const YlObject& rhs) const { return type() == rhs.type(); }
};

#endif // YL_PRIMITIVES_H
