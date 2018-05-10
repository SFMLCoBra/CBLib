#ifndef CB_CAMERA_HPP
#define CB_CAMERA_HPP

#include <iostream>
#include <memory>

#include <SFML\Graphics.hpp>

#include "Data.hpp"

namespace cb
{

/*
// handles the sfml-RenderWindow
// replaces the currentView
// controls the currentView
// -> zoom | rotation | center
// -> moving boundary
// -> relativ mouse position
// -> tile position
// -> drag/drop currentView with mouse sprite
// -> can handle multiple views saved as map 
//  
//  EXAMPLES:
//  1) example for zoom
//
//	while(wnd.pollevent(ev))
//	l...
//	case sf::Event::MouseWheelMoved:
//		if (ev.mouseWheel.delta > 0) <----------
//		{
//			cam.zoomOut();	<----------
//		}
//		else if (ev.mouseWheel.delta < 0)
//		{
//			cam.zoomIn();	<----------
//		}
//      l...
//		cam.update(); <----------
///		l...
*/
class Camera
{
public:
	/*
	// You can't use this class without initilizing the window.
	// -> Camera(sf::RenderWindow * window)
	// -> OnCreate(RenderWindow * window)
	*/	
	Camera() = delete;
	/*
	// Takes the currentView of the RenderWindow.
	// Won't delete window.
	// Boundary is enabled by default.
	*/
	Camera(sf::RenderWindow& window, const sf::FloatRect& boundary = {-10000, -10000, 10000, 10000 });
	Camera(const Camera&) = delete;
	virtual ~Camera();


	// ENUM 
	enum SPLITSCREEN_TYPE
	{
		VERTICAL,
		HORIZONTAL,
		// Vertical + horizontal
		FOURSPLIT
	};

	// METHODS

	/*
	// Updates the currentView. (e.g.: moving)
	*/
	void update();

	/*
	// Zooms out. Decreases zoom level.
	*/
	void zoomOut();

	/*
	// Zooms in. Increases zoom level.
	*/
	void zoomIn();

	/*
	// Resets the zoom level(!) to the initialized window currentView.
	*/
	void resetZoom();

	/*
	// Zooms in/out. (in: 0.5f / out: 2.0f)
	// e.g.: 
	// 1200w | 600h 
	// zoom(0.5f);
	// -> 600 | 300
	*/
	void zoom(float zoom);

	/*
	// Creates 'screensNumber' views and decides
	// with the second argument what to do with it.
	// Current view points to the first element in the map.
	// Default key strings: "view" + index 
	// PARAMETERS
	// - VERTICAL			splits every screen vertically
	// - HORIZONTAL			splits every screen horizontally
	// - FOURSPLIT			splits screens in four, resets views to 4
	*/
	void splitScreen(SPLITSCREEN_TYPE type);

	/*
	// Changes the index key to the given string key.
	// Returns NEW reference to the view.
	// Example:
	// // define Camera... 
	// sf::View mainView = camera.getView();
	// // Create another view with addView() or splitScreen()
	// // and create a second view pointing to it
	// 
	*/
	std::shared_ptr<sf::View> changeKeyValue(const std::string& oldKeyValue, const std::string& newKeyValue);

	/*
	// Removes the view by keyname. 
	// Returns false if couldn't find view.
	*/
	bool removeView(const std::string& viewName);

	/*
	// Adds a view to the map with the given name.
	// Returns handle to the view.
	// If element already exists, returns nullptr.
	// If no argument given, the key value
	// will be:  "view" + index ("view0","view1",...)
	*/
	std::shared_ptr<sf::View> addView(const std::string& viewName = "", const sf::FloatRect& viewRect = { 0, 0 , 1000, 1000 });

	/*
	// Clears the map<std::string, sf::View>.
	*/
	void removeAllViews();


	// SETTER
	

	/*
	// Uses the sfml enum Button.
	// If this sprite is pressed, you can drag the currentView
	// to another position until you release the sprite.
	// Default: Right Mouse Button
	*/
	void setMouseDragButton(sf::Mouse::Button button);

	/*
	// Uses the sfml enum Key. 
	// If this key is pressed, you can't move the currentView IN
	// update(). 
	// This sets moveable to false.
	// Default: LControl (left control)
	*/
	void setStopMoveKey(sf::Keyboard::Key key);

	/*
	// Sets the position of the currentView.
	*/
	void setCenter(sf::Vector2f position);

	/*
	// Sets a boundary for the currentView. (not size!)
	*/
	void setBounds(const sf::FloatRect &bounds);

	/*
	// Sets the limit to how many times you can
	// zoom in/out.
	*/
	void setZoomMaximum(int max);

	/*
	// Sets the zoom strength per zoom level.
	// Default: 0.05f;
	*/
	void setZoomStrength(float zoomPerStep);

	/*
	// Rotates the currentView.
	*/
	void setRotation(float rotation);

	/*
	// Whether the currentView is moveable.
	*/
	void setMoveable(bool moveable);

	/*
	// Whether the currentView is dragable with a mouse sprite.
	*/
	void setDragable(bool dragable);

	/*
	// Calls the sf::View setSize method. which will set the currentView size.
	*/
	void setSize(const sf::Vector2f& size);

	/*
	// Calls the sf::View setViewPort
	*/
	void setViewPort(const sf::FloatRect& viewport);

	/*
	// Whether the boundary should be enabled or not.
	*/
	void setBoundaryEnabled(bool enable);



	// GETTER

	/*
	// Returns the size of the currentView.
	// Returns nullptr if no window is set.
	*/
	const sf::Vector2f* getSize()const;

	/*
	// Returns the center position of the currentView. (world position)
	// Returns nullptr if no window is set.
	*/
	const sf::Vector2f* getCenter()const;

	/*
	// Returns the Position relativly to the coord system.
	*/
	sf::Vector2f getMouseWorldPos() const;

	/*
	// Returns the tile position realtivly to the mouse cursor.
	// e.g.:
	// 1) mouseX = 31, mouseY = 33, tileSize = 32
	// getMouseWorldTilePosCenter( 32 );
	// returns { 16, 48 } which is the center of the tile
	// 2) works for negative coords aswell.
	*/
	sf::Vector2f getMouseWorldTilePosCenter(int tileSize) const;

	/*
	// Returns the tile position.
	// e.g.:  
	// 1) x = 31, y = 33, tileSize = 32
	// getMouseWorldTilePosCenter( 32, 33, 32 );
	// returns { 16, 48 } which is the center of the tile
	// 2) ... works for negative coords aswell.
	*/
	sf::Vector2f getTilePositionCenter(float x, float y, int size) const;

	/*
	// Returns the top left position of the currentView in world coords.
	*/
	sf::Vector2f getTopLeftPos() const;

	/*
	// Returns the Position of the Mouse Cursor relativly to the window.
	// (left-top position. 0,0)
	*/
	static const sf::Vector2f& getMouseWindowPosition();

	/*
	// May the currentView be moved..
	*/
	bool isMoveable() const;

	/*
	// Can the currentView be moved with a mouse sprite.
	*/
	bool isDragable() const;

	/*
	// Is the boundary for moving the currentView enabled.
	*/
	bool isBoundaryEnabled() const;

	/*
	// Returns the viewport.
	// Returns nullptr if view is not set.
	*/
	const sf::FloatRect* getViewPort() const;

	/*
	// If no argument, this will return the current view of the window.
	// else it returns the view with given key.
	// if key not found, returns current view.
	// You need this method to get access to the views.
	*/
	const std::shared_ptr<sf::View> getView(const std::string& keyValue = "") const;

	/*
	// Writes the key values to the vector. (trunc)
	// returns false if there is no view.
	*/
	bool getViewsKeyValues(std::vector<std::string>& keyValues) const;

	/*
	// Returns every view by reference.
	*/
	std::map<std::string, std::shared_ptr<sf::View>>& getViews();


protected:

	/*
	// Sets currentView to the window.
	// Checks for nullptr.
	// Returns true if set.
	// Returns false if wnd == nullptr
	*/
	void setView();	

	/*
	// Returns false if current view is nullptr.
	// Additionally prints error when nullptr.
	*/
	bool isViewSet() const;

	/*
	// increments viewindex and returns name "view" + indx
	*/
	std::string getNextViewName();

private:
	// METHODS

	/*
	// Sets the currentView size based on the zoom level.
	*/
	void updateZoom();


	// VARIABLES
	static sf::RenderWindow* wnd;

	int viewIndex;
	std::string viewName;
	std::map<std::string, std::shared_ptr<sf::View>> views; 
	std::shared_ptr<sf::View> currentView;
	
	sf::Mouse::Button dragMouseButton;
	sf::Keyboard::Key stopMoveKey;
	bool moveable;
	bool dragable;
	bool boundaryEnabled;

	int currentZoom;
	float zoomStep;
	int zoomMax;
	int zoombefore;

	// currentView bounds
	sf::FloatRect bounds;
	sf::Vector2f viewSizeDefault;

	sf::Vector2f startPos;
	sf::Vector2f endPos;
	sf::Vector2f offset;
	bool onetimepressed;
};

}
#endif