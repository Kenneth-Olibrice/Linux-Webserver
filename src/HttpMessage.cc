#include "HttpMessage.hh"

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