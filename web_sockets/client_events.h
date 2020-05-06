//
// Created by vovan on 23.04.2020.
//

#ifndef CAM_PROJECT_2_CLIENT_EVENTS_H
#define CAM_PROJECT_2_CLIENT_EVENTS_H

/**There are some typical constants for events handling from a client*/
#define STR_GET_LIST_PORTS      "GET_LIST_PORTS"        // -//-
#define STR_GET_AUTO_DETECT     "GET_AUTO_DETECT"       // command for checking connected to raspberryPI cameras
#define STR_GET_SUMMARY         "GET_SUMMARY"           // command for getting full information about connected camera
#define STR_GET_LIST_FILES      "GET_LIST_FILES"        // -//-
#define STR_GET_NOW_PHOTO       "GET_NOW_PHOTO"         // command for doing a new photo and sending it to a web_client
#define STR_GET_PREVIEW          "GET_PREVIEW"          // command for getting a photo preview
#define STR_DO_ZOOM_PLUS         "DO_ZOOM_PLUS"         // command for increase zoom an image on a camera
#define STR_DO_ZOOM_MINUS        "DO_ZOOM_MINUS"        // -//-

#define GET_LIST_PORTS          0                       // here is a version for events
#define GET_AUTO_DETECT         1                       //
#define GET_SUMMARY             2                       //
#define GET_LIST_FILES          3                       //
#define GET_NOW_PHOTO           4                       //
#define GET_PREVIEW             5                       //
#define DO_ZOOM_PLUS            6                       //
#define DO_ZOOM_MINUS           7                       //

#define CONNECTED_WEB_CLIENT    8                       //that for event, that says that we have a new connected web-client
#define DISCONNECTED_WEB_CLIENT 9                       //that for event, that says that we have a disconnected web-client

#endif //CAM_PROJECT_2_CLIENT_EVENTS_H
