#ifndef HTTP_MESSAGE_H
#define HTTP_MESSAGE_H

#include <unordered_map>
#include <string>
#include <string_view>
#include <optional>


enum class HttpMethod {
    GET, HEAD, POST, PUT, DELETE,
    CONNECT, OPTIONS, TRACE
};

struct HttpRequestLine {
  // The choice of default value for method_ is arbitrary, but
  // being explicit about it is good because it makes behavior transparent.
  HttpMethod method_ {HttpMethod::GET};

  std::string uri_ {};

  bool operator== (const HttpRequestLine &other) const = default;

};

struct HttpResponseLine {
  int status_ {};
  std::optional<std::string> status_reason_ {};
};


class HttpMessage {
public:
  HttpMessage () = default;
  virtual std::string serialize () const = 0;
  

  static std::string serialize_method (const HttpMethod &method);
  static std::optional<HttpMethod> deserialize_method (std::string_view data);

  void set_headers (std::unordered_map<std::string, std::string> headers); // TODO: implement
  void set_body (std::string_view body) {body_ = std::string (body);}
  void set_header (std::string key, std::string value) {headers_[key] = value;}
  void set_version (int major, int minor);
  int get_major_version () const {return major_ver_;}
  int get_minor_version () const {return minor_ver_;}

  ~HttpMessage ();
  
protected:
  int major_ver_ {};
  int minor_ver_ {};
  std::unordered_map<std::string, std::string> headers_ {};
  std::string body_ {};
};


#endif