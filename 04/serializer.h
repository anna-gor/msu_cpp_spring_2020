#include <vector>
#include <ostream>
#include <istream>
#include <iostream>
#include <ctype.h>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char separator = ' ';
    std::ostream& out_;

public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(const ArgsT&... args)
    {
        return process(args...);
    }

private:
    template <class Arg, class... ArgsT>
    Error process(Arg& val, ArgsT&&... args)
    {
        process(val);
        return process(std::forward<ArgsT>(args)...);
    }

    Error process(uint64_t val)
    {
        out_ << val << separator;
        return Error::NoError;
    }
    Error process(bool val)
    {
        if(val)
            out_ << "true" << separator;
        else
            out_ << "false" << separator;
        return Error::NoError;
    }
};

class Deserializer
{
    static constexpr char separator = ' ';
    std::istream& in_;

public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args)
    {
        return process(args...);
    }

private:
    template <class Arg, class... ArgsT>
    Error process(Arg& val, ArgsT&&... args)
    {
        if(process(val) != Error::NoError)
            return Error::CorruptedArchive;
        return process(std::forward<ArgsT>(args)...);
    }

    Error process(bool& val)
    {
        std::string text;
        in_ >> text;
        if (text == "true")
            val = true;
        else if (text == "false")
            val = false;
        else
            return Error::CorruptedArchive;
        return Error::NoError;
    }

    Error process(uint64_t& val)
    {
        std::string text;
        in_ >> text;
        if (text[0] == '-' || text.empty())  return Error::CorruptedArchive;
        try
        {
            val = std::stoi(text);
        }
        catch(std::invalid_argument)
        {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

};