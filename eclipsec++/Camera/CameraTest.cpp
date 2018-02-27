/*
 * CameraTest.cpp
 *
 *  Created on: 26 Feb 2018
 *      Author: dan
 */
#include <ctime>
#include <fstream>
#include <iostream>
#include <unistd.h>
//#include <stdlib.h>
#include "raspicam.h"

using namespace std;

int main ( int argc,char **argv ) {
    raspicam::RaspiCam Camera; //Cmaera object
    //Open camera
    cout<<"Opening Camera..."<<endl;
    if ( !Camera.open()) {cerr<<"Error opening camera"<<endl;return -1;}
    //wait a while until camera stabilizes
    cout<<"Sleeping for 3 secs"<<endl;
    sleep(3);
    //capture
    Camera.grab();
    //allocate memory
    unsigned char *data=new unsigned char[  Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
    cout << Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) << endl;
    //extract the image in rgb format
    Camera.retrieve ( data,raspicam::RASPICAM_FORMAT_RGB );//get camera image
    //save
    std::ofstream outFile ( "raspicam_image.ppm",std::ios::binary );
    outFile<<"P6\n"<<Camera.getWidth() <<" "<<Camera.getHeight() <<" 255\n";
    outFile.write ( ( char* ) data, Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );
    cout<<"Image saved at raspicam_image.ppm"<<endl;
    //free resrources

    /* RESET THE BUFFER */
    sleep(2);
    Camera.grab();
    //memset(data, 0, Camera.retrieve(data,raspicam::RASPICAM_FORMAT_RGB));

    Camera.retrieve(data, raspicam::RASPICAM_FORMAT_RGB );

    std::ofstream outFile2 ( "raspicam_image2.ppm",std::ios::binary );
    outFile2<<"P6\n"<<Camera.getWidth() <<" "<<Camera.getHeight() <<" 255\n";

    outFile2.write((char*) data, Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB));
    cout<<"Image saved at raspicam_image2.ppm"<<endl;

    delete data;
    return 0;
}
