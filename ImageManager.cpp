#include "ImageManager.h"



ImageManager::ImageManager(ofImage& imgTempVal)
{
	imgVal = &imgTempVal;
	imgVal->loadImage("v.png");
	ofAddListener(ofEvents().mousePressed, this, &ImageManager::mousePressed);
	ofAddListener(ofEvents().update, this, &ImageManager::update);
	//ofAddListener(ofEvents().draw, this, & ImageManager::draw);
	ofAddListener(ofEvents().mouseDragged, this, &ImageManager::mouseDragged);
	//ofAddListener(ofEvents().mouseMoved, this, &ImageManager::mouseMoved);
	
}
void ImageManager::draw()
{
	std::cout << "beta";
	if (imgVal) {
		std::cout << "alfa";
		imgVal->draw(imagePosition.x, imagePosition.y, grabbedImageSize.x, grabbedImageSize.y);
		std::cout << "gamma";
		//imgVal->draw(20,20 , 50, 50);
		
	}
	if (bManualMode) {
		drawRects();
	}
}

bool ImageManager::myInside(ofRectangle req, int x, int y)
{
	if (x >= req.x && x <= req.x + req.width)
	{
		
		if (y >= req.y && y <= req.y + req.height)
		{
			return true;
		}
	}
	return false;
}

void ImageManager::update(ofEventArgs &args)
{
	
	if (bManualMode) {
		topLeftGrabIndicator.setPosition(imagePosition.x, imagePosition.y);
		//topLeftGrabIndicator.set(imagePosition.x - rectSize/2, imagePosition.y - rectSize/2, rectSize, rectSize);
		topRightGrabIndicator.setPosition(imagePosition.x - topRightGrabIndicator.width + grabbedImageSize.x, imagePosition.y);
		bottomLeftGrabIndicator.setPosition(imagePosition.x, imagePosition.y + grabbedImageSize.y - bottomLeftGrabIndicator.width);
		bottomRightGrabIndicator.setPosition(imagePosition.x - bottomRightGrabIndicator.width + grabbedImageSize.x, imagePosition.y + grabbedImageSize.y - bottomRightGrabIndicator.width);
	}
}

void ImageManager::drawRects() //drawRects jest w wewnatrz zwyklego draw
{
	ofSetColor(255, 0, 0);
	ofNoFill();
	ofDrawRectangle(topLeftGrabIndicator);
	ofDrawRectangle(topRightGrabIndicator);
	ofDrawRectangle(bottomLeftGrabIndicator);
	ofDrawRectangle(bottomRightGrabIndicator);

	//ofDrawCircle(topLeftGrabIndicator.x, topLeftGrabIndicator.y, 50);

	ofSetColor(255, 255, 255);
}

void ImageManager::mouseReleased(const int& x, const int& y, const int& button) //nie uzywane
{
}

void ImageManager::mousePressed(ofMouseEventArgs& mouse)
{
	// sprawdzilem juz wszystkie opcje i zawsze wywala sie tutaj niezaleznie od tego czy jest 
	// zastosowany ofvec2f czy moja customowa struktura, na ten moment juz nie wiem co moze powodowac ten blad
	int x = mouse.x;
	int y = mouse.y;
	

	

	startGrabPos = MyStruct(x, y);
	
	
	centralGrabIndicator = ofRectangle(imagePosition.x ,imagePosition.y, grabbedImageSize.x, grabbedImageSize.y);
	
	if (myInside(topLeftGrabIndicator, x, y)) {
		cornerGrabb = TOP_LEFT;
		
	}
	else if (myInside(topRightGrabIndicator, x, y)) {
		cornerGrabb = TOP_RIGHT;
		
	}
	else if (myInside(bottomLeftGrabIndicator, x, y)) {
		cornerGrabb = BOTTOM_LEFT;
		
	}
	else if (myInside(bottomRightGrabIndicator, x, y)) {
		cornerGrabb = BOTTOM_RIGHT;
		
	}
	else if (myInside(centralGrabIndicator, x, y)) {
		cornerGrabb = CENTRAL;

		

	}
	else {
		cornerGrabb = NOTHING;
	}
	
}
void ImageManager::mouseDragged(ofMouseEventArgs& args)
{
	int x = args.x;
	int y = args.y;

	if (bManualMode) {
		switch (cornerGrabb)
		{
		case NOTHING:
		{

		}
		break;

		case CENTRAL:
		{
			MyStruct grabDistance = startGrabPos - MyStruct(x, y);
			imagePosition -= grabDistance;
			startGrabPos -= grabDistance;
		}
		break;

		case TOP_LEFT:
		{
			MyStruct grabDistance = startGrabPos - MyStruct(x, y);
			grabbedImageSize += grabDistance;
			startGrabPos -= grabDistance;

			if (keepProportion16to9) {
				imagePosition.x -= grabDistance.x;
				imagePosition.y -= grabDistance.x * 9 / 16;
			}
			else if (keepProportion9to16)
			{
				imagePosition.x -= grabDistance.y * 9 / 16;
				imagePosition.y -= grabDistance.y;
			}
			else {
				imagePosition -= grabDistance;
			}
		}
		break;
		case TOP_RIGHT:
		{
			MyStruct grabDistance = startGrabPos - MyStruct(x, y);
			grabbedImageSize.x -= grabDistance.x;
			grabbedImageSize.y += grabDistance.y;
			startGrabPos -= grabDistance;


			if (keepProportion16to9) {
				imagePosition.y += grabDistance.x * 9 / 16;
			}
			else if (keepProportion9to16)
			{
				imagePosition.y -= grabDistance.y;
			}
			else {
				imagePosition.y -= grabDistance.y;
			}
		}
		break;
		case BOTTOM_LEFT:
		{

			MyStruct grabDistance = startGrabPos - MyStruct(x, y);
			grabbedImageSize.x += grabDistance.x;
			grabbedImageSize.y -= grabDistance.y;
			startGrabPos -= grabDistance;


			if (keepProportion9to16)
			{
				imagePosition.x += grabDistance.y * 9 / 16;
			}
			else
			{
				imagePosition.x -= grabDistance.x;
			}
		}
		break;
		case BOTTOM_RIGHT:
		{
			MyStruct grabDistance = startGrabPos - MyStruct(x, y);
			grabbedImageSize -= grabDistance;
			startGrabPos -= grabDistance;
		}
		break;
		default:

			break;
		}

		if (keepProportion16to9)
		{
			grabbedImageSize.y = grabbedImageSize.x * 9 / 16;
		}
		else if (keepProportion9to16)
		{
			grabbedImageSize.x = grabbedImageSize.y * 9 / 16;
		}
	}
}
//void ImageManager::mouseMoved(ofMouseEventArgs& args)
//{
//	int x = args.x;
//	int y = args.y;
//	overGrabPoint = NOTHING;
//
//	if (topLeftGrabIndicator.inside(x, y)) {
//		//overGrabPoint = TOP_LEFT;
//	}
//	else if (topRightGrabIndicator.inside(x, y)) {
//		//overGrabPoint = TOP_RIGHT;
//	}
//	else if (bottomLeftGrabIndicator.inside(x, y)) {
//		//overGrabPoint = BOTTOM_LEFT;
//	}
//	else if (bottomRightGrabIndicator.inside(x, y)) {
//		//overGrabPoint = BOTTOM_RIGHT;
//	}
//}
void ImageManager::drawGui()
{
	SettingsScroller(); //experymentalny scroller
	ofVec2f size1(300,60);
	ofVec2f size2(300, 200);
	ImGui::BeginChild("imageManagerGui", size2);
	
	if (ImGui::Checkbox("Keep Proportion 16:9", &keepProportion16to9))
	{
		keepProportion9to16 = false;
	}
	if (ImGui::Checkbox("Keep Proportion 9:16", &keepProportion9to16))
	{
		keepProportion16to9 = false;
	}
	if (ImGui::Checkbox("Keep Proportion 3:2", &keepProportion9to16))
	{
		keepProportion9to16 = false;
		keepProportion16to9 = false;
	}

	ImGui::BeginChild("EnterScale", size1);
	ImGui::InputInt("Scale X", &scaleX);
	ImGui::InputInt("Scale Y", &scaleY);
	
	if (ImGui::Button("ApplyScale"))
	{
		keepProportion16to9 = false;
		keepProportion9to16 = false;

		grabbedImageSize.x = scaleX;
		grabbedImageSize.y = scaleY;
	}
	ImGui::EndChild();

	ImGui::Checkbox("manual mode", &bManualMode);
	ImGui::DragInt("rect size", &rectSize, 1, 1, 100);
	if (ImGui::DragInt4("img pos & size", imagePosGui, 1, 1, 10000)) {

		imagePosition.x = imagePosGui[0];
		imagePosition.y = imagePosGui[1];
		grabbedImageSize.x = imagePosGui[2];
		grabbedImageSize.y = imagePosGui[3];
	}
	if (ImGui::Button("center x")) {
		// jaki jest rozmiar monitora/

		imagePosition.x = (appSize.x / 2 - grabbedImageSize.x / 2);
		imagePosGui[0] = imagePosition.x;
	}
	ImGui::SameLine();
	if (ImGui::Button("center y")) {

		imagePosition.y = (appSize.y / 2 - grabbedImageSize.y / 2);
		imagePosGui[1] = imagePosition.y;
	}
	ImGui::SameLine();
	if (ImGui::Button("center all")) {
		imagePosition.x = (appSize.x / 2 - grabbedImageSize.x / 2);
		imagePosGui[0] = imagePosition.x;

		imagePosition.y = (appSize.y / 2 - grabbedImageSize.y / 2);
		imagePosGui[1] = imagePosition.y;
	}
	
	ImGui::EndChild();
}
void ImageManager::imageSettingsSaver()
{	//POMYSL JAK TO ZROBIC !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//zapis ustawien do xml ktore sie spodobaly uzytkownikowi tak by pozniej wyswietlaly sie w rozwijanej liscie do wyboru przez uzytkownika
	//=====================================================================================================================
	
	std::string settingsVal = settingsID + ".xml";

	imgSettingsSaver.setValue("settings:scallableImageSettings:sizeX", grabbedImageSize.x);
	imgSettingsSaver.setValue("settings:scallableImageSettings:sizeY", grabbedImageSize.y);//ustawienia rozdzielczosci obrazu
	imgSettingsSaver.setValue("settings:scallableImageSettings:posX", imagePosition.x);
	imgSettingsSaver.setValue("settings:scallableImageSettings:posY", imagePosition.y);//ustawienia pozycji obrazu w oknie OF
	imgSettingsSaver.setValue("settings:scallableImageSettings:ID", settingsID);

	imgSettingsSaver.saveFile(settingsVal); //jak sie chce podac miejsce inne niz "data" miejsce zapisu to nalezy podac nazwe wraz ze sciezka
}
void ImageManager::imageSettingsLoader()
{	
	std::string settingsVal = settingsID + ".xml";
	if (imgSettingsSaver.loadFile(settingsVal)) 
	{
		grabbedImageSize.x = imgSettingsSaver.getValue("settings:scallableImageSettings:sizeX", 680);
			grabbedImageSize.y = imgSettingsSaver.getValue("settings:scallableImageSettings:sizeY", 680);
			imagePosition.x = imgSettingsSaver.getValue("settings:scallableImageSettings:posX", 680);
			imagePosition.y = imgSettingsSaver.getValue("settings:scallableImageSettings:posY", 680);
			settingsID = imgSettingsSaver.getValue("settings:scallableImageSettings:ID", 0);
			//cos tu jest nie tak(czemu imgSettingsSaver jak to jest load), zapytac zn zn

			imagePosGui[0] = imagePosition.x;
			imagePosGui[1] = imagePosition.y;
			imagePosGui[2] = grabbedImageSize.x;
			imagePosGui[3] = grabbedImageSize.y;
	}
}
void ImageManager::SettingsScroller()
{
	
	ofVec2f size(200,50);
	ImGui::Begin;
	//ImGui::BeginChild("",size);
	//to moze byc nie potrzebne, po co to castowac jak itak do petli potrzeba tego liczby//int numValID = stoi(settingsID);

	//for (int n = 0; n < 10; n++)
		
		//ImGui::Text("ID", settingsID);
	
	//ImGui::EndChild();*/
	


	
		
	
		
		//for (int n = 0; n < val; n++) {
		//	bool isSelected = false;
		//	//bool is_selected = (current_item == val);
		//	//ImGui::Text("ID", settingsID);
		//	/*if (ImGui::Selectable("id", isSelected)
		//	{
		//		ImGui::Button("id", size);
		//	}*/
		//}
		const char* arrayVal[10] = { "1","2","3","4","5","6","7","8","9","10" };
		static const char* current_item = NULL;
		if (ImGui::BeginCombo("##combo", current_item))
		{
			
			for (int n = 0; n < IM_ARRAYSIZE(arrayVal); n++)
			{
				bool is_selected = (current_item == arrayVal[n]); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(arrayVal[n], is_selected)) 
				{
					current_item = arrayVal[n];
				}
				if (is_selected) 
				{
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)

				}
			}
			ImGui::EndCombo;
		}
		ImGui::End;
	
	//ImGui::EndChild();
	ImGui::End;
};