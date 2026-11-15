#include "../include/HttpRequest.hh"

using namespace std;


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