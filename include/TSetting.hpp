#ifndef TSETTING_HPP
# define TSETTING_HPP

# include <string>

namespace Settings {
    typedef enum {
        Boolean = 0,
        Integer = 1,
        StdString = 2,
        QString = 3,
    } SupportedValueType;
}

template<typename _VALUE_TYPE, Settings::SupportedValueType _VALUE_ENUM>
class TSetting {
public:
    typedef std::string KeyType;
    typedef std::string DescriptionType;
    typedef _VALUE_TYPE ValueType;

public:
    TSetting(const KeyType & key, const ValueType & value): key(key), value(value) {}
    virtual ~TSetting() {}

    const KeyType &getKey() const {
        return this->key;
    }

    const ValueType & getValue() const {
        return this->value;
    }

    void setKey(const KeyType & key) {
        this->key = key;
    }

    void setValue(const ValueType & value) {
        this->value = value;
    }

private:
    KeyType key;
    ValueType value;
    Settings::SupportedValueType valueType = _VALUE_ENUM;
    DescriptionType description;
};

#endif // TSETTING_HPP

