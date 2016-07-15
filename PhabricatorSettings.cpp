#include "PhabricatorSettings.h"

Settings::Settings()
{

}

QString Settings::getUserPhid() const
{
    return m_userPhid;
}

void Settings::setUserPhid(const QString &userPhid)
{
    m_userPhid = userPhid;
}
