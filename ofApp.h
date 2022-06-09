#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	void setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float size);
	void setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float height, float width, float depth);

	ofEasyCam cam;
	ofMesh face_mesh, frame_mesh, sphere_mesh, draw_sphere_mesh;

	float noise_param_1, noise_param_2;
};