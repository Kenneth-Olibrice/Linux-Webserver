#include "../include/HttpMessage.hh"

using namespace std;


string HttpMessage::serialize_method (const HttpMethod &method) {
    string retval {};

    switch (method) {
        case HttpMethod::GET:
          retval = "GET";
          break;
        case HttpMethod::HEAD:
          retval = "HEAD";
          break;
        default:
          throw "HttpMethod::serialize_method() not fully implemented!";
    }

    return retval;
}

void HttpMessage::set_version (int major, int minor) {
  major_ver_ = major;
  minor_ver_ = minor;
}

HttpMessage::~HttpMessage () {
  // Empty.
}