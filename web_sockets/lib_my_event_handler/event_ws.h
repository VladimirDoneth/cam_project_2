//
// Created by vovan on 02.04.2020.
//

#ifndef WS_DEVICES_2_EVENT_WS_H
#define WS_DEVICES_2_EVENT_WS_H

/*These is a class EventWS, which used for contains an event state*/
class EventWS {
private:
    /*logical field with information about EVENT*/
    int idEvent;

public:
    /*Constructor for creating a new EventWS object,
     * ~>public constructor*/
    EventWS(int);
    ~EventWS();

    /*function for getting an event information
     * ~>public function*/
    int getEventID();
};


#endif //WS_DEVICES_2_EVENT_WS_H
