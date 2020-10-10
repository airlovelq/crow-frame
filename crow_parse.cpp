#include "crow_parse_template.h"

int parse_multipart(const crow::request& req, FormData &form_data, FileData &file_data) {
    auto type = req.get_header_value("Content-type");
    if ( type.find("multipart/form-data") != type.npos ) {
        auto dpos = type.find("=");
        if ( dpos == type.npos )
        {
            return -1;
        }

        std::string boundary = type.substr(dpos+1);
        boundary.insert(0, "--");
        //boundary += "\r\n";
        auto period_pos1 = req.body.find(boundary);
        if ( period_pos1 == req.body.npos )
        {
            return -1;
        }
        auto period_pos2 = req.body.find(boundary, period_pos1+1);
        while ( period_pos2 != req.body.npos )
        {
            auto period_str = req.body.substr(period_pos1+boundary.length()+2, period_pos2-period_pos1-boundary.length()-2);
            auto period_title_pos_end = period_str.find("\r\n");
            auto period_title = period_str.substr(0, period_title_pos_end);
            auto name_pos1 = period_title.find("name=\"");
            auto name_pos2 = period_title.find("\"", name_pos1+6);
            auto name = period_title.substr(name_pos1+6, name_pos2-name_pos1-6);

            auto period_content_pos_end = period_str.length()-2;//find("\r\n", period_title_pos_end+4);
            auto period_content = period_str.substr(period_title_pos_end+4, period_content_pos_end-period_title_pos_end-4);
            auto size = period_content.size();
            if ( period_title.find("filename") != period_title.npos )
            {
                file_data[name] = period_content;
            }
            else {
                form_data[name] = period_content;
            }
            period_pos1 = period_pos2;
            period_pos2 = req.body.find(boundary, period_pos1+1);
        }


        return 0;
    } else {
        return -1;
    }
}
