//
// Created by vovan on 04.05.2020.
//

#ifndef CAM_PROJECT_3_CAM_ADAPTER_H
#define CAM_PROJECT_3_CAM_ADAPTER_H

#define O_BINARY 0

#include <string>
#include <cstring>
#include <fcntl.h>
#include <gphoto2/gphoto2-camera.h>

class CamAdapter {
public:
    CamAdapter();
    ~CamAdapter();

    int initCamera();
    std::string getCameraInfo();
    int getCapture(char *fn);
    int getPreview(unsigned char **data, unsigned long int *size);


private:
    Camera		*camera;
    int		    ret = -1;
    GPContext	*context;
    CameraText	cameraText;
};


#endif //CAM_PROJECT_3_CAM_ADAPTER_H
