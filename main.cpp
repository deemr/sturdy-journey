#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
/* All the asio classes can be used by simply including the "asio.hpp" header file. */

void print(const boost::system::error_code& /*e*/){
    std::cout << "Hello, world from print" << std::endl;
}
int main() {
    /*
     * All programs that use asio need to have at least one I/O execution context,
     * such as an io_context or thread_pool object. An I/O execution context
     * provides access to I/O functionality. We declare an object of type
     * io_context first thing in the main function.
    */
    std::cout << "Blocking for 5 seconds..." << std::endl;

    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
    t.async_wait(&print);
    io.run();

    std::cout << "Hello, World!" << std::endl;

    return 0;
}
