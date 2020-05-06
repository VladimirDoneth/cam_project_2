//
// Created by vovan on 07.04.2020.
//

#ifndef WS_DEVICES_2_MY_WEB_SERVER_WORKER_H
#define WS_DEVICES_2_MY_WEB_SERVER_WORKER_H

#include <string>
#include <thread>
#include <iostream>
#include <fstream>
#include <condition_variable>

#include "web_sockets/WebServer.h"
#include "lib_gphoto2_bash_adapter/gphoto2_bash.h"
#include "my_cam_adapter/cam_adapter.h"

/*this is a class MyWebServerWorker which extends a HandelrWS from a project for RaspberryPi and devices (MPU, ....)*/
class MyWebServerWorker: public HandlerWS {
public:
    /**this constructor initialize an WebServer, and run it in another thread*/
    MyWebServerWorker();
    /**override function from HandleWS used for handling events*/
    void handleEventWS(std::shared_ptr<EventWS> event) override;
    /**this function is a infinite loop for processing events*/
    void processHandler();

private:
    std::thread server_thread;                      //thread object for WebServer thread
    std::shared_ptr<PrintfLogger> logger;           //for printing a log
    std::shared_ptr<MyServer> ws_server;            //object of WebServer
    std::shared_ptr<MyHandler> handler;             //and handler for events on WebServer
    std::shared_ptr<Gphoto2_adapter> adapter;       //bash adapter for working with CLI gphoto2
    std::shared_ptr<CamAdapter> camAdapter;         //this object is for working with camera through libgphoto2
    int countActiveConnections = 0;                 //just for counting active connections, now has NOT a big sense and influence on system
    int eventAction = -1;                           //a code of current event

    std::mutex mtx;                                 //a mutex variable which used in condition lock
    std::condition_variable cv;                     //a condition variable


    void startServer();                             //function where started the thread of WebServer
    void handleEventInOtherThread();                //it used for handing events which need a lot of computer time (hard to compute)
    void imageTransfer(int param);                  //it used for moving an image from a camera to Raspberry Pi an them to client
                                                    //if param == 0 here use a default capture method on a camera
                                                    //if param == 1 this function get from camera a default preview image
};

/*may be I should to create a new class for this?
 * there a few functions for encoding binary file to base64 for moving to client throw websocket
 * toBase64Array[] a char array with symbols for encoding
 * base64Encode(...) a function for getting encoded string
 * getEncodedFileString(...) - this function getting an filename and read this file then used th base64Encode() function
 *      and return an encoded string*/
static const char toBase64Array[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
std::string base64Encode(std::vector<char> buf, unsigned int bufLen);
std::string base64EncodeSA(const char *buf, unsigned long bufLen);
std::string getEncodedFileString(const std::string filename);

#endif //WS_DEVICES_2_MY_WEB_SERVER_WORKER_H