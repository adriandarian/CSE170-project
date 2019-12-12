#pragma once

#include <vector>
#include <string>

#include <sig/sn_poly_editor.h>
#include <sig/sn_lines2.h>

#include <sigogl/ui_button.h>
#include <sigogl/ws_viewer.h>

#include <sigogl/ui_button.h>
#include <sigogl/ui_radio_button.h>
#include <sig/sn_primitive.h>
#include <sig/sn_transform.h>
#include <sig/sn_manipulator.h>

#include <sigogl/ws_run.h>

// Viewer for this example:
class MyViewer : public WsViewer
{
protected:
	enum MenuEv
	{
		EvNormals,
		EvAnimate,
		EvExit
	};
	UiCheckButton *_nbut;
	bool _animating;
	bool cameraMovement = true;
	float xTwoStoryHouse = 0.0, yTwoStoryHouse = 0.0, zTwoStoryHouse = 0.0;
	float xBody = 0.0, yBody = 0.0, zBody = 0.0;
	float xRightArm = 0.0, yRightArm = 0.0, zRightArm = 0.0;
	float xLeftArm = 0.0, yLeftArm = 0.0, zLeftArm = 0.0;
	float xFan = 0.0, yFan = 0.0, zFan = 0.0;
	std::vector<std::vector<float>> pos = {
		{xTwoStoryHouse, yTwoStoryHouse, zTwoStoryHouse},
		{xBody, yBody, zBody},
		{xRightArm, yRightArm, zRightArm},
		{xLeftArm, yLeftArm, zLeftArm},
		{xFan, yFan, zFan}
	};
	SnGroup *g = new SnGroup;
	// SnGroup *TwoStoryHouse = new SnGroup;
	SnGroup *Body = new SnGroup;
	SnGroup *LeftArm = new SnGroup;
	SnGroup *RightArm = new SnGroup;
	SnGroup *Fan = new SnGroup;
	SnModel *model[5];
	SnModel *scene;
	SnTransform *t[5];
	GsMat m[5];
	GsMat mt[5];
	GsBox b0, b1, b2, b3, b4;
	std::vector<GsBox> b = { b0, b1, b2, b3, b4};
	std::vector<std::string> pieces = {
		"mushroom-house.obj",
	};
	// std::vector<SnGroup *> sep = {
	// 	TwoStoryHouse,
	// };
	std::vector<int> numRotations = {6, 3, 6, 6, 6};

public:
	MyViewer(int x, int y, int w, int h, const char *l);
	void build_ui();
	void add_model(SnShape *s, GsVec p);
	void build_scene();
	void show_normals(bool view);
	void run_animation();
	virtual int handle_keyboard(const GsEvent &e) override;
	virtual int uievent(int e) override;
};
