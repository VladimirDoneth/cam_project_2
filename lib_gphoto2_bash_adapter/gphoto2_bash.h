//
// Created by vovan on 23.04.2020.
//

#ifndef CAM_PROJECT_2_GPHOTO2_BASH_H
#define CAM_PROJECT_2_GPHOTO2_BASH_H

#define COMMAND_GPHOTO2_LIST_PORTS      "gphoto2 --list-ports"
#define COMMAND_GPHOTO2_AUTO_DETECT     "gphoto2 --auto-detect"
#define COMMAND_GPHOTO2_SUMMARY         "gphoto2 --summary"
#define COMMAND_GPHOTO2_LIST_FILES      "gphoto2 --list-files"
#define COMMAND_GPHOTO2_SET_SAVE_PLACE_INTERNAL_RAM     "gphoto2 --set-config capturetarget=0"
#define COMMAND_GPHOTO2_TRIGGER_CAPTURE                 "gphoto2 --trigger-capture"
#define COMMAND_GPHOTO2_GET_PHOTO                       "gphoto2 --get-file 1"
#define COMMAND_REMOVE_PHOTO            "rm *.jpg"

#include <string>
#include <vector>

class Gphoto2_adapter {
private:
    char buff[128];     //char buffer, used global to avoid a memory weak
    /**a private function used for returning a vector strings with result of running a 'bash command'*/
    std::vector<std::string> get_info_from_gphoto2(const char *command);
    /**a private function used constructor to set a save point for taking a photo on a camera*/
    void set_save_to_internal_RAM();

public:
    Gphoto2_adapter();
    /**a public function used for getting a total information by connected camera/cameras*/
    std::vector<std::string> get_summary();
    /** used for getting a list of supported ports*/
    std::vector<std::string> get_list_ports();
    /** used for getting a list of available media files*/
    std::vector<std::string> get_list_files();
    /** used for detecting a connected cameras*/
    std::vector<std::string> get_auto_detect();

    /** used for do capture on a camera*/
    void trigger_capture();
    /** used for loading on Raspberry Pi photo which was already done*/
    void get_photo_file();
    /** used for removing a photo file on Raspberry Pi*/
    void remove_photo_file();
};

#endif //CAM_PROJECT_2_GPHOTO2_BASH_H
