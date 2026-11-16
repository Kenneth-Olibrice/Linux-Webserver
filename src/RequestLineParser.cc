#include "../include/RequestLineParser.hh"
#include "../include/HttpMessage.hh"

#include <optional>
#include <stdexcept> // TODO: Remove once the below function is implemented

using namespace std;


std::optional<HttpRequestLine> HttpParser::parse_request_line (string_view data) {
    auto method_end = data.find (" ");

    // Parse the method first. If it is invalid or not present, return nullopt.
    optional<HttpMethod> method = HttpMessage::deserialize_method (string_view (data.begin (), method_end));
    if (!method.has_value ())
      return nullopt;

    string_view uri_ver_substr = string_view ();
}