#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include <functional>
#include "error_code.h"
#include "response.h"
#include "crow.h"
template <typename T>
struct crow_error_handler;

template <typename Ret, typename...Args>
struct crow_error_handler<Ret(const crow::request&, crow::response&, Args...)>
{
    using FUNC_TYPE = Ret(const crow::request&, crow::response&, Args...);
    using TRANS_FUNC_TYPE = std::function<Ret(const crow::request&, crow::response&, Args...)>;
    static TRANS_FUNC_TYPE generate(FUNC_TYPE f)
    {
        return [f](const crow::request& req, crow::response& res, Args...args) {
            try {
                return f(req,res,args...);
            } catch (CError &e) {
                res.code = 500;
                res.write(responseError(e.getCode(),e.getMsg(),std::string()));
                res.end();
            } catch (std::exception &e) {
                res.code = 500;
                res.write(responseError(500, "Internal Error", std::string(e.what())));
                res.end();
            }
        };
    }
};

template <typename Ret, typename...Args>
struct crow_error_handler<std::function<Ret(const crow::request&, crow::response&, Args...)>>
{
    using FUNC_TYPE = std::function<Ret(const crow::request&, crow::response&, Args...)>;
    using TRANS_FUNC_TYPE = std::function<Ret(const crow::request&, crow::response&, Args...)>;
    static TRANS_FUNC_TYPE generate(FUNC_TYPE f)
    {
        return [f](const crow::request& req, crow::response& res, Args...args) {
            try {
                return f(req,res,args...);
            } catch (CError &e) {
                res.code = 500;
                res.write(responseError(e.getCode(),e.getMsg(),std::string()));
                res.end();
            } catch (std::exception &e) {
                res.code = 500;
                res.write(responseError(500, "Internal Error", std::string(e.what())));
                res.end();
            }
        };
    }
};

template <typename Ret, typename...Args>
struct crow_error_handler<Ret(const crow::request&, Args...)>
{
    using FUNC_TYPE = Ret(const crow::request&, Args...);
    using TRANS_FUNC_TYPE = std::function<Ret(const crow::request&, Args...)>;
    static TRANS_FUNC_TYPE generate(FUNC_TYPE f)
    {
        return [f](const crow::request& req, Args...args) {
            try {
                return f(req,args...);
            } catch (CError &e) {
                return crow::response(500, responseError(e.getCode(),e.getMsg(),std::string()));
            } catch (std::exception &e) {
                return crow::response(500, responseError(500, "Internal Error", std::string(e.what())));
            }
        };
    }
};

template <typename Ret, typename...Args>
struct crow_error_handler<std::function<Ret(const crow::request&, Args...)>>
{
    using FUNC_TYPE = std::function<Ret(const crow::request&, Args...)>;
    using TRANS_FUNC_TYPE = std::function<Ret(const crow::request&, Args...)>;
    static TRANS_FUNC_TYPE generate(FUNC_TYPE f)
    {
        return [f](const crow::request& req, Args...args) {
            try {
                return f(req,args...);
            } catch (CError &e) {
                return crow::response(500, responseError(e.getCode(),e.getMsg(),std::string()));
            } catch (std::exception &e) {
                return crow::response(500, responseError(500, "Internal Error", std::string(e.what())));
            }
        };
    }
};

#define CROW_ERROR_HANDLER(func) crow_error_handler<decltype(func)>::generate(func)
#endif // ERROR_HANDLER_H
