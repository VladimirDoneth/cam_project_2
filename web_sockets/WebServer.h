//
// Created by vovan on 25.03.2020.
//

#ifndef WS_DEVICES_2_WEBSERVER_H
#define WS_DEVICES_2_WEBSERVER_H

#include "seasocks/PrintfLogger.h"
#include "seasocks/Server.h"
#include "seasocks/StringUtil.h"
#include "seasocks/WebSocket.h"
#include "seasocks/util/Json.h"
#include "seasocks/PageHandler.h"
#include "lib_my_event_handler/event_ws.h"
#include "lib_my_event_handler/delegate_ws.h"

#include "client_events.h"

#include <iostream>
#include <cstdio>
#include <chrono>
#include <cstdlib>
#include <getopt.h>
#include <memory>
#include <cstring>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <mutex>

using namespace std::chrono;
using namespace seasocks;
using namespace std;

class MyServer : public Server {
public:
    using Server::Server;

private:
    virtual void checkThread() const override {

    };
};


class MyHandler : public WebSocket::Handler {
public:
    explicit MyHandler(MyServer* server);

    virtual void onConnect(WebSocket* connection);
    virtual void onData(WebSocket* connection, const char* data);
    virtual void onDisconnect(WebSocket* connection);

    /**a method for sending a single string value to websocket client*/
    void sendValue(const std::string values);

    /**a method for sending a strings vector values to websocket client*/
    //template <typename Seq<std::string>>
    //void sendVectorValues(const Seq& seq);
    void sendVectorValues(const std::vector<std::string> vector_values);


private:
    set<WebSocket*> _connections;   //set of WebSocket connections
    std::shared_ptr<Server> _server;                //pointer on object of this server
    DelegateWS* _delegate;          //instance of event delegator
};

/**this used to */
struct MyAuthHandler : PageHandler {
    std::shared_ptr<Response> handle(const Request& request) override {
        // Here one would handle one's authentication system, for example;
        // * check to see if the user has a trusted cookie: if so, accept it.
        // * if not, redirect to a login handler page, and await a redirection
        //   back here with relevant URL parameters indicating success. Then,
        //   set the cookie.
        // For this example, we set the user's authentication information purely
        // from their connection.
        request.credentials()->username = formatAddress(request.getRemoteAddress());
        return Response::unhandled(); // cause next handler to run
    }
};
#endif //WS_DEVICES_2_WEBSERVER_H