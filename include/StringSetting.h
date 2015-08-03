#ifndef STRINGSETTING_H
# define STRINGSETTING_H

# include "TSetting.hpp"

namespace Settings {
    typedef TSetting<std::string, Settings::SupportedValueType::StdString> StringSetting;
}

#endif // STRINGSETTING_H
