#ifndef ROUTE_H
#define ROUTE_H
#include "error_handler.h"
#define CROW_ROUTE_CUSTOM(app, route_path, method, func) CROW_ROUTE(app, route_path).methods(method)(CROW_ERROR_HANDLER(func))
#endif // ROUTE_H
