//
// Created by biba_bo on 5/8/20.
//



#include <bits/fcntl-linux.h>
#include <fcntl.h>
#include "cam_adapter.h"

CamAdapterGphoto2::CamAdapterGphoto2() {
    isCameraInitialized = false;
}

CamAdapterGphoto2::CamAdapterGphoto2(Camera *camera, GPContext *context) {
    isCameraInitialized = true;
    this->context = context;
    this->camera = camera;
}

CamAdapterGphoto2::~CamAdapterGphoto2() {
    if(isCameraInitialized) {
        gp_camera_exit(camera, context);
        gp_camera_free(camera);
        gp_context_unref(context);
    }
}

int CamAdapterGphoto2::tryToInitCamera() {
    if (isCameraInitialized)
        return CAMERA_WAS_INITIALIZED;

    context = create_context();
    gp_camera_new (&camera);

    int opt_res = gp_camera_init(camera, context);
    if (opt_res < GP_OK) {
        gp_camera_free(camera);
        isCameraInitialized = false;
        return CAMERA_NOT_FOUND;
    }

    isCameraInitialized = true;
    return CAMERA_SUCCESSFULLY_INIT;
}

int CamAdapterGphoto2::tryToReinitCamera() {
    if (isCameraInitialized) {
        gp_camera_exit(camera, context);
        gp_camera_free(camera);
        gp_context_unref(context);
    }

    context = create_context();
    gp_camera_new(&camera);

    int opt_res = gp_camera_init(camera, context);
    if (opt_res < GP_OK) {
        gp_camera_free(camera);
        isCameraInitialized = false;
        return CAMERA_NOT_FOUND;
    }

    isCameraInitialized = true;
    return CAMERA_SUCCESSFULLY_INIT;
}

std::string CamAdapterGphoto2::getCameraSummary() {
    if (!isCameraInitialized)
        return "CAMERA_ISN'T INITIALIZED";
    CameraText cameraText;
    int opt_res = gp_camera_get_summary(camera, &cameraText, context);
    if (opt_res < GP_OK)
        return "CAMERA FAILED RETRIEVING SUMMARY.";
    return cameraText.text;
}

int CamAdapterGphoto2::getCapture(char *fn) {
    if (!isCameraInitialized)
        return CAMERA_NOT_INITIALIZED;

    int fd, opt_res;
    CameraFile *file;
    CameraFilePath  camera_file_path;

    std::cout << "Start capturing...\n";
    strcpy(camera_file_path.folder, "/");
    strcpy(camera_file_path.name, "tmp_image.jpg");

    opt_res = gp_camera_capture(camera, GP_CAPTURE_IMAGE, &camera_file_path, context);
    if (opt_res < GP_OK)
        return CANNOT_CAPTURE;
    fd = open(fn, O_CREAT | O_WRONLY | O_BINARY, 0644);
    opt_res = gp_file_new_from_fd(&file, fd);
    opt_res = gp_camera_file_get(camera, camera_file_path.folder, camera_file_path.name,
            GP_FILE_TYPE_NORMAL, file, context);
    gp_file_free(file);
    if (opt_res < GP_OK)
        return CANNOT_GET_FILE;

    opt_res = gp_camera_file_delete(camera, camera_file_path.folder, camera_file_path.name, context);
    if (opt_res < GP_OK)
        return CANNOT_DELETE_CAMFILE;

    return CAMERA_SUCCESSFULLY_CAPTURED;
}

int CamAdapterGphoto2::getCapture(char **data, unsigned long *size) {
    return 0;
}


