#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		if (this->radius_list[i] > 0) {
		
			this->radius_list[i] += this->speed_list[i];
		}
		else {

			this->radius_list[i] += this->speed_list[i] * 20;
		}

		if (this->radius_list[i] > this->max_radius_list[i]) {

			this->location_list.erase(this->location_list.begin() + i);
			this->radius_list.erase(this->radius_list.begin() + i);
			this->speed_list.erase(this->speed_list.begin() + i);
			this->max_radius_list.erase(this->max_radius_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}

	ofColor color;
	for(int i = 0; i < 1; i++) 	{

		int random_deg = ofRandom(360);
		int random_radius = 250 + ofRandom(-20, 20);

		auto location = glm::vec2(random_radius * cos(random_deg * DEG_TO_RAD), random_radius * sin(random_deg * DEG_TO_RAD));
		this->location_list.push_back(location);
		this->radius_list.push_back(ofRandom(-600, -300));
		this->speed_list.push_back(ofRandom(0.1, 0.5));
		this->max_radius_list.push_back(ofRandom(15, 30));

		color.setHsb(ofMap(location.x, -270, 270, 0, 255), 255, 255);
		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		if (this->radius_list[i] > 0) {

			auto alpha = this->radius_list[i] < this->max_radius_list[i] * 0.8 ? 255 : ofMap(this->radius_list[i], this->max_radius_list[i] * 0.8, this->max_radius_list[i], 255, 64);
			ofSetColor(this->color_list[i], alpha);

			ofNoFill();
			ofDrawCircle(this->location_list[i], this->radius_list[i]);

			ofSetColor(this->color_list[i]);

			ofFill();
			ofDrawCircle(this->location_list[i], 2);
		}
		else {

			auto alpha = ofMap(this->radius_list[i], -600, 0, 64, 255);
			ofSetColor(this->color_list[i], alpha);

			ofNoFill();
			ofDrawLine(glm::vec3(this->location_list[i], this->radius_list[i]), glm::vec3(this->location_list[i], this->radius_list[i] - 20));
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}