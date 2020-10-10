#ifndef CORS_H
#define CORS_H
#include <string>
#include "crow.h"

struct CorsMiddleware
{
    CorsMiddleware()
    {

    }

//    void setMessage(std::string newMsg)
//    {
//        message = newMsg;
//    }

    struct context
    {
    };

    void before_handle(crow::request& req, crow::response& res, context& ctx)
    {
//        CROW_LOG_DEBUG << " - MESSAGE: " << message;
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "origin, x-requested-with, accept, access-control-allow-origin, authorization, content-type");
        res.set_header("Access-Control-Allow-Methods", "GET,POST,PUT,DELETE,PATCH,OPTIONS");
        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Expose-Headers", "Content-Length, Access-Control-Allow-Origin, Access-Control-Allow-Headers, Content-Type");
        if( req.method == crow::HTTPMethod::OPTIONS)
        {
            res.end();
        }
    }

    void after_handle(crow::request& req, crow::response& res, context& ctx)
    {
        // no-op
    }
};
#endif // CORS_H
