#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(1);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(150, 4);
	this->sphere_mesh = ico_sphere.getMesh();
	this->frame_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	this->noise_param_1 = ofRandom(1000);
	this->noise_param_2 = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 90 < 45) {

		this->noise_param_1 += ofMap(ofGetFrameNum() % 90, 0, 45, 0.15, 0);
	}
	else {

		this->noise_param_2 += ofMap(ofGetFrameNum() % 90, 45, 90, 0.15, 0);
	}

	this->face_mesh.clear();
	this->frame_mesh.clear();

	this->draw_sphere_mesh = this->sphere_mesh;

	for (auto& vertex : this->draw_sphere_mesh.getVertices()) {

		auto noise_value = ofNoise(glm::vec4(vertex * 0.01, noise_param_1));
		auto noise_radius = ofMap(noise_value, 0, 1, 65, 135);

		vertex = glm::normalize(vertex) * noise_radius;
	}

	auto span = 8;
	auto max_height = 150;
	auto radius = 250;
	for (auto x = -300; x <= 300; x += span) {

		for (auto y = -300; y <= 300; y += span) {

			auto distance = glm::length(glm::vec2(x, y));
			if (distance > radius - 20 && distance < radius + 20) {

				auto power = ofMap(abs(distance - radius), 0, 20, 1, 0.1);
				auto len = ofMap(ofNoise(x * 0.05, y * 0.05, noise_param_2), 0, 1, 0, max_height * power);
				this->setBoxToMesh(this->face_mesh, this->frame_mesh, glm::vec3(x, y, len * 0.5), span, span, len);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofTranslate(0, -50, 0);
	ofRotateX(285);

	ofPushMatrix();
	ofTranslate(glm::vec3(0, 0, 200));
	
	ofSetColor(0);
	this->draw_sphere_mesh.draw();
	ofSetColor(255, 0, 0);
	this->draw_sphere_mesh.drawWireframe();

	ofPopMatrix();

	this->face_mesh.drawFaces();
	this->frame_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float size) {

	this->setBoxToMesh(face_target, frame_target, location, size, size, size);
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float height, float width, float depth) {

	auto face_color = ofColor(0);
	auto frame_color = ofColor(255, 0, 0);

	int index = face_target.getVertices().size();

	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99));

	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99));

	for (int i = 0; i < 8; i++) {

		face_target.addColor(face_color);
	}

	face_target.addIndex(index + 0); face_target.addIndex(index + 1); face_target.addIndex(index + 2);
	face_target.addIndex(index + 0); face_target.addIndex(index + 2); face_target.addIndex(index + 3);

	face_target.addIndex(index + 4); face_target.addIndex(index + 5); face_target.addIndex(index + 6);
	face_target.addIndex(index + 4); face_target.addIndex(index + 6); face_target.addIndex(index + 7);

	face_target.addIndex(index + 0); face_target.addIndex(index + 4); face_target.addIndex(index + 1);
	face_target.addIndex(index + 4); face_target.addIndex(index + 5); face_target.addIndex(index + 1);

	face_target.addIndex(index + 1); face_target.addIndex(index + 5); face_target.addIndex(index + 6);
	face_target.addIndex(index + 6); face_target.addIndex(index + 2); face_target.addIndex(index + 1);

	face_target.addIndex(index + 2); face_target.addIndex(index + 6); face_target.addIndex(index + 7);
	face_target.addIndex(index + 7); face_target.addIndex(index + 3); face_target.addIndex(index + 2);

	face_target.addIndex(index + 3); face_target.addIndex(index + 7); face_target.addIndex(index + 4);
	face_target.addIndex(index + 4); face_target.addIndex(index + 0); face_target.addIndex(index + 3);

	frame_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * 0.5));
	frame_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * 0.5));

	frame_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * 0.5));
	frame_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * 0.5));

	for (int i = 0; i < 8; i++) {

		frame_target.addColor(frame_color);
	}

	frame_target.addIndex(index + 0); frame_target.addIndex(index + 1);
	frame_target.addIndex(index + 1); frame_target.addIndex(index + 2);
	frame_target.addIndex(index + 2); frame_target.addIndex(index + 3);
	frame_target.addIndex(index + 3); frame_target.addIndex(index + 0);

	frame_target.addIndex(index + 4); frame_target.addIndex(index + 5);
	frame_target.addIndex(index + 5); frame_target.addIndex(index + 6);
	frame_target.addIndex(index + 6); frame_target.addIndex(index + 7);
	frame_target.addIndex(index + 7); frame_target.addIndex(index + 4);

	frame_target.addIndex(index + 0); frame_target.addIndex(index + 4);
	frame_target.addIndex(index + 1); frame_target.addIndex(index + 5);
	frame_target.addIndex(index + 2); frame_target.addIndex(index + 6);
	frame_target.addIndex(index + 3); frame_target.addIndex(index + 7);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}