#include "../include/HttpMessage.hh"
#include <string_view>


class HttpRequest : public HttpMessage {
public:
  HttpRequest () = default;
  virtual std::string serialize () const override;

  void set_uri (std::string_view uri) {request_line_.uri_ = uri;}
  void set_method (HttpMethod method) {request_line_.method_ = method;}

  std::string getUri () const {return request_line_.uri_;}

  virtual ~HttpRequest ();

private:
  struct HttpRequestLine request_line_ {};
};