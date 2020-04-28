#include <iostream>
#include <memory>
#include "lib_gphoto2_bash_adapter/gphoto2_bash.h"
#include "my_web_server_worker.h"

int main() {
    /* this is a begin point for starting work a program in a constructor of MyWebServerWorker
     * we start a WebServer in a new thread
     */
    std::shared_ptr<MyWebServerWorker> myWebServerWorker = std::make_shared<MyWebServerWorker>();
    /* and here we start a thread with a Handler */
    myWebServerWorker->processHandler();
    return 0;
}


//there was a code for testing a gphoto2_bash adapter, and then it moved into a new version
/*
int main() {
    bool isRun = true;
    std::shared_ptr<Gphoto2_adapter> adapter = std::make_shared<Gphoto2_adapter>();

    while (isRun) {
        std::cout << "Please print a command" << std::endl;
        std::cout << "1. gphoto2 --list-ports" << std::endl;
        std::cout << "2. gphoto2 --auto-detect" << std::endl;
        std::cout << "3. gphoto2 --summary" << std::endl;
        std::cout << "4. gphoto2 --list-files" << std::endl;
        std::cout << "5. gphoto2 --trigger-capture" << std::endl;
        std::cout << "-1. EXIT" << std::endl;

        std::vector<std::string> vector_result;

        int command;
        std::cin >> command;
        switch (command) {
            case 1:
                vector_result = adapter->get_list_ports();
                break;
            case 2:
                vector_result = adapter->get_auto_detect();
                break;
            case 3:
                vector_result = adapter->get_summary();
                break;
            case 4:
                vector_result = adapter->get_list_files();
                break;
            case 5:
                adapter->remove_photo_file();
                adapter->trigger_capture();
                adapter->get_photo_file();
                break;
            case -1:
                std::cout << "GOOD BYE, BRO!" << std::endl;
                isRun = false;
                break;
            default:
                std::cout << "WRONG COMMAND ..." << std::endl;
        }
        for (std::string str: vector_result)
            std::cout << str;

        std::cout << "\n\n ________>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<__________\n" << std::endl;
    }
    return 0;
}
*/