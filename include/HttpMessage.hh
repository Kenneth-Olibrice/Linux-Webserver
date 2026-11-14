#include <unordered_map>
#include <string>
#include <string_view>


enum HttpMethod {
    GET, HEAD, POST, PUT, DELETE,
    CONNECT, OPTIONS, TRACE
};



class HttpMessage {
public:
  std::string serialize () const;


  static inline std::string serialize_method (const HttpMethod &method);
  
  void set_method (HttpMethod method) {method_ = method;}
  void set_version (std::string_view version) {version_ = std::string (version);}
  void set_address (std::string_view address) {address_ = std::string (address);}
  void set_headers (std::unordered_map<std::string, std::string> headers); // TODO: implement
  void set_body (std::string_view body) {body_ = std::string (body);}
  void set_header (std::string key, std::string value) {headers_[key] = value;}

private:
  // The choice of default value for method_ is arbitrary, but
  // being explicit about it is good because it makes behavior transparent.
  HttpMethod method_ {HttpMethod::GET};
  std::string version_ {};
  std::string address_ {};
  std::unordered_map<std::string, std::string> headers_ {};
  std::string body_ {};
};