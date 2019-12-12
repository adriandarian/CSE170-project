# include "my_viewer.h"

# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>

# include <sigogl/ws_run.h>

MyViewer::MyViewer ( int x, int y, int w, int h, const char* l ) : WsViewer(x,y,w,h,l)
{
	_nbut=0;
	_animating=false;
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
}

void MyViewer::build_scene ()
{
	// Re-initialize the scene before drawing.
	rootg()->remove_all();

	SnModel *Grass = new SnModel;//grass
	if (!Grass->model()->load("C:\\Users\\adria\\Documents\\CSE170-project\\sigapp\\src\\Objects\\grassPatch.obj")) {
		gsout << "Grass was not loaded" << gsnl;
	}
	Grass->color(GsColor::green);
	GsModel* GrassModel = Grass->model();
	GrassModel->scale(10000);
	rootg()->add(Grass); 

	SnModel *TwoStoryHouse = new SnModel;
	if (!TwoStoryHouse->model()->load("C:\\Users\\adria\\Documents\\CSE170-project\\sigapp\\src\\Objects\\mushroom-house.obj")) {
		gsout << "TwoStoryHouse was not loaded" << gsnl;
	}
	// TwoStoryHouse->color(GsColor::green);
	GsModel* TwoStoryHouseModel = TwoStoryHouse->model();
	TwoStoryHouseModel->scale(1);
	add_model(TwoStoryHouse, GsVec(xTwoStoryHouse, yTwoStoryHouse, zTwoStoryHouse));

	// ! Trying to load a second mushroom house
	SnModel *TwoStoryHouse2 = new SnModel;
	if (!TwoStoryHouse2->model()->load("C:\\Users\\adria\\Documents\\CSE170-project\\sigapp\\src\\Objects\\mushroom-house.obj")) {
		gsout << "TwoStoryHouse was not loaded" << gsnl;
	}
	// TwoStoryHouse->color(GsColor::green);
	GsModel* TwoStoryHouseModel2 = TwoStoryHouse2->model();
	TwoStoryHouseModel2->scale(1);
	add_model(TwoStoryHouse2, GsVec(0.0f, 5.0f, 0.0f));
}

// Below is an example of how to control the main loop of an animation:
void MyViewer::run_animation ()
{
	if ( _animating ) return; // avoid recursive calls
	_animating = true;
	
	int ind = gs_random ( 0, rootg()->size()-1 ); // pick one child
	SnManipulator* manip = rootg()->get<SnManipulator>(ind); // access one of the manipulators
	GsMat m = manip->mat();

	double frdt = 1.0/30.0; // delta time to reach given number of frames per second
	double v = 4; // target velocity is 1 unit per second
	double t=0, lt=0, t0=gs_time();
	do // run for a while:
	{	while ( t-lt<frdt ) { ws_check(); t=gs_time()-t0; } // wait until it is time for next frame
		double yinc = (t-lt)*v;
		if ( t>2 ) yinc=-yinc; // after 2 secs: go down
		lt = t;
		m.e24 += (float)yinc;
		if ( m.e24<0 ) m.e24=0; // make sure it does not go below 0
		manip->initial_mat ( m );
		render(); // notify it needs redraw
		ws_check(); // redraw now
	}	while ( m.e24>0 );
	_animating = false;
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
