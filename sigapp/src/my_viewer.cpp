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

	maManip = new SnManipulator;
	maManip1 = new SnManipulator;
	maManip2 = new SnManipulator;
	maManip3 = new SnManipulator;
	maManip4 = new SnManipulator;
	maManip5 = new SnManipulator;
	maManip6 = new SnManipulator;
	maManip7 = new SnManipulator;
	maManip8 = new SnManipulator;

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

void MyViewer::add_model(SnShape *shape, GsVec point)
{
	SnManipulator *manipulator = new SnManipulator;
	GsMat matrix;
	matrix.translation(point);
	manipulator->initial_mat(matrix);
	SnManipulator *ShadowManipulator = new SnManipulator;
	GsMat ShadowMatrix;

	ShadowMatrix.set(shadowPoints);
	ShadowMatrix.rcombtrans(point);

	ShadowManipulator->initial_mat(ShadowMatrix);

	SnGroup *group = new SnGroup;
	SnLines *lines = new SnLines;
	lines->color(GsColor::orange);
	group->add(shape);
	group->add(lines);
	manipulator->child(group);
	// ShadowManipulator->child(group);
	rootg()->add(manipulator);
	// rootg()->add(ShadowManipulator);

	rootg()->add(manipulator);
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

	// SnModel *TwoStoryHouse = new SnModel;
	// if (!TwoStoryHouse->model()->load("../src/Objects/mushroom-house.obj"))
	// {
	// 	gsout << "TwoStoryHouse was not loaded" << gsnl;
	// }
	// // TwoStoryHouse->color(GsColor::green);
	// GsModel *TwoStoryHouseModel = TwoStoryHouse->model();
	// TwoStoryHouse->model()->get_bounding_box(house1);
	// TwoStoryHouseModel->scale(1);
	// add_model(TwoStoryHouse, GsVec(xTwoStoryHouse, yTwoStoryHouse, zTwoStoryHouse));

	// SnModel *TwoStoryHouse1 = new SnModel;
	// if (!TwoStoryHouse1->model()->load("../src/Objects/mushroom-house.obj"))
	// {
	// 	gsout << "TwoStoryHouse was not loaded" << gsnl;
	// }
	// // TwoStoryHouse->color(GsColor::green);
	// GsModel *TwoStoryHouseModel1 = TwoStoryHouse1->model();
	// TwoStoryHouseModel1->scale(1);
	// //add_model(TwoStoryHouse1, GsVec(20000.0F, 0.0F, 20000.0F));

	// SnModel *TwoStoryHouse3 = new SnModel;
	// if (!TwoStoryHouse3->model()->load("../src/Objects/mushroom-house.obj"))
	// {
	// 	gsout << "TwoStoryHouse was not loaded" << gsnl;
	// }
	// // TwoStoryHouse->color(GsColor::green);
	// GsModel *TwoStoryHouseModel3 = TwoStoryHouse3->model();
	// TwoStoryHouseModel3->scale(1);
	// add_model(TwoStoryHouse3, GsVec(-20000.0f, 0.0f, 0.0f));

	SnModel *TwoStoryHouse = new SnModel;
	if (!TwoStoryHouse->model()->load("../src/Objects/villagefinal3.obj"))
	{
		gsout << "TwoStoryHouse was not loaded" << gsnl;
	}
	// TwoStoryHouse->color(GsColor::green);
	GsModel *TwoStoryHouseModel = TwoStoryHouse->model();
	TwoStoryHouse->model()->get_bounding_box(house1);
	TwoStoryHouseModel->scale(1);
	add_model(TwoStoryHouse, GsVec(xTwoStoryHouse, yTwoStoryHouse, zTwoStoryHouse));

	// snMario = new SnModel;

	// if (!snMario->model()->load("../src/objects/goomba.obj"))
	// {
	// 	gsout << "Goomba model was not loaded" << gsnl;
	// }

	// gsMario.translation(mover);

	// SnGroup *maGroup = new SnGroup;
	// maManip->visible(false);
	// maManip->initial_mat(gsMario);
	// maGroup->add(snMario);
	// maManip->child(maGroup);

	// rootg()->add(maManip);

	// snMario1 = new SnModel;

	// if (!snMario1->model()->load("../src/objects/goomba.obj"))
	// {
	// 	gsout << "Goomba model was not loaded" << gsnl;
	// }

	// gsMario1.translation(mover1);

	// SnGroup *maGroup1 = new SnGroup;
	// maManip1->initial_mat(gsMario1);
	// maManip1->visible(false);
	// maGroup1->add(snMario1);
	// maManip1->child(maGroup1);

	// rootg()->add(maManip1);

	// snMario2 = new SnModel;

	// if (!snMario2->model()->load("../src/objects/goomba.obj"))
	// {
	// 	gsout << "Goomba model was not loaded" << gsnl;
	// }

	// gsMario2.translation(mover2);

	// SnGroup *maGroup2 = new SnGroup;
	// maManip2->visible(false);
	// maManip2->initial_mat(gsMario2);
	// maGroup2->add(snMario2);
	// maManip2->child(maGroup2);

	// rootg()->add(maManip2);

	// snMario3 = new SnModel;

	// if (!snMario3->model()->load("../src/objects/goomba.obj"))
	// {
	// 	gsout << "Goomba model was not loaded" << gsnl;
	// }

	// gsMario3.translation(mover3);

	// SnGroup *maGroup3 = new SnGroup;
	// maManip3->visible(false);
	// maManip3->initial_mat(gsMario3);
	// maGroup3->add(snMario3);
	// maManip3->child(maGroup3);

	// rootg()->add(maManip3);

	// snMario4 = new SnModel;

	// if (!snMario4->model()->load("../src/objects/goomba.obj"))
	// {
	// 	gsout << "Goomba model was not loaded" << gsnl;
	// }

	// gsMario4.translation(mover4);

	// SnGroup *maGroup4 = new SnGroup;
	// maManip4->visible(false);
	// maManip4->initial_mat(gsMario4);
	// maGroup4->add(snMario4);
	// maManip4->child(maGroup4);

	// rootg()->add(maManip4);

	// snMario5 = new SnModel;

	// if (!snMario5->model()->load("../src/objects/goomba.obj"))
	// {
	// 	gsout << "Goomba model was not loaded" << gsnl;
	// }

	// gsMario5.translation(mover5);

	// SnGroup *maGroup5 = new SnGroup;
	// maManip5->visible(false);
	// maManip5->initial_mat(gsMario5);
	// maGroup5->add(snMario5);
	// maManip5->child(maGroup5);

	// rootg()->add(maManip5);

	// snMario6 = new SnModel;

	// if (!snMario6->model()->load("../src/objects/goomba.obj"))
	// {
	// 	gsout << "Goomba model was not loaded" << gsnl;
	// }

	// gsMario6.translation(mover6);

	// SnGroup *maGroup6 = new SnGroup;
	// maManip6->visible(false);
	// maManip6->initial_mat(gsMario6);
	// maGroup6->add(snMario6);
	// maManip6->child(maGroup6);

	// rootg()->add(maManip6);

	// snMario7 = new SnModel;

	// if (!snMario7->model()->load("../src/objects/goomba.obj"))
	// {
	// 	gsout << "Goomba model was not loaded" << gsnl;
	// }

	// gsMario7.translation(mover7);

	// SnGroup *maGroup7 = new SnGroup;
	// maManip7->visible(false);
	// maManip7->initial_mat(gsMario7);
	// maGroup7->add(snMario7);
	// maManip7->child(maGroup7);

	// rootg()->add(maManip7);

	// snMario8 = new SnModel;

	// if (!snMario8->model()->load("../src/objects/goomba.obj"))
	// {
	// 	gsout << "Goomba model was not loaded" << gsnl;
	// }

	// gsMario8.translation(mover8);

	// SnGroup *maGroup8 = new SnGroup;
	// maManip8->visible(false);
	// maManip8->initial_mat(gsMario8);
	// maGroup8->add(snMario8);
	// maManip8->child(maGroup8);

	// rootg()->add(maManip8);
}

void MyViewer::move_camera_right()
{
	camera().translate(GsVec(cameraX + cameraAdjustment, cameraY, cameraZ));
	render();
	ws_check();
}

void MyViewer::move_camera_left()
{
	camera().translate(GsVec(cameraX - cameraAdjustment, cameraY, cameraZ));
	render();
	ws_check();
}

void MyViewer::move_camera_up()
{
	camera().translate(GsVec(cameraX, cameraY + cameraAdjustment, cameraZ));
	render();
	ws_check();
}

void MyViewer::move_camera_down()
{
	camera().translate(GsVec(cameraX, cameraY - cameraAdjustment, cameraZ));
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

void MyViewer::rotate_camera_right()
{
	camera().rotate(GsQuat());
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

void MyViewer::move_sun_up()
{
	shadowPoints[9] += 1;
	render();
	ws_check();
}

void MyViewer::move_sun_down()
{
	shadowPoints[9] -= 1;
	render();
	ws_check();
}

void MyViewer::moveLeft()
{
	mover.x -= 0.05f;

	gsMario.translation(mover);

	maManip->initial_mat(gsMario);

	mover1.x += 0.05f;

	gsMario1.translation(mover1);

	maManip1->initial_mat(gsMario1);

	mover2.x += 0.05f;

	gsMario2.translation(mover2);

	maManip2->initial_mat(gsMario2);

	mover3.x -= 0.05f;

	gsMario3.translation(mover3);

	maManip3->initial_mat(gsMario3);

	mover4.x -= 0.05f;

	gsMario4.translation(mover4);

	maManip4->initial_mat(gsMario4);

	mover5.x -= 0.05f;

	gsMario5.translation(mover5);

	maManip5->initial_mat(gsMario5);

	mover6.x -= 0.05f;

	gsMario6.translation(mover6);

	maManip6->initial_mat(gsMario6);

	mover7.x += 0.05f;

	gsMario7.translation(mover7);

	maManip7->initial_mat(gsMario7);

	mover8.x -= 0.05f;

	gsMario8.translation(mover8);

	maManip8->initial_mat(gsMario8);

	redraw();
}

void MyViewer::moveRight()
{
	mover.x += 0.05f;

	gsMario.translation(mover);

	maManip->initial_mat(gsMario);

	mover1.x -= 0.05f;

	gsMario1.translation(mover1);

	maManip1->initial_mat(gsMario1);

	mover2.x -= 0.05f;

	gsMario2.translation(mover2);

	maManip2->initial_mat(gsMario2);

	mover3.x += 0.05f;

	gsMario3.translation(mover3);

	maManip3->initial_mat(gsMario3);

	mover4.x += 0.05f;

	gsMario4.translation(mover4);

	maManip4->initial_mat(gsMario4);

	mover5.x += 0.05f;

	gsMario5.translation(mover5);

	maManip5->initial_mat(gsMario5);

	mover6.x += 0.05f;

	gsMario6.translation(mover6);

	maManip6->initial_mat(gsMario6);

	mover7.x -= 0.05f;

	gsMario7.translation(mover7);

	maManip7->initial_mat(gsMario7);

	mover8.x += 0.05f;

	gsMario8.translation(mover8);

	maManip8->initial_mat(gsMario8);

	redraw();
}

void MyViewer::moveUp()
{
	mover.y -= 0.05f;

	gsMario.translation(mover);

	maManip->initial_mat(gsMario);

	mover1.y += 0.05f;

	gsMario1.translation(mover1);

	maManip1->initial_mat(gsMario1);

	mover2.y += 0.05f;

	gsMario2.translation(mover2);

	maManip2->initial_mat(gsMario2);

	mover3.y -= 0.05f;

	gsMario3.translation(mover3);

	maManip3->initial_mat(gsMario3);

	mover4.y -= 0.05f;

	gsMario4.translation(mover4);

	maManip4->initial_mat(gsMario4);

	mover5.y -= 0.05f;

	gsMario5.translation(mover5);

	maManip5->initial_mat(gsMario5);

	mover6.y -= 0.05f;

	gsMario6.translation(mover6);

	maManip6->initial_mat(gsMario6);

	mover7.y += 0.05f;

	gsMario7.translation(mover7);

	maManip7->initial_mat(gsMario7);

	mover8.y -= 0.05f;

	gsMario8.translation(mover8);

	maManip8->initial_mat(gsMario8);

	redraw();
}

void MyViewer::moveDown()
{
	mover.y += 0.05f;

	gsMario.translation(mover);

	maManip->initial_mat(gsMario);

	mover1.y -= 0.05f;

	gsMario1.translation(mover1);

	maManip1->initial_mat(gsMario1);

	mover2.y -= 0.05f;

	gsMario2.translation(mover2);

	maManip2->initial_mat(gsMario2);

	mover3.y += 0.05f;

	gsMario3.translation(mover3);

	maManip3->initial_mat(gsMario3);

	mover4.y += 0.05f;

	gsMario4.translation(mover4);

	maManip4->initial_mat(gsMario4);

	mover5.y += 0.05f;

	gsMario5.translation(mover5);

	maManip5->initial_mat(gsMario5);

	mover6.y += 0.05f;

	gsMario6.translation(mover6);

	maManip6->initial_mat(gsMario6);

	mover7.y -= 0.05f;

	gsMario7.translation(mover7);

	maManip7->initial_mat(gsMario7);

	mover8.y += 0.05f;

	gsMario8.translation(mover7);

	maManip8->initial_mat(gsMario8);

	redraw();
}

void MyViewer::jumpUp()
{
	mover.z += 0.05f;

	gsMario.translation(mover);

	maManip->initial_mat(gsMario);

	mover1.z += 0.05f;

	gsMario1.translation(mover1);

	maManip1->initial_mat(gsMario1);

	mover2.z += 0.05f;

	gsMario2.translation(mover2);

	maManip2->initial_mat(gsMario2);

	mover3.z += 0.05f;

	gsMario3.translation(mover3);

	maManip3->initial_mat(gsMario3);

	mover4.z += 0.05f;

	gsMario4.translation(mover4);

	maManip4->initial_mat(gsMario4);

	mover5.z += 0.05f;

	gsMario5.translation(mover5);

	maManip5->initial_mat(gsMario5);

	mover6.z += 0.05f;

	gsMario6.translation(mover6);

	maManip6->initial_mat(gsMario6);

	mover7.z += 0.05f;

	gsMario7.translation(mover7);

	maManip7->initial_mat(gsMario7);

	mover8.z += 0.05f;

	gsMario8.translation(mover8);

	maManip8->initial_mat(gsMario8);

	redraw();
}

void MyViewer::jumpDown()
{
	mover.z -= 0.05f;

	gsMario.translation(mover);

	maManip->initial_mat(gsMario);

	mover1.z -= 0.05f;

	gsMario1.translation(mover1);

	maManip1->initial_mat(gsMario1);

	mover2.z -= 0.05f;

	gsMario2.translation(mover2);

	maManip2->initial_mat(gsMario2);

	mover3.z -= 0.05f;

	gsMario3.translation(mover3);

	maManip3->initial_mat(gsMario3);

	mover4.z -= 0.05f;

	gsMario3.translation(mover4);

	maManip4->initial_mat(gsMario4);

	mover5.z -= 0.05f;

	gsMario5.translation(mover5);

	maManip5->initial_mat(gsMario5);

	mover6.z -= 0.05f;

	gsMario6.translation(mover6);

	maManip6->initial_mat(gsMario6);

	mover7.z -= 0.05f;

	gsMario7.translation(mover7);

	maManip7->initial_mat(gsMario7);

	mover8.z -= 0.05f;

	gsMario8.translation(mover8);

	maManip8->initial_mat(gsMario8);

	redraw();
}

// Below is an example of how to control the main loop of an animation:
void MyViewer::run_animation()
{
	if (_animating)
		return; // avoid recursive calls
	_animating = true;

	double frdt = 1.0 / 30.0; // delta time to reach given number of frames per second
	double time = 0, lt = 0, t0 = gs_time();
	do // run for a while:
	{
		while (time - lt < frdt)
		{
			ws_check();
			time = gs_time() - t0;
		} // wait until it is time for next frame
		lt = time;
		while (time - lt < frdt)
		{
			ws_check();
			time = gs_time() - t0;
		}
		lt = time;

		if (time < 20)
		{
			if (time < 1)
			{
				moveUp();
				ws_check();
			}
			if (time > 1 && time < 2)
			{
				moveRight();
				ws_check();
			}
			if (time > 3 && time < 4)
			{
				moveDown();
				ws_check();
			}
			if (time > 4 && time < 5)
			{
				moveLeft();
				ws_check();
			}
			if (time > 6 && time < 7)
			{
				jumpUp();
				ws_check();
			}
			if (time > 7 && time < 8)
			{
				jumpDown();
				ws_check();
			}
			if (time > 8 && time < 9)
			{
				moveUp();
				ws_check();
			}
			if (time > 9 && time < 10)
			{
				moveRight();
				ws_check();
			}
			if (time > 10 && time < 11)
			{
				moveDown();
				ws_check();
			}
			if (time > 11 && time < 12)
			{
				moveLeft();
				ws_check();
			}
			if (time > 12 && time < 13)
			{
				time = 0;
				lt = 0;
				t0 = gs_time();
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
	gsout << "Camera: " << camera() << gsnl;
	// gsout << "Shadow: ";
	// for (int i = 0; i < sizeof(shadowPoints)/sizeof(shadowPoints[0]); i++) {
	// 	if (i%4 == 0) gsout << gsnl;
	// 	gsout << shadowPoints[i] << ", ";
	// }

	switch (e.key)
	{
	case GsEvent::KeyEsc:
	{
		gs_exit();
		return 1;
	}
	case 'n':
	{
		bool b = !_nbut->value();
		_nbut->value(b);
		show_normals(b);
		return 1;
	}
	case GsEvent::KeyLeft:
	{
		move_camera_left();
		return 1;
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
	{
		camera_zoom_in();
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
	{
		gsout << "Key pressed: " << e.key << gsnl;
	}
	}

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