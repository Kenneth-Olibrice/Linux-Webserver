#include <gtest/gtest.h>
#include "../include/HttpRequest.hh"


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