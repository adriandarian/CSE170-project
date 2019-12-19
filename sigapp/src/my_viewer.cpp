#include "my_viewer.h"

#include <sigogl/ui_button.h>
#include <sigogl/ui_radio_button.h>
#include <sig/sn_primitive.h>
#include <sig/sn_transform.h>
#include <sig/sn_manipulator.h>

#include <sigogl/ws_run.h>

MyViewer::MyViewer(int x, int y, int w, int h, const char *l) : WsViewer(x, y, w, h, l)
{
	_nbut = 0;
	_animating = false;
	cameraX = camera().center.x;
	cameraY = camera().center.y;
	cameraZ = camera().center.z;

	build_ui();
	build_scene();
}

void MyViewer::build_ui()
{
	UiPanel *p, *sp;
	UiManager *uim = WsWindow::uim();
	p = uim->add_panel("", UiPanel::HorizLeft);
	p->add(new UiButton("View", sp = new UiPanel()));
	{
		UiPanel *p = sp;
		p->add(_nbut = new UiCheckButton("Normals", EvNormals));
	}
	p->add(new UiButton("Animate", EvAnimate));
	p->add(new UiButton("Exit", EvExit));
	p->top()->separate();
}

void MyViewer::add_model(SnShape *s, GsVec p)
{
	SnManipulator *manip = new SnManipulator;
	GsMat m;
	m.translation(p);
	manip->initial_mat(m);
	SnManipulator *shadow = new SnManipulator;
	GsMat shad;

	shad.set(shadowPoints);
	shad.rcombtrans(p);

	shadow->initial_mat(shad);

	SnGroup *g = new SnGroup;
	SnLines *l = new SnLines;
	l->color(GsColor::orange);
	g->add(s);
	g->add(l);
	manip->child(g);
	shadow->child(g);
	rootg()->add(manip);
	rootg()->add(shadow);

	rootg()->add(manip);
}

void MyViewer::build_scene()
{
	// Re-initialize the scene before drawing.
	rootg()->remove_all();

	// SnModel *Grass = new SnModel; //grass
	// if (!Grass->model()->load("../src/Objects/grassPatch.obj"))
	// {
	// 	gsout << "Grass was not loaded" << gsnl;
	// }
	// Grass->color(GsColor::green);
	// GsModel *GrassModel = Grass->model();
	// GrassModel->scale(10000);
	// rootg()->add(Grass);

	SnModel *TwoStoryHouse = new SnModel;
	if (!TwoStoryHouse->model()->load("../src/Objects/mushroom-house.obj"))
	{
		gsout << "TwoStoryHouse was not loaded" << gsnl;
	}
	// TwoStoryHouse->color(GsColor::green);
	GsModel *TwoStoryHouseModel = TwoStoryHouse->model();
	TwoStoryHouse->model()->get_bounding_box(house1);
	TwoStoryHouseModel->scale(1);
	add_model(TwoStoryHouse, GsVec(xTwoStoryHouse, yTwoStoryHouse, zTwoStoryHouse));

	SnModel *TwoStoryHouse1 = new SnModel;
	if (!TwoStoryHouse1->model()->load("../src/Objects/mushroom-house.obj"))
	{
		gsout << "TwoStoryHouse was not loaded" << gsnl;
	}
	// TwoStoryHouse->color(GsColor::green);
	GsModel *TwoStoryHouseModel1 = TwoStoryHouse1->model();
	TwoStoryHouseModel1->scale(1);
	//add_model(TwoStoryHouse1, GsVec(20000.0F, 0.0F, 20000.0F));

	SnModel *TwoStoryHouse3 = new SnModel;
	if (!TwoStoryHouse3->model()->load("../src/Objects/mushroom-house.obj"))
	{
		gsout << "TwoStoryHouse was not loaded" << gsnl;
	}
	// TwoStoryHouse->color(GsColor::green);
	GsModel *TwoStoryHouseModel3 = TwoStoryHouse3->model();
	TwoStoryHouseModel3->scale(1);
	add_model(TwoStoryHouse3, GsVec(-20000.0f, 0.0f, 0.0f));

	//this one is sideways

	//SnModel* House = new SnModel;
	//if (!House->model()->load("../src/Objects/20951_Mushroom_v2_NEW.obj")) {
	//	gsout << "house was not loaded" << gsnl;
	//}
	//// TwoStoryHouse->color(GsColor::green);
	//GsModel* House1 = House->model();
	//House1->scale(3000);
	//add_model(House, GsVec(-20000.0f, 10.0f, 30000.0f));
}

void MyViewer::move_camera_right()
{
	camera().translate(GsVec(cameraX - cameraAdjustment, cameraY, cameraZ));
	render();
	ws_check();
}

void MyViewer::move_camera_left()
{
	camera().translate(GsVec(cameraX + cameraAdjustment, cameraY, cameraZ));
	render();
	ws_check();
}

void MyViewer::move_camera_up()
{
	camera().translate(GsVec(cameraX, cameraY - cameraAdjustment, cameraZ));
	render();
	ws_check();
}

void MyViewer::move_camera_down()
{
	camera().translate(GsVec(cameraX, cameraY + cameraAdjustment, cameraZ));
	render();
	ws_check();
}

void MyViewer::camera_zoom_in()
{
	camera().translate(GsVec(cameraX, cameraY, cameraZ - cameraAdjustment));
	render();
	ws_check();
}

void MyViewer::camera_zoom_out()
{
	camera().translate(GsVec(cameraX, cameraY, cameraZ + cameraAdjustment));
	render();
	ws_check();
}

void MyViewer::move_sun_right()
{
	shadowPoints[1] += 1;
	render();
	ws_check();
}

void MyViewer::move_sun_left()
{
	shadowPoints[1] -= 1;
	render();
	ws_check();
}

void MyViewer::move_sun_up() {
	shadowPoints[9] += 1;
	render();
	ws_check();
}

void MyViewer::move_sun_down() {
	shadowPoints[9] -= 1;
	render();
	ws_check();
}

// Below is an example of how to control the main loop of an animation:
void MyViewer::run_animation()
{
	if (_animating) return; // avoid recursive calls
	_animating = true;

	double frdt = 1.0 / 30.0; // delta time to reach given number of frames per second
	double time = 0, lt = 0, t0 = gs_time();
	do // run for a while:
	{
		while (time - lt < frdt) { ws_check(); time = gs_time() - t0; } // wait until it is time for next frame
		lt = time;
		if (time < 20) {
			if (time < 1) {
				camera().translate(GsVec(cameraX , cameraY, cameraZ - cameraAdjustment));
				render();
				ws_check();
			}
			if (time > 1 && time < 6) {
				//camera().rotate(GsQuat(0.0f, 0.0f, 0.0f, 0.005f));
				render();
				ws_check();
			}
		}
	} while (time < 30);
	_animating = false;
}

void MyViewer::show_normals(bool view)
{
	// Note that primitives are only converted to meshes in GsModel
	// at the first draw call.
	GsArray<GsVec> fn;
	SnGroup *r = (SnGroup *)root();
	for (int k = 0; k < r->size(); k++)
	{
		SnManipulator *manip = r->get<SnManipulator>(k);
		SnShape *s = manip->child<SnGroup>()->get<SnShape>(0);
		SnLines *l = manip->child<SnGroup>()->get<SnLines>(1);
		if (!view)
		{
			l->visible(false);
			continue;
		}
		l->visible(true);
		if (!l->empty())
			continue; // build only once
		l->init();
		if (s->instance_name() == SnPrimitive::class_name)
		{
			GsModel &m = *((SnModel *)s)->model();
			m.get_normals_per_face(fn);
			const GsVec *n = fn.pt();
			float f = 0.33f;
			for (int i = 0; i < m.F.size(); i++)
			{
				const GsVec &a = m.V[m.F[i].a];
				l->push(a, a + (*n++) * f);
				const GsVec &b = m.V[m.F[i].b];
				l->push(b, b + (*n++) * f);
				const GsVec &c = m.V[m.F[i].c];
				l->push(c, c + (*n++) * f);
			}
		}
	}
}

int MyViewer::handle_keyboard(const GsEvent &e)
{
	int ret = WsViewer::handle_keyboard(e); // 1st let system check events
	bool update = false;

	if (ret)
		return ret;

	// for Debug mode only
	// gsout << "Camera: " << camera() << gsnl;
	gsout << "Shadow: ";
	for (int i = 0; i < sizeof(shadowPoints)/sizeof(shadowPoints[0]); i++) {
		if (i%4 == 0) gsnl;
		gsout << shadowPoints[i] << ", ";
	}

	switch (e.key)
	{
	case GsEvent::KeyEsc:
		gs_exit();
		return 1;
	case 'n':
	{
		bool b = !_nbut->value();
		_nbut->value(b);
		show_normals(b);
		return 1;
	}
	case GsEvent::KeyLeft:
	{	if (camera().center.x <= house1.dx() && camera().center.z <= house1.dz() && camera().center.x >= house1.dx() - 1000.0f && camera().center.z >= house1.dz() - 1000.0f) {
		gsout << house1.dz() << "," << house1.dx() << gsnl;
		return 1;
		}
	else {
		move_camera_left();
		return 1;
		}
	}
	case GsEvent::KeyUp:
	{
		move_camera_up();
		return 1;
	}
	case GsEvent::KeyRight:
	{
		move_camera_right();
		return 1;
	}
	case GsEvent::KeyDown:
	{
		move_camera_down();
		return 1;
	}
	case 'q':
	{	if (camera().center.z >= house1.dz() - 70000.0f) {
			camera_zoom_in();
			
		}
		return 1;
	}
	case 'e':
	{
		camera_zoom_out();
		return 1;
	}
	case 'w':
	{
		move_sun_up();
		return 1;
	}
	case 'a':
	{
		move_sun_left();
		return 1;
	}
	case 's':
	{
		move_sun_down();
		return 1;
	}
	case 'd':
	{
		move_sun_right();
		return 1;
	}
	default:
		gsout << "Key pressed: " << e.key << gsnl;
	}

	// if ( update )
	// {	_gLight->get<SnTransform>(0)->get().setrans(lightPos);
	// 	update_shadow ();
	// }

	return 0;
}

int MyViewer::uievent(int e)
{
	switch (e)
	{
	case EvNormals:
		show_normals(_nbut->value());
		return 1;
	case EvAnimate:
		run_animation();
		return 1;
	case EvExit:
		gs_exit();
	}
	return WsViewer::uievent(e);
}