#include "token.h"
#include "error_code.h"

int checkToken(const crow::request &req, crow::response &res, Poco::JSON::Object &token) {
    auto auth = req.get_header_value("Authorization");
    if (auth.length() == 0) {
        throw CError(5000);
        res.write("No Authorization");
        return -1;
    }
    std::vector<std::string> vs;
    splitString(auth, vs, " ");
    if (vs.size()!=2) {
        throw CError(5000);
        res.write("Authorization Field Error");
        return -1;
    }
    if (vs[0].compare("Bearer")!=0) {
        throw CError(5000);
        res.write("Authorization Field Error");
        return -1;
    }
    try {
        Poco::JWT::Signer signer(TOKEN_KEY);
        token = signer.verify(vs[1]).payload();
    } catch (...) {
        throw CError(5000);
        res.write("Token Error");
        return -1;
    }
    return 0;
}
