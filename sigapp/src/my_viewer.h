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
	
	// Camera Global Variables
	bool cameraMovement = true;
	float cameraX = 0, cameraY = 0, cameraZ = 0, cameraAdjustment = 1000.0f;

	// Object Global Variables
	float xTwoStoryHouse = 0.0, yTwoStoryHouse = 0.0, zTwoStoryHouse = 0.0;

	std::vector<std::vector<float>> pos = {
		{xTwoStoryHouse, yTwoStoryHouse, zTwoStoryHouse},
	};
	SnGroup *g = new SnGroup;
	// SnGroup *TwoStoryHouse = new SnGroup;
	SnModel *model[5];
	SnModel *scene;
	SnTransform *t[5];
	GsMat m[5];
	GsMat mt[5];
	std::vector<std::string> pieces = {
		"mushroom-house.obj",
	};

public:
	MyViewer(int x, int y, int w, int h, const char *l);
	void build_ui();
	void add_model(SnShape *s, GsVec p);
	void build_scene();
	void show_normals(bool view);
	void move_camera_left();
	void move_camera_up();
	void move_camera_right();
	void move_camera_down();
	void camera_zoom_in();
	void camera_zoom_out();
	void run_animation();
	virtual int handle_keyboard(const GsEvent &e) override;
	virtual int uievent(int e) override;
};
