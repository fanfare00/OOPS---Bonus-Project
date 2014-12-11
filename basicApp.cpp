#include "cinder/app/AppBasic.h"
#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;

// We'll create a new Cinder Application by deriving from the AppBasic class
class BasicApp : public AppBasic {
public:
	void mouseDown(MouseEvent event);
	void keyDown(KeyEvent event);
	void draw();
	void setupDots();

	// This will maintain a list of points which we will draw line segments between
	list<Vec2f>		mPoints;
	list<Vec2f>		dotPoints;

	int dotSize;
};

void BasicApp::setupDots()
{
	dotPoints.push_back(Vec2f(75, 125));
	dotPoints.push_back(Vec2f(200, 200));
	dotPoints.push_back(Vec2f(300, 50));
	dotPoints.push_back(Vec2f(400, 400));
}

void BasicApp::mouseDown(MouseEvent event)
{
	for (auto dotIter = dotPoints.begin(); dotIter != dotPoints.end(); ++dotIter)
	{
		if (event.getPos().distance(*dotIter) < 10)
		{
			mPoints.push_back(event.getPos());
		}
	}

}

void BasicApp::keyDown(KeyEvent event)
{
	if (event.getChar() == 'f')
		setFullScreen(!isFullScreen());
}

void BasicApp::draw()
{
	setupDots();
	gl::clear(Color(0.1f, 0.1f, 0.15f));

	for (auto dotIter = dotPoints.begin(); dotIter != dotPoints.end(); ++dotIter)
	{
		gl::drawSolidCircle(*dotIter, 10.0);
	}


	gl::color(1.0f, 0.5f, 0.25f);
	gl::begin(GL_LINE_STRIP);
	for (auto pointIter = mPoints.begin(); pointIter != mPoints.end(); ++pointIter) {
		gl::vertex(*pointIter);
	}
	gl::end();
}

// This line tells Cinder to actually create the application
CINDER_APP_BASIC(BasicApp, RendererGl)