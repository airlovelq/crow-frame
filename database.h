#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <memory>
#include <mutex>
#include <cstdlib>
#include "Poco/Data/SessionPool.h"

using namespace Poco::Data;
enum DB_TYPE {
    POSTGRESQL = 0,
    MYSQL = 1,
    SQLITE = 2,
};

class CDatabase
{
public:
    CDatabase();
    ~CDatabase();

public:
    static void Connect(DB_TYPE db_type, const std::string &sdb_name=std::getenv("DB_NAME"), const std::string &sdb_user=std::getenv("DB_USER"), const std::string &sdb_password=std::getenv("DB_PASSWORD"), const std::string &sdb_host=std::getenv("DB_HOST"), const std::string& sdb_port=std::getenv("DB_PORT"));
protected:
    static std::mutex m_mu;
    static std::unique_ptr<SessionPool> m_pool;
    Session m_sess;
//    std::unique_ptr<Session> m_sess;
public:
    void Begin();
    void Commit();
    void Rollback();
public:
    void test();
};
#endif // DATABASE_H
