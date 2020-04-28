//
// Created by vovan on 17.04.2020.
//

#include "gphoto2_bash.h"

std::vector<std::string> Gphoto2_adapter::get_info_from_gphoto2(const char *command) {
    std::vector<std::string> result;
    FILE *process_file;
    process_file = popen(command, "r");
    if (process_file != NULL) {
        while (fgets(buff, sizeof(buff), process_file))
            result.push_back(buff);
        pclose(process_file);
    }
    return result;
}

std::vector<std::string> Gphoto2_adapter::get_summary() {
    return get_info_from_gphoto2(COMMAND_GPHOTO2_SUMMARY);
}

std::vector<std::string> Gphoto2_adapter::get_list_ports() {
    return get_info_from_gphoto2(COMMAND_GPHOTO2_LIST_PORTS);
}

std::vector<std::string> Gphoto2_adapter::get_list_files() {
    return get_info_from_gphoto2(COMMAND_GPHOTO2_LIST_FILES);
}

std::vector<std::string> Gphoto2_adapter::get_auto_detect() {
    return get_info_from_gphoto2(COMMAND_GPHOTO2_AUTO_DETECT);
}

void Gphoto2_adapter::set_save_to_internal_RAM() {
    system(COMMAND_GPHOTO2_SET_SAVE_PLACE_INTERNAL_RAM);
}

void Gphoto2_adapter::trigger_capture() {
    system(COMMAND_GPHOTO2_TRIGGER_CAPTURE);
}

void Gphoto2_adapter::get_photo_file() {
    system(COMMAND_GPHOTO2_GET_PHOTO);
}

void Gphoto2_adapter::remove_photo_file() {
    system(COMMAND_REMOVE_PHOTO);
}

Gphoto2_adapter::Gphoto2_adapter() {
    this->set_save_to_internal_RAM();
}
