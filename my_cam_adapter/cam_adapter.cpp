//
// Created by vovan on 04.05.2020.
//



#include "cam_adapter.h"

int CamAdapter::initCamera() {
    ret = gp_camera_init (camera, context);
    if (ret < GP_OK) {
        printf("No camera auto detected.\n");
        //gp_camera_free (camera);
        return -1;
    }
    return 1;
}

CamAdapter::CamAdapter() {
    context = gp_context_new();
    gp_camera_new(&camera);
}

CamAdapter::~CamAdapter() {
    gp_camera_exit(camera, context);
    gp_camera_free(camera);
    gp_context_unref(context);
}

std::string CamAdapter::getCameraInfo() {
    if (ret < GP_OK)
        return "Camera isn't initialized";
    ret = gp_camera_get_summary (camera, &cameraText, context);
    if (ret < GP_OK) {
        gp_camera_free (camera);
        return "Camera failed retrieving summary.";
    }
    return cameraText.text;
}


//isn't work correctly
int CamAdapter::getCapture(char *fn) {
    if (ret < GP_OK)
        return -1;
    int fd, retval;
    CameraFile *file;
    CameraFilePath camera_file_path;

    /* NOP: This gets overridden in the library to /capt0000.jpg */
    strcpy(camera_file_path.folder, "/");
    strcpy(camera_file_path.name, "foo.jpg");

    retval = gp_camera_capture(camera, GP_CAPTURE_IMAGE, &camera_file_path, context);
    fd = open(fn, O_CREAT | O_WRONLY | O_BINARY, 0644);
    retval = gp_file_new_from_fd(&file, fd);
    retval = gp_camera_file_get(camera, camera_file_path.folder, camera_file_path.name,
                                GP_FILE_TYPE_NORMAL, file, context);
    gp_file_free(file);
    retval = gp_camera_file_delete(camera, camera_file_path.folder, camera_file_path.name,
                                   context);
    return 1;
}

//returns not tested array!!!
int CamAdapter::getPreview(char **data, unsigned long int *size) {
    int is_OK = -1;;
    CameraFile* file;
    try {
        is_OK = gp_camera_capture_preview(camera, file, context);
        if (is_OK != GP_OK) {

        } else {
            is_OK = gp_file_get_data_and_size(file, (const char **) data, size);
        }
    }
    catch (const std::exception &e) {

    }
    std::cout << is_OK << " -- " << *size << "\n";
    return is_OK;
}

int CamAdapter::getCapture(char **data, unsigned long int *size) {
    int is_OK = -1;
    if (ret < GP_OK)
        return is_OK;

    CameraFile* file;
    CameraFilePath camera_file_path;

    strcpy(camera_file_path.folder, "/" );
    strcpy(camera_file_path.name, "foo.jpg");

    is_OK = gp_camera_capture(camera, GP_CAPTURE_IMAGE, &camera_file_path, context);

    is_OK = gp_camera_file_get(camera, camera_file_path.folder, camera_file_path.name, GP_FILE_TYPE_NORMAL, file, context);
    is_OK = gp_file_get_data_and_size(file, (const char **)data, size);

    is_OK = gp_camera_file_delete(camera, camera_file_path.folder, camera_file_path.name, context);

    return is_OK;
}
