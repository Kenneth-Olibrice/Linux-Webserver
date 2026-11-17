#ifndef HTTP_REQUEST_HH
#define HTTP_REQUEST_HH

#include "../include/HttpMessage.hh"
#include <string_view>


class HttpRequest : public HttpMessage {
public:
  // SMFs.
  HttpRequest () = default;
  virtual ~HttpRequest ();

  // Serialization and deserialization.
  virtual std::string serialize () const override;
  static std::optional<HttpRequest> deserialize (std::string_view raw);
  static std::optional<HttpRequestLine> deserialize_request_line (std::string_view raw);

  // Mutators.
  void set_uri (std::string_view uri) {request_line_.uri_ = uri;}
  void set_method (HttpMethod method) {request_line_.method_ = method;}

  // State view.
  std::string getUri () const {return request_line_.uri_;}

  // Operators.
  bool operator== (const HttpRequest &other) const;
private:
  struct HttpRequestLine request_line_ {};
};

#endif