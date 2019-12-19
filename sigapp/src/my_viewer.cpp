# include "my_viewer.h"

# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>

# include <sigogl/ws_run.h>

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
SnModel* snMario;
SnManipulator* maManip;

GsMat gsMario1;
SnModel* snMario1;
SnManipulator* maManip1;

GsMat gsMario2;
SnModel* snMario2;
SnManipulator* maManip2;

GsMat gsMario3;
SnModel* snMario3;
SnManipulator* maManip3;

GsMat gsMario4;
SnModel* snMario4;
SnManipulator* maManip4;

GsMat gsMario5;
SnModel* snMario5;
SnManipulator* maManip5;

GsMat gsMario6;
SnModel* snMario6;
SnManipulator* maManip6;

GsMat gsMario7;
SnModel* snMario7;
SnManipulator* maManip7;

GsMat gsMario8;
SnModel* snMario8;
SnManipulator* maManip8;


bool up;
bool down;
bool left;
bool right;

MyViewer::MyViewer ( int x, int y, int w, int h, const char* l ) : WsViewer(x,y,w,h,l)
{


	_nbut=0;
	_animating=false;

	maManip = new SnManipulator;
	maManip1 = new SnManipulator;
	maManip2 = new SnManipulator;
	maManip3 = new SnManipulator;
	maManip4 = new SnManipulator;
	maManip5 = new SnManipulator;
	maManip6 = new SnManipulator;
	maManip7 = new SnManipulator;
	maManip8 = new SnManipulator;

	build_ui ();
	build_scene ();
}

void MyViewer::build_ui ()
{
	UiPanel *p, *sp;
	UiManager* uim = WsWindow::uim();
	p = uim->add_panel ( "", UiPanel::HorizLeft );
	p->add ( new UiButton ( "View", sp=new UiPanel() ) );
	{	UiPanel* p=sp;
		p->add ( _nbut=new UiCheckButton ( "Normals", EvNormals ) ); 
	}
	p->add ( new UiButton ( "Animate", EvAnimate ) );
	p->add ( new UiButton ( "Exit", EvExit ) ); p->top()->separate();
}

void MyViewer::add_model ( SnShape* s, GsVec p )
{
	SnManipulator* manip = new SnManipulator;
	GsMat m;
	GsMat r;
	m.translation(p);
	manip->initial_mat(m);
	SnManipulator* shadow = new SnManipulator;
	GsMat shad;

	shad.setl1(1, -8 / 5, 0, 0);
	shad.setl2(0, 0, 0, 0);
	shad.setl3(0, -20 / 5, 1, 0);
	shad.setl4(0, 0, 0, 1);
	shad.rcombtrans(p);

	shadow->initial_mat(shad);

	SnGroup* g = new SnGroup;
	SnLines* l = new SnLines;
	l->color(GsColor::orange);
	g->add(s);
	g->add(l);
	manip->child(g);
	shadow->child(g);
	rootg()->add(manip);
	rootg()->add(shadow);

	rootg()->add(manip);

	//FUNCTION FOR animations that move around


	//camera FUNCTIONS :) FROM PREVIOUS PROJECT WILL NEED TO IMPLENTENT LATER
	//double frdt = 1.0 / 30.0;
	//double t, lt, t0 = gs_time();
	//gtime = 0.0f;
	//if (camView == true) {
	//	camera().eye.x = 10;
	//	camera().eye.y = 280;
	//	camera().eye.z = 10;
	//	render();
	//	ws_check();
	//}
	//else {
	//	t = 0;
	//	lt = 0;
	//	do {
	//		lt = gs_time() - t0;
	//		if (lt < 2.0f) {
	//			camera().eye.x += 0.1f;
	//			camera().eye.z += 0.1f;
	//			camera().center.y = 0.0f;
	//		}
	//		if (lt > 2.0f && lt <= 5.0f) {
	//			camera().eye.x -= 0.05f;
	//			camera().eye.z -= 0.05f;
	//		}

	//		render();
	//		ws_check();
	//		message().setf("local time = % f", lt);
	//	} while (lt < 5.0f);
	//}
}

void MyViewer::build_scene ()
{

	snMario = new SnModel;


	if (!snMario->model()->load("../src/objects/goomba.obj"))
	{
		gsout << "Goomba model was not loaded" << gsnl;
	}

	gsMario.translation(mover);

	SnGroup* maGroup = new SnGroup;
	maManip->visible(false);
	maManip->initial_mat(gsMario);
	maGroup->add(snMario);
	maManip->child(maGroup);

	rootg()->add(maManip);

	snMario1 = new SnModel;

	if (!snMario1->model()->load("../src/objects/goomba.obj"))
	{
		gsout << "Goomba model was not loaded" << gsnl;
	}

	gsMario1.translation(mover1);

	SnGroup* maGroup1 = new SnGroup;
	maManip1->initial_mat(gsMario1);
	maManip1->visible(false);
	maGroup1->add(snMario1);
	maManip1->child(maGroup1);

	rootg()->add(maManip1);

	snMario2 = new SnModel;

	if (!snMario2->model()->load("../src/objects/goomba.obj"))
	{
		gsout << "Goomba model was not loaded" << gsnl;
	}

	gsMario2.translation(mover2);

	SnGroup* maGroup2 = new SnGroup;
	maManip2->visible(false);
	maManip2->initial_mat(gsMario2);
	maGroup2->add(snMario2);
	maManip2->child(maGroup2);

	rootg()->add(maManip2);

	snMario3 = new SnModel;

	if (!snMario3->model()->load("../src/objects/goomba.obj"))
	{
		gsout << "Goomba model was not loaded" << gsnl;
	}

	gsMario3.translation(mover3);

	SnGroup* maGroup3 = new SnGroup;
	maManip3->visible(false);
	maManip3->initial_mat(gsMario3);
	maGroup3->add(snMario3);
	maManip3->child(maGroup3);

	rootg()->add(maManip3);

	snMario4 = new SnModel;

	if (!snMario4->model()->load("../src/objects/goomba.obj"))
	{
		gsout << "Goomba model was not loaded" << gsnl;
	}

	gsMario4.translation(mover4);

	SnGroup* maGroup4 = new SnGroup;
	maManip4->visible(false);
	maManip4->initial_mat(gsMario4);
	maGroup4->add(snMario4);
	maManip4->child(maGroup4);

	rootg()->add(maManip4);

	snMario5 = new SnModel;

	if (!snMario5->model()->load("../src/objects/goomba.obj"))
	{
		gsout << "Goomba model was not loaded" << gsnl;
	}

	gsMario5.translation(mover5);

	SnGroup* maGroup5 = new SnGroup;
	maManip5->visible(false);
	maManip5->initial_mat(gsMario5);
	maGroup5->add(snMario5);
	maManip5->child(maGroup5);

	rootg()->add(maManip5);

	snMario6 = new SnModel;

	if (!snMario6->model()->load("../src/objects/goomba.obj"))
	{
		gsout << "Goomba model was not loaded" << gsnl;
	}

	gsMario6.translation(mover6);

	SnGroup* maGroup6 = new SnGroup;
	maManip6->visible(false);
	maManip6->initial_mat(gsMario6);
	maGroup6->add(snMario6);
	maManip6->child(maGroup6);

	rootg()->add(maManip6);

	snMario7 = new SnModel;

	if (!snMario7->model()->load("../src/objects/goomba.obj"))
	{
		gsout << "Goomba model was not loaded" << gsnl;
	}

	gsMario7.translation(mover7);

	SnGroup* maGroup7 = new SnGroup;
	maManip7->visible(false);
	maManip7->initial_mat(gsMario7);
	maGroup7->add(snMario7);
	maManip7->child(maGroup7);

	rootg()->add(maManip7);

	snMario8 = new SnModel;

	if (!snMario8->model()->load("../src/objects/goomba.obj"))
	{
		gsout << "Goomba model was not loaded" << gsnl;
	}

	gsMario8.translation(mover8);

	SnGroup* maGroup8 = new SnGroup;
	maManip8->visible(false);
	maManip8->initial_mat(gsMario8);
	maGroup8->add(snMario8);
	maManip8->child(maGroup8);

	rootg()->add(maManip8);


	
	/*
	SnModel *Grass = new SnModel;//grass
	if (!Grass->model()->load("../src/objects/grassPatch.obj")) {
		gsout << "Grass was not loaded" << gsnl;
	}
	Grass->color(GsColor::green);
	GsModel* GrassModel = Grass->model();
	GrassModel->scale(10000);
	rootg()->add(Grass); 

	SnModel *TwoStoryHouse = new SnModel;
	if (!TwoStoryHouse->model()->load("../src/objects/mushroom-house.obj")) {
		gsout << "TwoStoryHouse was not loaded" << gsnl;
	}
	// TwoStoryHouse->color(GsColor::green);
	GsModel* TwoStoryHouseModel = TwoStoryHouse->model();
	TwoStoryHouseModel->scale(1);
	add_model(TwoStoryHouse, GsVec(xTwoStoryHouse, yTwoStoryHouse, zTwoStoryHouse));

	SnModel* TwoStoryHouse1 = new SnModel;
	if (!TwoStoryHouse1->model()->load("../src/objects/mushroom-house.obj")) {
		gsout << "TwoStoryHouse was not loaded" << gsnl;
	}
	// TwoStoryHouse->color(GsColor::green);
	GsModel* TwoStoryHouseModel1 = TwoStoryHouse1->model();
	TwoStoryHouseModel1->scale(1);
	add_model(TwoStoryHouse1, GsVec(20000.0F, 0.0F, 20000.0F));


	// ! Trying to load a second mushroom house
	SnModel *TwoStoryHouse2 = new SnModel;
	if (!TwoStoryHouse2->model()->load("../src/objects/mushroom-house-1.obj")) {
		gsout << "TwoStoryHouse was not loaded" << gsnl;
	}
	// TwoStoryHouse->color(GsColor::green);
	GsModel* TwoStoryHouseModel2 = TwoStoryHouse2->model();
	TwoStoryHouseModel2->scale(1);
	add_model(TwoStoryHouse2, GsVec(3000.0f, 0.0f, -20000.0f));



	SnModel* TwoStoryHouse3 = new SnModel;
	if (!TwoStoryHouse3->model()->load("../src/objects/mushroom-house.obj")) {
		gsout << "TwoStoryHouse was not loaded" << gsnl;
	}
	// TwoStoryHouse->color(GsColor::green);
	GsModel* TwoStoryHouseModel3 = TwoStoryHouse3->model();
	TwoStoryHouseModel3->scale(1);
	add_model(TwoStoryHouse3, GsVec(-20000.0f, 0.0f, 0.0f));  */

	//this one is sideways

	//SnModel* House = new SnModel;
	//if (!House->model()->load("C:\\Users\\Ruby Law\\Desktop\\CSE170-project-master\\sigapp\\src\\Objects\\20951_Mushroom_v2_NEW.obj")) {
	//	gsout << "house was not loaded" << gsnl;
	//}
	//// TwoStoryHouse->color(GsColor::green);
	//GsModel* House1 = House->model();
	//House1->scale(3000);
	//add_model(House, GsVec(-20000.0f, 10.0f, 30000.0f));


}

// Below is an example of how to control the main loop of an animation:
void MyViewer::run_animation ()
{
	if ( _animating ) return; // avoid recursive calls
	_animating = true;

	double frdt = 1.0 / 30.0;
	double time = 0, lt = 0, t0 = gs_time();
	do
	{
		while (time - lt < frdt) { ws_check(); time = gs_time() - t0; }
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

void MyViewer::show_normals ( bool view )
{
	// Note that primitives are only converted to meshes in GsModel
	// at the first draw call.
	GsArray<GsVec> fn;
	SnGroup* r = (SnGroup*)root();
	for ( int k=0; k<r->size(); k++ )
	{	SnManipulator* manip = r->get<SnManipulator>(k);
		SnShape* s = manip->child<SnGroup>()->get<SnShape>(0);
		SnLines* l = manip->child<SnGroup>()->get<SnLines>(1);
		if ( !view ) { l->visible(false); continue; }
		l->visible ( true );
		if ( !l->empty() ) continue; // build only once
		l->init();
		if ( s->instance_name()==SnPrimitive::class_name )
		{	GsModel& m = *((SnModel*)s)->model();
			m.get_normals_per_face ( fn );
			const GsVec* n = fn.pt();
			float f = 0.33f;
			for ( int i=0; i<m.F.size(); i++ )
			{	const GsVec& a=m.V[m.F[i].a]; l->push ( a, a+(*n++)*f );
				const GsVec& b=m.V[m.F[i].b]; l->push ( b, b+(*n++)*f );
				const GsVec& c=m.V[m.F[i].c]; l->push ( c, c+(*n++)*f );
			}
		}  
	}
}

int MyViewer::handle_keyboard ( const GsEvent &e )
{
	int ret = WsViewer::handle_keyboard ( e ); // 1st let system check events
	if ( ret ) return ret;

	switch ( e.key )
	{	case GsEvent::KeyEsc : gs_exit(); return 1;
		case 'n' : { bool b=!_nbut->value(); _nbut->value(b); show_normals(b); return 1; }
		default: gsout<<"Key pressed: "<<e.key<<gsnl;


		case GsEvent::KeyUp: {

			moveUp();

			up = !up;

			return 1;
		}

		case GsEvent::KeyDown: {

			moveDown();

			down = !down;

			return 1;
		}

		case GsEvent::KeyRight: {

			moveRight();

			right = !right;

			return 1;
		}

		case GsEvent::KeyLeft: {

			moveLeft();

			left = !left;

			return 1;
		}
		

	}

	return 0;
}

int MyViewer::uievent ( int e )
{
	switch ( e )
	{	case EvNormals: show_normals(_nbut->value()); return 1;
		case EvAnimate: run_animation(); return 1;
		case EvExit: gs_exit();
	}
	return WsViewer::uievent(e);
}
