//
// Created by biba_bo on 5/8/20.
//

#ifndef CAM_PROJECT_2_CAM_ADAPTER_H
#define CAM_PROJECT_2_CAM_ADAPTER_H

#define CAMERA_OK                       0

#define CAMERA_WAS_INITIALIZED          1
#define CAMERA_SUCCESSFULLY_INIT        2
#define CAMERA_SUCCESSFULLY_CAPTURED    3

#define CAMERA_NOT_FOUND                -1
#define CAMERA_NOT_INITIALIZED          -2
#define CANNOT_CAPTURE                  -3
#define CANNOT_GET_FILE                 -4
#define CANNOT_DELETE_CAMFILE           -5



#include <gphoto2/gphoto2-camera.h>
#include <string>
#include <iostream>
#include <cstring>

#include "cam_functions.h"

class CamAdapterGphoto2 {
public:
    CamAdapterGphoto2();
    CamAdapterGphoto2(Camera* camera, GPContext* context);
    ~CamAdapterGphoto2();

    int tryToInitCamera();
    int tryToReinitCamera();

    std::string getCameraSummary();

    int getCapture(char *fn);       /**for getting a capture and saving it on Raspberry PI like a file with "fn" name*/
    int getCapture(char **data, unsigned long int *size);       /**for getting a capture as a char array*/
    int getPreview(char *fn);       /**for getting preview and saving it on Raspberry PI like a file with "fn" name*/      //not work???
    int getPreview(char **data, unsigned long int *size);  /**for getting a preview as a char array */

    int doZoomPlus();       /**for increasing an image on a camera*/
    int doZoomMinus();      /**for decreasing an image on a camera*/

private:
    Camera *camera;
    GPContext  *context;
    bool isCameraInitialized;
};


#endif //CAM_PROJECT_2_CAM_ADAPTER_H
