#include <algorithm>
#include <charconv>

#include "../include/HttpRequest.hh"

using namespace std;


// TODO: remove, debug-only
#include <iostream>
#include <meta>

// `serialize()` turns an HttpMessage object and converts it to a string of bytes
// conforming to the message format defined in [RFC 9112]. 
//
// `serialize()` performs no correctness checking and can produce 
// a malformed HTTP message string. It is the responsibility of the caller
// to ensure that an HttpMessage object is correct before calling `serialize()`.
string HttpRequest::serialize () const {
    string retval {};


    string method = serialize_method (request_line_.method_);
    

    retval += method;
    retval += " ";

    retval += request_line_.uri_;
    retval += " ";

    retval += "HTTP/" + to_string (major_ver_) + "." + to_string (minor_ver_);
    retval += "\r\n"; // CRLF terminates the start line.

    for (auto &ele : headers_) {
      retval += ele.first;
      retval += ":";
      retval += ele.second;
      retval += "\r\n";
    }

    retval += "\r\n";
    retval += body_;

    return retval;
}

HttpRequest::~HttpRequest () {
    // Empty.
}

optional<HttpRequestLine> HttpRequest::deserialize_request_line (std::string_view raw) {
    size_t end_method_offset = raw.find (" ");
    if (end_method_offset == raw.npos)
        return nullopt;
    
    HttpRequestLine to_return;
    auto end_method_it = raw.begin () + end_method_offset;

    optional method = HttpMessage::deserialize_method (string_view (raw.begin (), end_method_it));
    if (!method.has_value ())
        return nullopt;

    to_return.method_ = method.value ();

    auto begin_uri_it = next (end_method_it);
    if (begin_uri_it == raw.end ())
        return nullopt;
    
    string_view uri (begin_uri_it, raw.end ());

    size_t end_uri_offset = uri.find (" ");
    if (end_uri_offset == uri.npos)
        return nullopt;
    
    auto end_uri_it = uri.begin () + end_uri_offset;

    to_return.uri_ = string (uri.begin (), end_uri_it);

    return to_return;
}

optional<HttpRequest> HttpRequest::deserialize (string_view raw) {
    HttpRequest to_return;
    const string clrf {"\r\n"};
    size_t start_line_end_index {raw.find ("\r\n")};
    if (start_line_end_index == raw.npos)
        return nullopt;
    
    optional<HttpRequestLine> request_line = HttpRequest::deserialize_request_line (string_view (raw.begin (), raw.begin () + start_line_end_index));
    if (!request_line.has_value ())
        return nullopt;
    
    cout << "Request uri: " << request_line.value ().uri_ << endl;

    // string_view headers_body {raw.begin () + start_line_end_index, raw.end ()};
    // cout << headers_body << endl;

    auto headers_begin = next (next (raw.begin () + start_line_end_index));
    if (headers_begin == raw.end ())
        return nullopt;

    string_view headers_body (headers_begin, raw.end ());
    // cout << headers_body;

    size_t end_headers_offset {raw.find ("\r\n\r\n")};
    if (end_headers_offset == headers_body.npos)
        return nullopt;

    auto end_headers_it = headers_body.begin () + end_headers_offset;
    auto current_headers_it = headers_body.begin ();

    cout << "test: " << *current_headers_it << endl;

    while (next (next (current_headers_it)) != end_headers_it) {
        size_t end_line {headers_body.find ("\r\n")};
        if (end_line == headers_body.npos)
            return nullopt;
        
        string_view current_line (current_headers_it, current_headers_it + end_line);
        size_t end_key = {current_line.find (":")};
        if (end_key == current_line.npos) {
            cout << "the value" << current_line << endl;
            return nullopt;
        }

        string key (current_line.begin (), current_line.begin () + end_key);
        string value (next (current_line.begin () + end_key), current_line.begin () + end_line);
        cout << "key: " << key << endl;
        cout << "value: " << value << endl;

        current_headers_it = current_line.begin () + end_line;

        to_return.set_header (key, value);

        current_headers_it = next (next (current_headers_it));

    }


    // For now, we will assume a content-length field is present.
    // TODO: Implement full semantics here, e.g. the case of transfer-encoding.
    cout << "blah" << endl;
    size_t content_length {};
    if (!to_return.headers_.contains ("content-length"))
        return nullopt;

    string content_length_string = to_return.headers_["content-length"];
    auto res = from_chars (content_length_string.data (), content_length_string.data () + content_length_string.size (), content_length);
    // if (res.ec == errc::invalid_argument) {
    //     cout << "Invalid content-length argument" << endl;
    //     return nullopt;
    // }
    
    auto body_begin = end_headers_it + 4;
    string_view body_view (body_begin, raw.end ());

    // if (content_length != body_view.size ())
    //     return nullopt;

    to_return.set_body (string (body_view));
    cout << "body: " << to_return.body_ << endl;

    return to_return;
}

bool HttpRequest::operator== (const HttpRequest &other) const {
    bool eq_requestlines = request_line_ == other.request_line_;
    bool eq_headers = headers_ == other.headers_;
    bool eq_body = body_ == other.body_;

    return eq_requestlines && eq_headers && eq_body;
}