#ifndef TTask_H
# define TTask_H

# include <memory>

template<typename _ID_TYPE, typename _NAME_TYPE, typename _DESCRIPTION_TYPE>
class TTask {
public:
    typedef _ID_TYPE IdType;
    typedef _NAME_TYPE NameType;
    typedef _DESCRIPTION_TYPE DescriptionType;
    typedef TTask<_ID_TYPE, _NAME_TYPE, _DESCRIPTION_TYPE> Type;
    typedef std::unique_ptr<Task> TaskPtr;

private:
    TTask() {}

public:
    TTask(const IdType & id, const NameType & name, const DescriptionType & description): id(id), name(name), description(description) { }

    TTask(TTask const &other) {
        id = other.id;
        name = other.name;
        description = other.description;
    }

    TTask &operator=(TTask const &other) {
        id = other.id;
        name = other.name;
        description = other.description;
        return *this;
    }

    virtual ~TTask() {}

    const IdType & getId() const {
        return this->id;
    }

    void setId(const IdType & id) {
        this->id = id;
    }

    const NameType & getName() const {
        return this->name;
    }

    void setName(const NameType & name) {
        this->name = name;
    }

private:
    IdType id;
    NameType name;
    DescriptionType description;
};

#endif // TTask_H
