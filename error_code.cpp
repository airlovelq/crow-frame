#include "error_code.h"

std::map<int, std::string> CError::m_errors = {
    {0,"success"},
    {5000, "Authentic Error"},
};

CError::CError(int code)
    :m_code(code)
{

}

int CError::getCode() const
{
    return m_code;
}

const std::string& CError::getMsg() const
{
    return m_errors[m_code];
}
