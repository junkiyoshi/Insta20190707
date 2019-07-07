#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofRotate(90);

	auto radius_min = 110;
	auto radius_max = 180;
	auto radius_span = 8;

	for (int radius = radius_min; radius < radius_max; radius += radius_span) {

		ofColor color;
		color.setHsb(ofRandom(255), 180, 255);

		auto start_deg = ofGetFrameNum() * ofRandom(3, 8) + ofRandom(720);
		auto len = ofRandom(80, 360);

		vector<glm::vec2> vertices_in, vertices_out;
		auto first = true;
		for (int deg = start_deg; deg < start_deg + len; deg += 1) {

			int position_deg = deg % 720;
			if (position_deg < 360) {

				vertices_in.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)) + glm::vec2((radius_min + radius_max) * -0.5, -30));
				vertices_out.push_back(glm::vec2((radius + radius_span) * cos(deg * DEG_TO_RAD), (radius + radius_span) * sin(deg * DEG_TO_RAD)) + glm::vec2((radius_min + radius_max) * -0.5, 30));
			}
			else {

				int tmp_radius = ofMap(radius, radius_min, radius_max, radius_max, radius_min);
				vertices_in.push_back(glm::vec2(-1 * tmp_radius * cos(deg * DEG_TO_RAD), tmp_radius * sin(deg * DEG_TO_RAD)) + glm::vec2((radius_min + radius_max) * 0.5, -30));
				vertices_out.push_back(glm::vec2(-1 * (tmp_radius - radius_span) * cos(deg * DEG_TO_RAD), (tmp_radius - radius_span) * sin(deg * DEG_TO_RAD)) + glm::vec2((radius_min + radius_max) * 0.5, 30));
			}
		}

		reverse(vertices_out.begin(), vertices_out.end());

		ofFill();
		ofSetColor(color);
		ofBeginShape();
		ofVertices(vertices_in);
		ofVertices(vertices_out);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(39);
		ofBeginShape();
		ofVertices(vertices_in);
		ofVertices(vertices_out);
		ofEndShape(true);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}