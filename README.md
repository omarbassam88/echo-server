# Qt Echo Server

A simple Qt application that runs a basic TCP server that you can connect to and send messages and it will echo back the messages you sent.

This was originally done for educational purposes following the Plural Sight Tutorial by Tod Gentille.

[Introduction to Qt: A C++ Cross Platform Application Framework](https://app.pluralsight.com/library/courses/introduction-qt-cplusplus-framework/table-of-contents)

## Basic Usage

- Start the server.
- Connect to the server using telnet at port 3000.

    `telnet localhost 3000`

- Use tel net to send messages to the server.
- The server should echo Back your messages enclosed in an `echo-server` tag.

## System Requirements

- Qt6
- CMake =>3.5
- telnet
