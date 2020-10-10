#ifndef CROW_PARSE_TEMPLATE_H
#define CROW_PARSE_TEMPLATE_H

#include <string>
#include "crow.h"
#include "Poco/JSON/Parser.h"

template<typename FUNC> struct crow_json_parse;
template<typename Ret, typename...Args>
struct crow_json_parse<Ret(const crow::request&, crow::json::rvalue&, Args...)>
{
public:
    using FUNC_TYPE = Ret(const crow::request&, crow::json::rvalue&, Args...);
    using TRANS_FUNC_TYPE = std::function<Ret(const crow::request&, crow::response&, Args...)>;
    static TRANS_FUNC_TYPE generate(FUNC_TYPE f)
    {
        return [f](const crow::request &req, Args...args) {
            auto type = req.get_header_value("Content-type");
            if ( type.compare("application/json") == 0 ) {
                auto json_value = crow::json::load(req.body);
                return f(req, json_value, args...);
            } else {
                return crow::response("Not application/json!");
            }
        };
    }
};

template<typename Ret, typename...Args>
struct crow_json_parse<std::function<Ret(const crow::request&, crow::json::rvalue&, Args...)>>
{
public:
    using FUNC_TYPE = std::function<Ret(const crow::request&, crow::json::rvalue&, Args...)>;
    using TRANS_FUNC_TYPE = std::function<Ret(const crow::request&, crow::response&, Args...)>;
    static TRANS_FUNC_TYPE generate(FUNC_TYPE f)
    {
        return [f](const crow::request &req, Args...args) {
            auto type = req.get_header_value("Content-type");
            if ( type.compare("application/json") == 0 ) {
                auto json_value = crow::json::load(req.body);
                return f(req, json_value, args...);
            } else {
                return crow::response("Not application/json!");
            }
        };
    }
};

template<typename Ret, typename...Args>
struct crow_json_parse<std::function<Ret(const crow::request&, crow::response&, crow::json::rvalue&, Args...)>>
{
public:
    using FUNC_TYPE = std::function<Ret(const crow::request&, crow::response&, crow::json::rvalue&, Args...)>;
    using TRANS_FUNC_TYPE = std::function<Ret(const crow::request&, crow::response&, Args...)>;
    static TRANS_FUNC_TYPE generate(FUNC_TYPE f)
    {
        return [f](const crow::request &req, crow::response& res, Args...args) {
            auto type = req.get_header_value("Content-type");
            if ( type.compare("application/json") == 0 ) {
                auto json_value = crow::json::load(req.body);
                return f(req, res, json_value, args...);
            } else {
                res.write("Not application/json!");
                res.end();
            }
        };
    }
};

template<typename Ret, typename...Args>
struct crow_json_parse<Ret(const crow::request&, crow::response&, crow::json::rvalue&, Args...)>
{
public:
    using FUNC_TYPE = Ret(const crow::request&, crow::response&, crow::json::rvalue&, Args...);
    using TRANS_FUNC_TYPE = std::function<Ret(const crow::request&, crow::response&, Args...)>;
    static TRANS_FUNC_TYPE generate(FUNC_TYPE f)
    {
        return [f](const crow::request &req, crow::response& res, Args...args) {
            auto type = req.get_header_value("Content-type");
            if ( type.compare("application/json") == 0 ) {
                auto json_value = crow::json::load(req.body);
                return f(req, res, json_value, args...);
            } else {
                res.write("Not application/json!");
                res.end();
            }
        };
    }
};

using FormData = std::map<std::string, std::string>;
using FileData = std::map<std::string, std::string>;
int parse_multipart(const crow::request& req, FormData &form_data, FileData &file_data);


template<typename FUNC> struct crow_multipart_parse;
template<typename Ret, typename...Args>
struct crow_multipart_parse<Ret(const FormData&, const FileData&, const crow::request&, Args...)>
{
public:
    static std::function<Ret(const crow::request&, Args...)> generate(std::function<Ret(const FormData&, const FileData&, const crow::request&, Args...)> f)
    {
        return [f](const crow::request &req, Args...args) {
            FormData form_data;
            FileData file_data;
            if ( parse_multipart(req, form_data, file_data) == 0 )
            {
                return f(form_data, file_data, req, args...);
            } else {
                return crow::response("Not multipart/form-data!");
            }
        };
    }
};

template<typename Ret, typename...Args>
struct crow_multipart_parse<std::function<Ret(const FormData&, const FileData&, const crow::request&, crow::response&, Args...)>>
{
public:
    static std::function<Ret(const crow::request&, crow::response&, Args...)> generate(std::function<Ret(const FormData&, const FileData&, const crow::request&, crow::response&, Args...)> f)
    {
        return [f](const crow::request &req, crow::response& res,Args...args) {
            FormData form_data;
            FileData file_data;
            if ( parse_multipart(req, form_data, file_data) == 0 )
            {
                return f(form_data, file_data, req, res, args...);
            } else {
                res.write("Not multipart/form-data!");
                res.end();
            }
        };
    }
};

//template<typename Ret, typename...Args>
//struct crow_multipart_parse<Ret(const FormData&, const FileData&, const crow::request&, crow::response&, Args...)>
//{
//public:
//    static std::function<Ret(const crow::request&, crow::response&, Args...)> generate(std::function<Ret(const FormData&, const FileData&, const crow::request&, crow::response&, Args...)> f)
//    {
//        return [f](const crow::request &req, crow::response& res,Args...args) {
//            FormData form_data;
//            FileData file_data;
//            if ( parse_multipart(req, form_data, file_data) == 0 )
//            {
//                return f(form_data, file_data, req, res, args...);
//            } else {
//                res.write("Not multipart/form-data!");
//                res.end();
//            }
//        };
//    }
//};

#define CROW_JSON_PARSE_FUNC(func) crow_json_parse<decltype(func)>::generate(func)
#define CROW_MULTIPART_PARSE_FUNC(func) crow_multipart_parse<decltype(func)>::generate(func)

#endif // CROW_PARSE_TEMPLATE_H
