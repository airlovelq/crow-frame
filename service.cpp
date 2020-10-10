#include "crow.h"
#include "service.h"
#include "controller.h"
#include "database.h"
#include "error_code.h"
#include "cors.h"
#include "error_handler.h"
#include "route.h"
#include "token.h"
#include "response.h"

static void test(const crow::request& req, crow::response& res, const Poco::JSON::Object& token) {
//    throw "opp";
//    throw CError(5000);
    Poco::JSON::Object jres;
    jres.set("test", 9);
    res.write(responseSuccess(jres));
//    res.write(token.get("user_id").toString());
    res.end();
}

static void test2(const crow::request& req, crow::response& res, crow::json::rvalue& jval) {
//    throw "opp";
//    CController con;
    auto ret = RunOperation(CController(), &CController::test, 10);
    throw CError(5000);
    res.write("oop");
//    res.write(token.get("user_id").toString());
    res.end();
}

static void test3(const crow::request& req, crow::response& res)
{
    throw CError(5000);
}

void startService()
{
    CDatabase::Connect(POSTGRESQL, "sugar2", "postgres", "postgres", "192.168.100.103", "10202");
    crow::App<CorsMiddleware> app;
//    auto f = CROW_JSON_PARSE_FUNC(test2);
//    CROW_TOEKN_CHECK_FUNC(f);
//    CROW_ROUTE(app, "/test").methods(crow::HTTPMethod::GET)
//            (CROW_JSON_PARSE_FUNC(test2));
//    CROW_ROUTE(app, "/test2").methods(crow::HTTPMethod::GET)
//            (CROW_ERROR_HANDLER(test3));
    CROW_ROUTE_CUSTOM(app, "/test3", crow::HTTPMethod::GET, CROW_TOEKN_CHECK_HANDLER(test));
    app.port(8788).concurrency(3).run();
}
