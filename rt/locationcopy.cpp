#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <math.h>

#include "Location.h"

using namespace std;

Location::Location()
{
        longitude = 0.0;
        latitude  = 0.0;
}

Location::Location(double someLatitude, double someLongitude)
{
        latitude  = someLatitude;
        longitude = someLongitude;
}
void Location::set_location(double someLatitude, double someLongitude)
{
        longitude = someLongitude;
        latitude  = someLatitude;
}

string Location::to_string()
{
        stringstream result;

        result << setprecision(2) << fixed
               << latitude << ' ' << longitude;

        return result.str();
}

void Location::print()
{
        printf("%.2f %.2f", latitude, longitude);
}


/*
 * from
 *  http://www.codeproject.com/Articles/22488/
 *          Distance-using-Longitiude-and-latitude-using-c
 */

// distance function using a pointer
//  arg: a pointer to a location
//  ret: the distance between the calling location and the arg
//
double Location::distance_to(Location *locp)
{
        return distance_to(*locp);
}

// distance function using a reference param
//  arg: a reference to a Location
//  ret: the distance between the calling location and the arg
//
double Location::distance_to(Location &x)
{
        double  longx, latx;

        latx  = x.latitude;
        longx = x.longitude;

        double PI = 4.0 * atan(1.0);

        //main code inside the class
        double dlat1  = latitude  * (PI / 180);
        double dlong1 = longitude * (PI / 180);

        double dlat2  = latx  * (PI / 180);
        double dlong2 = longx * (PI / 180);

        double dLong  = dlong1 - dlong2;
        double dLat   = dlat1  - dlat2;

        double aHarv  = pow(sin(dLat / 2.0), 2.0) +
                        cos(dlat1) * cos(dlat2) * pow(sin(dLong / 2), 2);
        double cHarv  = 2 * atan2(sqrt(aHarv), sqrt(1.0 - aHarv));

        // earth's radius from wikipedia varies
        // between 6,356.750 km -- 6,378.135 km (~3,949.901 -- 3,963.189 miles)
        // The IUGG value for the equatorial radius of
        // the Earth is 6378.137 km (3963.19 mile)

        const double earth = 3963.19;           // I am doing miles,
                                                // just change this
                                                // to radius in kilometers
                                                // to get distances in km
        double dist    = earth * cHarv;
        return dist;
}