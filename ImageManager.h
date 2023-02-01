#pragma once
#include "ofxXmlSettings.h"
#include "ofxImGui.h"


//ENUM G£ÓWNY
enum CornerGrabb
{
	NOTHING,
	CENTRAL,
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT

};
struct MyStruct
{
	MyStruct() {}
	MyStruct(int newx, int newy)
	{
		x = newx;
		y = newy;
	}
	MyStruct& operator-(const MyStruct& other)const 
	{
		return MyStruct(x - other.x, y - other.y);

		
	}
	MyStruct& operator-=(const MyStruct& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;

	}
	MyStruct& operator+=(const MyStruct& other)
	{
		x += other.x;
		y += other.y;
		return *this;

	}
	int x;
	int y;
};


//=================================================================================================================
//DEKLARACJA KLASY MANAGERA
class ImageManager
{
public:
	ImageManager() {};
	ImageManager(ofImage &imgTempVal);


	ofImage *imgVal;



	bool keepProportion16to9 = false;
	bool keepProportion9to16 = false;

//==============================================================================================================
	void draw();
	bool myInside(ofRectangle req, int x, int y);
	void update(ofEventArgs& args);
	void drawRects();
	void mouseReleased(const int& x, const int& y, const int& button);
	void mousePressed(ofMouseEventArgs& mouse);

	void mouseDragged(ofMouseEventArgs& args);
	//void mouseMoved(ofMouseEventArgs& args);
	void drawGui();

	void imageSettingsSaver();
	void imageSettingsLoader();
	void SettingsScroller();//testowy scroller do wypisywania zapisanych ustawien do wyboru


//===============================================================================================================
public:
	//ofVec2f startGrabPos;
	MyStruct startGrabPos;
	MyStruct grabbedImageSize = MyStruct(500, 500);
	MyStruct imagePosition = MyStruct(100, 100);
	int rectSize = 50.0f;
	
	ofRectangle topLeftGrabIndicator = ofRectangle(0.0f, 0.0f, rectSize, rectSize);
	ofRectangle topRightGrabIndicator = ofRectangle(0.0f, 0.0f, rectSize, rectSize);
	ofRectangle bottomLeftGrabIndicator = ofRectangle(0.0f, 0.0f, rectSize, rectSize);
	ofRectangle bottomRightGrabIndicator = ofRectangle(0.0f, 0.0f, rectSize, rectSize);
	ofRectangle centralGrabIndicator = ofRectangle();

	CornerGrabb cornerGrabb = NOTHING;
	CornerGrabb overGrabPoint = NOTHING;

	ofxXmlSettings imgSettingsSaver;


	bool bManualMode = true;

	int scaleX = 680;
	int scaleY = 470;

	int imagePosGui[4];
	std::string settingsID;
	ofVec2f appSize = ofVec2f(1024, 768);
};

