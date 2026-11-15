#ifndef REQUEST_LINE_PARSER_HH
#define REQUEST_LINE_PARSER_HH

#include <string_view>
#include "../include/HttpMessage.hh"
#include <optional>


namespace HttpParser {
    std::optional<HttpRequestLine> parse_request_line (std::string_view data);
};

#endif