#include <gtest/gtest.h>
#include "../include/HttpMessage.hh"


// Confirm that the most basic GET request is properly
// serialized.
TEST (HttpSerialization, BasicGet) {
    HttpMessage msg {};
    msg.set_address ("/");
    msg.set_method (HttpMethod::GET);
    msg.set_version ("HTTP/1.1");
    msg.set_header ("host", "localhost");

    std::string serialized_msg {msg.serialize ()};
    std::string correct_serialization = "GET / HTTP/1.1\r\nhost:localhost\r\n\r\n";
    ASSERT_EQ (serialized_msg, correct_serialization);
}