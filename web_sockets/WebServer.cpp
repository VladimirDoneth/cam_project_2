//
// Created by vovan on 25.03.2020.
//

#include "WebServer.h"

MyHandler::MyHandler(MyServer* server) : _server(server){
    this->_delegate = DelegateWS::getInstance();
}

void MyHandler::onConnect(WebSocket* connection) {

    //cout << "onConnect getRequestUri: " << connection->getRequestUri() << endl;
    _connections.insert(connection);
    /*cout << "Connected: " << connection->getRequestUri()
         << " : " << formatAddress(connection->getRemoteAddress())
         << endl;
    cout << "Credentials: " << *(connection->credentials()) << endl;*/
    _delegate->doEvent(std::make_shared<EventWS>(CONNECTED_WEB_CLIENT));
}


/**there we generate events for different clicking of buttons on web page*/
void MyHandler::onData(WebSocket* connection, const char* data) {
    cout << "onData: " << data << endl;
    if ( strcmp(data, STR_GET_LIST_PORTS) == 0) {
        _delegate->doEvent(std::make_shared<EventWS>(GET_LIST_PORTS));
    } else if (strcmp(data, STR_GET_AUTO_DETECT) == 0) {
        _delegate->doEvent(std::make_shared<EventWS>(GET_AUTO_DETECT));
    } else if (strcmp(data, STR_GET_SUMMARY) == 0) {
        _delegate->doEvent(std::make_shared<EventWS>(GET_SUMMARY));
    } else if (strcmp(data, STR_GET_LIST_FILES) == 0) {
        _delegate->doEvent(std::make_shared<EventWS>(GET_LIST_FILES));
    } else if (strcmp(data, STR_GET_NOW_PHOTO) == 0) {
        _delegate->doEvent(std::make_shared<EventWS>(GET_NOW_PHOTO));
    }
}

void MyHandler::onDisconnect(WebSocket* connection) {
    _connections.erase(connection);
    /*cout << "Disconnected: " << connection->getRequestUri()
         << " : " << formatAddress(connection->getRemoteAddress())
         << endl;*/
    _delegate->doEvent(std::make_shared<EventWS>(DISCONNECTED_WEB_CLIENT));
}

void MyHandler::sendValue(const std::string values) {
    std::cout << values << std::endl;
    for (auto c : _connections) {
        c->send(values);
    }
}

void MyHandler::sendVectorValues(const std::vector<std::string> vector_values) {
    for (auto c: _connections)
        for (std::string val: vector_values)
            c->send(val);
}
