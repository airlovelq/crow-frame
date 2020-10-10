#include "controller.h"
#include "database.h"

CController::CController()
    :m_db(std::make_unique<CDatabase>())
{

}

CController::~CController()
{

}

void CController::Enter()
{
    m_db->Begin();
}

void CController::Exit(bool commit)
{
    commit?m_db->Commit():m_db->Rollback();
}

int CController::test(int t)
{
    return 9;
}
