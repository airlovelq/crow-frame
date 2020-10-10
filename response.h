#ifndef RESPONSE_H
#define RESPONSE_H
#include <string>
#include <functional>
#include "Poco/JSON/Object.h"

template <typename T>
std::string responseFormat(int success, int code, const std::string& msg, T&& data) {
    Poco::JSON::Object jres;
    jres.set("success", success);
    jres.set("code", code);
    jres.set("message", msg);
    jres.set("data", std::forward<T>(data));
    std::stringstream  jsnString;
    jres.stringify( jsnString, 3 );
    return jsnString.str();
}

template <typename T>
std::string responseSuccess(T&& data) {
    return responseFormat(1, 0, "success", std::forward<T>(data));
}

template <typename T>
std::string responseError(int code, const std::string& msg, T&& data) {
    return responseFormat(0, code, msg, std::forward<T>(data));
}


#endif // RESPONSE_H
