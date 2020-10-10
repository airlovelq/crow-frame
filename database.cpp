#include "database.h"
#include "Poco/Data/PostgreSQL/Connector.h"
#include "Poco/Data/RecordSet.h"

std::unique_ptr<SessionPool> CDatabase::m_pool;

CDatabase::CDatabase()
    :m_sess(m_pool->get())
{

}

CDatabase::~CDatabase() {

}

void CDatabase::Connect(DB_TYPE db_type, const std::string &sdb_name, const std::string &sdb_user, const std::string &sdb_password, const std::string &sdb_host, const std::string& sdb_port) {
    std::string connector, connect_string;
    switch (db_type) {
    case POSTGRESQL:
        PostgreSQL::Connector::registerConnector();
        connector = PostgreSQL::Connector::KEY;
        connect_string = "hostaddr=";
        connect_string.append(sdb_host);
        connect_string.append(" ");

        connect_string.append("port=");
        connect_string.append(sdb_port);
        connect_string.append(" ");

        connect_string.append("user=");
        connect_string.append(sdb_user);
        connect_string.append(" ");

        connect_string.append("password=");
        connect_string.append(sdb_password);
        connect_string.append(" ");

        connect_string.append("dbname=");
        connect_string.append(sdb_name);
        connect_string.append(" ");
        break;
    default:
        break;
    }
    m_pool = std::make_unique<Poco::Data::SessionPool>(connector, connect_string);
}

void CDatabase::Begin()
{
    m_sess.begin();
}

void CDatabase::Commit()
{
    m_sess.commit();
}

void CDatabase::Rollback()
{
    m_sess.rollback();
}

void CDatabase::test() {
//    auto sess = m_pool->get();
    RecordSet rs(m_sess, "select * from user_platform");
    std::size_t cols = rs.columnCount();
    m_sess.rollback();
}
