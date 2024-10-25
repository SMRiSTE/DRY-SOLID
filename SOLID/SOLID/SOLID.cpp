//Принцип открытости/закрытости: функция saveTo
//Принцип единственной ответственности: класс Data
//Принцип разделения интерфейса: Printable
#include <fstream>
#include <string>
#include <stdexcept>

class IPrintable
{
public:
    virtual ~IPrintable() = default;

    virtual std::string print() const = 0;
};

class Data : public IPrintable
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };

    Data(std::string data, Format format)
        : data_(std::move(data)), format_(format) {}

    std::string print() const override
    {
        switch (format_)
        {
        case Format::kText:
            return data_;
        case Format::kHTML:
            return "<html>" + data_ + "</html>";
        case Format::kJSON:
            return "{ \"data\": \"" + data_ + "\"}";
        default:
            throw std::runtime_error("Invalid format!");
        }
    }

private:
    std::string data_;
    Format format_;
};

class ISaver
{
public:
    virtual ~ISaver() = default;
    virtual void save(std::ofstream& file, const IPrintable& printable) = 0;
};

class TextSaver : public ISaver
{
public:
    void save(std::ofstream& file, const IPrintable& printable) override
    {
        file << printable.print();
    }
};

class HTMLSaver : public ISaver
{
public:
    void save(std::ofstream& file, const IPrintable& printable) override
    {
        file << printable.print();
    }
};

class JSONSaver : public ISaver
{
public:
    void save(std::ofstream& file, const IPrintable& printable) override
    {
        file << printable.print();
    }
};

void saveData(std::ofstream& file, const IPrintable& printable, ISaver& saver)
{
    saver.save(file, printable);
}
