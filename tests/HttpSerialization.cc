#include <gtest/gtest.h>
#include <iostream>
#include <optional>

#include "../include/HttpRequest.hh"
#include "../include/HttpMessage.hh"
#include "../include/RequestLineParser.hh"

// Confirm that the most basic GET request is properly
// serialized.
TEST (HttpSerialization, BasicGet) {
    HttpRequest msg {};
    msg.set_uri ("/");
    msg.set_method (HttpMethod::GET);
    msg.set_version (1, 1);
    msg.set_header ("host", "localhost");

    std::string serialized_msg {msg.serialize ()};
    std::string correct_serialization = "GET / HTTP/1.1\r\nhost:localhost\r\n\r\n";
    ASSERT_EQ (serialized_msg, correct_serialization);
}


TEST (HttpSerialization, BasicDeserializeMethod) {
    std::string method_get {"GET"};

    // According to [RFC 9110], HTTP methods are case sensitive.
    std::string lowercase_get {"get"};

    // Method names with whitespaces should be rejected as malformed.
    std::string space_get {"g et"};
    std::string space_get2 {"get "};
    std::string space_get3 {" get"};
    
    ASSERT_NE (HttpMethod::GET, HttpMessage::deserialize_method (lowercase_get));
    ASSERT_NE (HttpMethod::GET, HttpMessage::deserialize_method (space_get));
    ASSERT_NE (HttpMethod::GET, HttpMessage::deserialize_method (space_get2));
    ASSERT_NE (HttpMethod::GET, HttpMessage::deserialize_method (space_get3));
    ASSERT_EQ (HttpMethod::GET, HttpMessage::deserialize_method (method_get));

    std::cout << "buns" << std::endl;
}

TEST (HttpSerialziation, DeserializeValid) {
    std::string request1 = "GET / HTTP/1.1\r\n"
                           "host:www.youtube.com\r\n"
                           "header1:value1\r\n"
                           "header2:value2\r\n"
                           "content-length:12\r\n"
                           "\r\n"
                           "Hello world!";

    HttpRequest correct_deserialized;

    // Correct start-line serialization.
    correct_deserialized.set_method (HttpMethod::GET);
    correct_deserialized.set_uri ("/");
    correct_deserialized.set_version (1,1);

    // Correct headers serialization.
    correct_deserialized.set_header ("host", "www.youtube.com");
    correct_deserialized.set_header ("header1", "value1");
    correct_deserialized.set_header ("header2", "value2");
    
    std::optional actual_deserialized = HttpRequest::deserialize (request1);

    ASSERT_TRUE (actual_deserialized.has_value ());
    // ASSERT_EQ (correct_deserialized, actual_deserialized.value ());

}