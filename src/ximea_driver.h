// Sample for XIMEA Software Package V2.57
#include <m3api/xiApi.h>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <image_transport/publisher.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <std_msgs/UInt8.h>
#include <camera_info_manager/camera_info_manager.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <yaml-cpp/yaml.h>


class ximea_driver{
	public:
	ximea_driver( int serial_no = 0 , std::string cam_name = ""); //if no serial no is specified select the first cam on the bus
	ximea_driver(std::string file_name);

	int readParamsFromFile(std::string file_name);
	void applyParameters();
	void errorHandling(XI_RETURN ret, std::string message);
	void enableTrigger(unsigned char trigger_mode);		//0 none, 1 soft_trigger, 2 hard_trigger_rising edge (unsupported)
	void limitBandwidth(int mbps);
	void openDevice();
	void closeDevice();
	void startAcquisition();
	void stopAcquisition();
	void acquireImage();
	void triggerDevice();
		
/*
	void readParamsFromFile(string file_name);
	int setTriggerMode();
	int setYamlURL();
	int setDownSampleFactor(int factor);
	int enableAutoExposure(bool enable);
	int enableBinning(bool enable);

*/
	int getSerialNo() const {return serial_no_;}
	virtual void setImageDataFormat(std::string s);	//this is virtual because the ros class needs to do a bit more work to publish the right image
	void setROI(int rect_left, int rect_top, int rect_width, int rect_height);
	//void setFrameRate(int rate);
	//void setBandWidth(int cams_on_bus);
	void setExposure(int time);

	bool hasValidHandle(){ return xiH_ == NULL ? false : true; }
	const XI_IMG& getImage()const{ return image_; }

	protected:

	void assignDefaultValues();

	//variables for ximea api internals
	std::string cam_name_;
	int serial_no_;

	int cams_on_bus_;
	int bandwidth_safety_margin_;
	int frame_rate_;

	int bandwidth_;
	
	int exposure_time_;
	bool auto_exposure_;

	bool binning_enabled_;
	int downsample_factor_;

	int rect_left_;
	int rect_top_;
	int rect_width_;
	int rect_height_;

	bool acquisition_active_;
	
	std::string image_data_format_; /*One of XI_MONO8, XI_RGB24, XI_RGB32, XI_RAW*/
	std::string yaml_url_; 
	HANDLE xiH_;
	XI_IMG image_;

	int image_capture_timeout_;	//max amount of time to wait for an image to come in
	unsigned char trigger_mode_;
	//variables for ros api internals
	
};
