#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "Poco/JWT/Token.h"
#include "Poco/JWT/Signer.h"
#include "crow.h"
#include "define.h"
#include "public_function.h"

int checkToken(const crow::request &req, crow::response &res, Poco::JSON::Object &token);

template<typename FUNC> struct crow_token_check;
template<typename Ret, typename...Args>
struct crow_token_check<Ret(const crow::request&, const Poco::JSON::Object&,  Args...)>
{
public:
    using FUNC_TYPE = Ret(const crow::request&, const Poco::JSON::Object&,  Args...);
    using TRANS_FUNC_TYPE = std::function<Ret(const crow::request&, Args...)>;
    static TRANS_FUNC_TYPE generate(FUNC_TYPE f)
    {
        return [f](const crow::request &req, Args...args) {
            crow::response res;
            Poco::JSON::Object token;
            if (0 == checkToken(req, res, token)) {
                return f(req, token, args...);
            } else {
                return res;
            }
        };
    }
};

template<typename Ret, typename...Args>
struct crow_token_check<std::function<Ret(const crow::request&, const Poco::JSON::Object&,  Args...)>>
{
public:
    using FUNC_TYPE = std::function<Ret(const crow::request&, const Poco::JSON::Object&,  Args...)>;
    using TRANS_FUNC_TYPE = std::function<Ret(const crow::request&, Args...)>;
    static TRANS_FUNC_TYPE generate(FUNC_TYPE f)
    {
        return [f](const crow::request &req, Args...args) {
            crow::response res;
            Poco::JSON::Object token;
            if (0 == checkToken(req, res, token)) {
                return f(req, token, args...);
            } else {
                return res;
            }
        };
    }
};

template<typename Ret, typename...Args>
struct crow_token_check<std::function<Ret(const crow::request&, crow::response&, const Poco::JSON::Object&,  Args...)>>
{
public:
    using FUNC_TYPE = std::function<Ret(const crow::request&, crow::response&, const Poco::JSON::Object&,  Args...)>;
    using TRANS_FUNC_TYPE = std::function<Ret(const crow::request&, crow::response&, Args...)>;
    static TRANS_FUNC_TYPE generate(FUNC_TYPE f)
    {
        return [f](const crow::request &req, crow::response &res, Args...args) {
            Poco::JSON::Object token;
            if (0 == checkToken(req, res, token)){
                return f(req, res, token, args...);
            } else {
                res.end();
            }
        };
    }
};

template<typename Ret, typename...Args>
struct crow_token_check<Ret(const crow::request&, crow::response&, const Poco::JSON::Object&,  Args...)>
{
public:
    using FUNC_TYPE = Ret(const crow::request&, crow::response&, const Poco::JSON::Object&,  Args...);
    using TRANS_FUNC_TYPE = std::function<Ret(const crow::request&, crow::response&, Args...)>;
    static TRANS_FUNC_TYPE generate(FUNC_TYPE f)
    {
        return [f](const crow::request &req, crow::response &res, Args...args) {
            Poco::JSON::Object token;
            if (0 == checkToken(req, res, token)){
                return f(req, res, token, args...);
            } else {
                res.end();
            }
        };
    }
};
#define CROW_TOEKN_CHECK_HANDLER(func) crow_token_check<decltype(func)>::generate(func)
#endif // TOKEN_H
