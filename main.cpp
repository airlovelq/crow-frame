#include <iostream>
#include "token.h"
#include "crow.h"
#include "Poco/JWT/Token.h"

#include "crow_parse_template.h"
#include "token.h"
#include "database.h"
#include "service.h"
using namespace std;

template <typename T>
void tt(T&& b) {
    b = 3;
}

void jj(int &&j) {
    j = 0;
}
void jj(int &j) {
    j=0;
}
int main()
{
    int &&a = 1;
    jj(a);
//    CDatabase db(CDatabase::POSTGRESQL, "sugar2", "postgres", "postgres", "192.168.100.103", "10202");
//    db.test();
    startService();

//    parseToken("eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VyX2lkIjoiN2E2NTY2YTMtOWI3OS00ZTFmLWEzMTgtZjUwMDFmNmFmYWE3IiwidXNlcl90eXBlIjoiTU9ERUxfREVWRUxPUEVSIiwiZXhwIjoxNjAxNDAwNzc2fQ.DEEkN9fWksBDdDq9TwnPau-Z7ljGtlKgCUPB7pwVAwU");
    cout << "Hello World!" << endl;
    return 0;
}
