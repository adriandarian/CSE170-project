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
	float cameraX = 0, cameraY = 0, cameraZ = 0, cameraAdjustment = 10.0f;

	// Bounding Box
	GsBox house1, house2;

	// Shadow Global Variables
	GsMat shadowPoints = {
		1, // visibility?
		0, // rotate across z-axis
		0, // shift across the x-axis
		0, // Does nothing to the shadow

		0, // shift across y-axis and rotate across y-axis
		0, // rotate across y-axis
		0, // ?
		0, // Does nothing to the shadow

		// Leave alone for the shadow to be mounted to the Objects
		0,  // ?
		-1, // stretches across the z-axis
		1,  // ?
		0,  // ?

		// Do Not Touch - Messes with the whole shadow
		0, // ?
		0, // ?
		0, // ?
		1  // ?
	};

	// Object Global Variables
	float xTwoStoryHouse = 0.0,
		  yTwoStoryHouse = 0.0, zTwoStoryHouse = 0.0;
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

	GsVec mover = GsVec(0.0f, 0.0f, 0.0f);
	GsVec mover1 = GsVec(4.4f, 4.4f, 0.0f);
	GsVec mover2 = GsVec(4.4f, 0.0f, 0.0f);
	GsVec mover3 = GsVec(0.0f, 4.4f, 0.0f);
	GsVec mover4 = GsVec(0.0f, 8.8f, 0.0f);
	GsVec mover5 = GsVec(8.8f, 8.8f, 0.0f);
	GsVec mover6 = GsVec(8.8f, 0.0f, 0.0f);
	GsVec mover7 = GsVec(4.4f, 8.8f, 0.0f);
	GsVec mover8 = GsVec(8.8f, 4.4f, 0.0f);

	GsMat gsMario;
	SnModel *snMario;
	SnManipulator *maManip;

	GsMat gsMario1;
	SnModel *snMario1;
	SnManipulator *maManip1;

	GsMat gsMario2;
	SnModel *snMario2;
	SnManipulator *maManip2;

	GsMat gsMario3;
	SnModel *snMario3;
	SnManipulator *maManip3;

	GsMat gsMario4;
	SnModel *snMario4;
	SnManipulator *maManip4;

	GsMat gsMario5;
	SnModel *snMario5;
	SnManipulator *maManip5;

	GsMat gsMario6;
	SnModel *snMario6;
	SnManipulator *maManip6;

	GsMat gsMario7;
	SnModel *snMario7;
	SnManipulator *maManip7;

	GsMat gsMario8;
	SnModel *snMario8;
	SnManipulator *maManip8;

	bool up;
	bool down;
	bool left;
	bool right;

public:
	MyViewer(int x, int y, int w, int h, const char *l);
	void build_ui();
	void add_model(SnShape *s, GsVec p);
	void build_scene();
	void show_normals(bool view);
	void move_camera_right();
	void move_camera_left();
	void move_camera_up();
	void move_camera_down();
	void camera_zoom_in();
	void camera_zoom_out();
	void rotate_camera_right();
	void rotate_camera_left();
	void move_sun_right();
	void move_sun_left();
	void move_sun_up();
	void move_sun_down();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void jumpUp();
	void jumpDown();
	void run_animation();
	virtual int handle_keyboard(const GsEvent &e) override;
	virtual int uievent(int e) override;
};
