#ifndef ERROR_CODE_H
#define ERROR_CODE_H
#include <map>
class CError {
public:
    CError(int code);
private:
    int m_code = 0;
public:
    int getCode() const;
    const std::string& getMsg() const;
public:
    static std::map<int, std::string> m_errors;
};


#endif // ERROR_CODE_H
