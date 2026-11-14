#include "../include/HttpMessage.hh"

using namespace std;


string HttpMessage::serialize_method (const HttpMethod &method) {
    string retval {};

    switch (method) {
        case GET:
          retval = "GET";
          break;
        case HEAD:
          retval = "HEAD";
          break;
        default:
          throw "HttpMethod::serialize_method() not fully implemented!";
    }

    return retval;
}

// `serialize()` turns an HttpMessage object and converts it to a string of bytes
// conforming to the message format defined in [RFFC 9112]. 
//
// `serialize()` performs no correctness checking and can produce 
// a malformed HTTP message string. It is the responsibility of the caller
// to ensure that an HttpMessage object is correct before calling `serialize()`.
string HttpMessage::serialize () const {
    string retval {};


    string method = serialize_method (method_);
    

    retval += method;
    retval += " ";

    retval += address_;
    retval += " ";

    retval += version_;
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