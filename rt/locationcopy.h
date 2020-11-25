/*
 * Location.h
 *
 * A Location class a Location class identifies a point on the Earth
 * (or any sphere).
 */

#ifndef LOCATION_H
#define LOCATION_H

#include <string>

class Location
{
public:
        Location();
        Location(double latitude, double longitude);

        void   set_location(double latitude, double longitude);
        double distance_to(Location &other);
        double distance_to(Location *other);
        void   print();
        std::string to_string();
private:
        double  longitude;
        double  latitude;
};