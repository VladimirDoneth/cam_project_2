//
// Created by vovan on 04.05.2020.
//

#ifndef CAM_PROJECT_3_CAM_ADAPTER_H
#define CAM_PROJECT_3_CAM_ADAPTER_H

#define O_BINARY 0

#include <string>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <gphoto2/gphoto2-camera.h>

class CamAdapter {
public:
    CamAdapter();       /**default constructor*/
    ~CamAdapter();      /**default destructor*/

    int initCamera();       /**for starting work an camera*/
    std::string getCameraInfo();    /**for getting a camera information like a firm_name, a count of memory, works types and so on*/
    int getCapture(char *fn);       /**for getting a capture and saving it on Raspberry PI like a file with "fn" name*/
    int getCapture(char **data, unsigned long int *size);       /**for getting a capture as a char array*/
    int getPreview(char *fn);  /**for getting preview and saving it on Raspberry PI like a file with "fn" name*/      //not work???
    int getPreview(char **data, unsigned long int *size);  /**for getting a preview as a char array */

    int doZoomPlus();       /**for increasing an image on a camera*/
    int doZoomMinus();      /**for decreasing an image on a camera*/

private:
    Camera		*camera;
    int		    ret = -1;
    GPContext	*context;
    CameraText	cameraText;


};


#endif //CAM_PROJECT_3_CAM_ADAPTER_H
