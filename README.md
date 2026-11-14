An HTTP/1.1 Webserver written in C++. 

To build, navigate to the root directory and run `cmake -S . -B build` followed by `cmake --build build`. 

To start the server, run `build/server`. Root is required.

To run unit tests, run `cmake --build build --target test` after building.
