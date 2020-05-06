//
// Created by vovan on 07.04.2020.
//

#include "my_web_server_worker.h"

bool isHaveMyEvent = false;
bool checkMyEvent() {
    return isHaveMyEvent;
}


MyWebServerWorker::MyWebServerWorker() {
    startServer();
    DelegateWS* delegateWs = DelegateWS::getInstance();
    delegateWs->addHandler(this);
    adapter = std::make_shared<Gphoto2_adapter>();
    camAdapter = std::make_shared<CamAdapter>();
    camAdapter->initCamera();//not good solution, try to modify a CamAdapter
}

void MyWebServerWorker::startServer() {
    this->server_thread = std::thread([this]() {
        logger = std::make_shared<PrintfLogger>();
        ws_server = make_shared<MyServer>(logger);
        handler = std::make_shared<MyHandler>(ws_server.get());
        ws_server->addPageHandler(std::make_shared<MyAuthHandler>());
        ws_server->addWebSocketHandler("/cam_project_2", handler);
        ws_server->serve("src/server_files", 9091);
    });
}

void MyWebServerWorker::handleEventWS(std::shared_ptr<EventWS> event) {
    eventAction = event->getEventID();
    switch (eventAction) {
        case CONNECTED_WEB_CLIENT:
            countActiveConnections++;
            break;
        case DISCONNECTED_WEB_CLIENT:
            countActiveConnections--;
            break;
        default:
            std::unique_lock<std::mutex> lck(mtx);
            isHaveMyEvent = true;
            cv.notify_one();
    }
}

void MyWebServerWorker::handleEventInOtherThread() {
    if (countActiveConnections > 0) {
        switch (eventAction) {
            case GET_LIST_PORTS:
                handler->sendVectorValues(adapter->get_list_ports());
                break;
            case GET_AUTO_DETECT:
                handler->sendVectorValues(adapter->get_auto_detect());
                break;
            case GET_SUMMARY:
                handler->sendVectorValues(adapter->get_summary());
                break;
            case GET_LIST_FILES:
                handler->sendVectorValues(adapter->get_list_files());
                break;
            case GET_NOW_PHOTO:
                imageTransfer(0);
                break;
            case GET_PREVIEW:
                imageTransfer(1);
                break;
            case DO_ZOOM_PLUS:
                break;
            case DO_ZOOM_MINUS:
                break;
            default:
                std::cout << "here we have a troubles with lock";
                break;
        }
    }
}

void MyWebServerWorker::imageTransfer(int param) {
    switch (param) {
        case 0:
            handler->sendValue("HERE SHOULD BE A PHOTO");
            adapter->remove_photo_file();
            //adapter->trigger_capture();
            //adapter->get_photo_file();
            camAdapter->getCapture("VirtualObjec.jpg");
            try {
                std::string data = getEncodedFileString("VirtualObjec.jpg");
                //std::cout << data << std::endl;
                handler->sendValue(data);
            } catch (std::exception e) {
                handler->sendValue("ERROR WITH IMAGE FILE");
            }
            break;
        case 1:
            char *data;
            unsigned long size;
            int res = camAdapter->getPreview(&data, &size);
            if (res < 0) {
                handler->sendValue("\nCANNOT TO GET A VALUE");
            } else {
                std::string str_value = base64EncodeSA(data, size);
                handler->sendValue("HERE SHOULD BE A PHOTO");
                handler->sendValue(str_value);
            }
            break;
    }
}

void MyWebServerWorker::processHandler() {
    while(true) {
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, checkMyEvent);
        isHaveMyEvent = false;
        handleEventInOtherThread();
        eventAction = -1;
    }
}

std::string base64EncodeSA(const char *buf, unsigned long bufLen) {
    size_t ret_size = bufLen+2;

    ret_size = 4*ret_size/3;

    std::string ret;
    ret.reserve(ret_size);

    unsigned char b3[3];
    for (unsigned int i=0; i<ret_size/4; ++i)
    {
        size_t index = i*3;
        b3[0] = buf[index+0];
        b3[1] = buf[index+1];
        b3[2] = buf[index+2];

        ret.push_back(toBase64Array[ ((b3[0] & 0xfc) >> 2) ]);
        ret.push_back(toBase64Array[ ((b3[0] & 0x03) << 4) + ((b3[1] & 0xf0) >> 4) ]);
        ret.push_back(toBase64Array[ ((b3[1] & 0x0f) << 2) + ((b3[2] & 0xc0) >> 6) ]);
        ret.push_back(toBase64Array[ ((b3[2] & 0x3f)) ]);
    }

    return ret;
}

std::string base64Encode(std::vector<char> buf, unsigned int bufLen) {
    size_t ret_size = bufLen+2;

    ret_size = 4*ret_size/3;

    std::string ret;
    ret.reserve(ret_size);

    unsigned char b3[3];
    for (unsigned int i=0; i<ret_size/4; ++i)
    {
        size_t index = i*3;
        b3[0] = buf[index+0];
        b3[1] = buf[index+1];
        b3[2] = buf[index+2];

        ret.push_back(toBase64Array[ ((b3[0] & 0xfc) >> 2) ]);
        ret.push_back(toBase64Array[ ((b3[0] & 0x03) << 4) + ((b3[1] & 0xf0) >> 4) ]);
        ret.push_back(toBase64Array[ ((b3[1] & 0x0f) << 2) + ((b3[2] & 0xc0) >> 6) ]);
        ret.push_back(toBase64Array[ ((b3[2] & 0x3f)) ]);
    }

    return ret;
}

std::string getEncodedFileString(std::string filename) {
    std::basic_ifstream<char> image_file (filename, std::ios_base::in | std::ios_base::binary);
    image_file.seekg(0, std::ios_base::end);
    size_t length = image_file.tellg();
    image_file.seekg(0, std::ios_base::beg);

    std::vector<char> charDataBuffer(length);
    image_file.read(&charDataBuffer[0], length);
    std::string res = base64Encode(charDataBuffer, length);
    image_file.close();
    return res;
}
