#include "../include/RequestLineParser.hh"

#include <stdexcept> // TODO: Remove once the below function is implemented
using namespace std;


std::optional<HttpRequestLine> HttpParser::parse_request_line (string_view data) {
    auto method_end = data.find (" ");
    throw std::runtime_error ("Not implemented.");
}