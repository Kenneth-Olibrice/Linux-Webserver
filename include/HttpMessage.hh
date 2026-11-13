#include <unordered_map>
#include <string>

enum HttpMethod {
    GET, HEAD, POST, PUT, DELETE,
    CONNECT, OPTIONS, TRACE
};



class HttpMessage {
public:
  std::string serialize () const;


  static inline std::string serialize_method (const HttpMethod &method);
  
private:
  HttpMethod method_;
  std::string version_;
  std::string address_;
  std::unordered_map<std::string, std::string> headers_;
  std::string body_;
};