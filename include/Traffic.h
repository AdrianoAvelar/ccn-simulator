/*
 * Traffic.h
 *
 *  Created on: Apr 10, 2014
 *      Author: adriano
 */

#ifndef TRAFFIC_H_
#define TRAFFIC_H_

class Property {


private:


};

class Traffic {

    virtual void start() = 0;
    virtual void addProperty(Property* property);
    virtual void received();
};

#endif /* TRAFFIC_H_ */
