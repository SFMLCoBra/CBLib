#include "Camera.hpp"

sf::RenderWindow* cb::Camera::wnd;


namespace cb
{


Camera::Camera(sf::RenderWindow &window, const sf::FloatRect& boundary)
	: bounds(boundary), viewName("view")
{
	wnd = &window;

	viewIndex = 0;
	views.insert({ getNextViewName(), std::shared_ptr<sf::View>{new sf::View()} } );
	*views["view0"] = wnd->getDefaultView();
	currentView = views["view0"];

	viewSizeDefault = views["view0"]->getSize();

	// set new 'handle'
	wnd->setView(*currentView);

	// default values for drag sprite and stop key
	dragMouseButton = sf::Mouse::Button::Right;
	stopMoveKey = sf::Keyboard::Key::LControl;

	zoombefore = 0;
	currentZoom = 0;
	zoomMax = 5;

	zoomStep = 0.05f;
	onetimepressed = false;
	dragable = true;
	moveable = true;
	boundaryEnabled = true;
}

Camera::~Camera()
{
	// window won't be deleted.
	views.clear();
}

void Camera::update()
{
	if ((sf::Keyboard::isKeyPressed(stopMoveKey)))
	{
		moveable = false;
	}

	if (moveable)
	{
		if (sf::Mouse::isButtonPressed(dragMouseButton) && dragable)
		{
			if (!onetimepressed)
			{
				onetimepressed = true;
				startPos = getMouseWorldPos();
			}
			endPos += startPos - getMouseWorldPos();

			if (boundaryEnabled)
			{
				sf::Vector2f center = endPos;
				if (center.x < bounds.left) // left
				{
					endPos.x = bounds.left;
				}
				else if (center.x > bounds.width) // right
				{
					endPos.x = bounds.width;
				}

				if (center.y < bounds.top) // bottom
				{
					endPos.y = bounds.top;
				}
				else if (center.y > bounds.height) // top
				{
					endPos.y = bounds.height;
				}
			}
			setCenter(endPos);
		}
		else if (onetimepressed)
		{
			onetimepressed = false;
		}
	}

	updateZoom();
	setView();
}

void Camera::zoom(float zoom)
{
	if (!isViewSet())
		return;

	currentView->zoom(zoom);
}

void Camera::splitScreen(SPLITSCREEN_TYPE type)
{
	if (!isViewSet())
		return;

	sf::Vector2f center = currentView->getCenter();
	sf::Vector2f size = currentView->getSize();

	float twidth = size.x * .5f;
	float theight = size.y * .5f;
	float tcx = size.x * .25f; // offset from center
	float tcy = size.y * .25f;

	std::shared_ptr<sf::View> v1, v2, v3, v4;

	std::vector<std::shared_ptr<sf::View>> copies;

	switch (type)
	{
	case SPLITSCREEN_TYPE::HORIZONTAL :
		for (auto& i : views)
		{
			sf::Vector2f t = i.second->getCenter();
			i.second->setSize(
				i.second->getSize().x, 
				i.second->getSize().y * .5f);

			sf::FloatRect vp = i.second->getViewport();
			i.second->setViewport(sf::FloatRect{ 
				0.f, 0.f, 
				i.second->getViewport().width,
				i.second->getViewport().height * .5f });

			i.second->setCenter(
				i.second->getCenter().x, 
				i.second->getCenter().y - i.second->getSize().y *.5f);

			std::shared_ptr<sf::View> tview = i.second;
			tview->setCenter(sf::Vector2f(
				t.x, 
				t.y + i.second->getSize().y * .5f));

			tview->setSize(
				i.second->getSize().x, 
				i.second->getSize().y);

			tview->setViewport(sf::FloatRect{ 
				0.f, vp.height + .5f * i.second->getViewport().height,
				i.second->getViewport().width, i.second->getViewport().height });

			copies.push_back(tview);
		}
		for (auto& i : copies)
		{
			views.insert({ getNextViewName(), i});
		}
		break;
	case SPLITSCREEN_TYPE::VERTICAL:
		for (auto& i : views)
		{
			sf::Vector2f t = i.second->getCenter();
			i.second->setSize(
				i.second->getSize().x * .5f,
				i.second->getSize().y);

			sf::FloatRect vp = i.second->getViewport();
			i.second->setViewport(sf::FloatRect{ 0.f, 0.f, 
				vp.width * 0.5f, vp.height });

			i.second->setCenter(
				i.second->getCenter().x - i.second->getSize().x *.5f,
				i.second->getCenter().y);

			std::shared_ptr<sf::View> tview = i.second;
			tview->setCenter(sf::Vector2f(t.x + i.second->getSize().x * .5f, t.y));

			tview->setSize(
				i.second->getSize().x, 
				i.second->getSize().y);

			tview->setViewport(sf::FloatRect{
				vp.width + .5f * vp.width, 0.f, 
				vp.width * .5f, vp.height });

			copies.push_back(tview);
		}
		for (auto& i : copies)
		{
			views.insert({ getNextViewName(), i });
		}		
		break;
	case SPLITSCREEN_TYPE::FOURSPLIT:
		viewIndex = 0;
		views.clear();

		twidth = size.x * .5f;
		theight = size.y * .5f;
		tcx = size.x * .25f; // offset from center
		tcy = size.y * .25f;


		v1 = std::make_shared<sf::View>();
		v2 = std::make_shared<sf::View>();
		v3 = std::make_shared<sf::View>();
		v4 = std::make_shared<sf::View>();

		v1->setCenter(center + sf::Vector2f{ -tcx, -tcy });
		v2->setCenter(center + sf::Vector2f{  tcx, -tcy });
		v3->setCenter(center + sf::Vector2f{  tcx,  tcy });
		v4->setCenter(center + sf::Vector2f{ -tcx,  tcy });

		v1->setSize({ twidth, theight });
		v2->setSize({ twidth, theight });
		v3->setSize({ twidth, theight });
		v4->setSize({ twidth, theight });

		v1->setViewport(sf::FloatRect{ 0.0f, 0.0f, 0.5f, 0.5f });
		v2->setViewport(sf::FloatRect{ 0.5f, 0.0f, 0.5f, 0.5f });
		v3->setViewport(sf::FloatRect{ 0.5f, 0.5f, 0.5f, 0.5f });
		v4->setViewport(sf::FloatRect{ 0.0f, 0.5f, 0.5f, 0.5f });

		views.insert({ getNextViewName(), v1 });
		views.insert({ getNextViewName(), v2 });
		views.insert({ getNextViewName(), v3 });
		views.insert({ getNextViewName(), v4 });
		break;
	default:
		CB_DEFAULT_ERROR_MSG(std::to_string(type) + " is an invalid type.");
		break;
	}

	if (!views.empty())
	{
		if (views.find("view0") == views.end() )
			currentView = views.begin()->second;
		else
			currentView = views.find("view0")->second;
		setView();
	}
}

const std::shared_ptr<sf::View> Camera::getView(const std::string& key) const
{
	// Return currentView
	if (key == "")
	{
		if (currentView != nullptr)
		{
			return currentView;
		}
		return nullptr;
	}
	// Return the view with specific key
	else
	{
		auto it = views.find(key);

		if (it == views.end())
		{
			CB_DEFAULT_ERROR_MSG("No View with key: " + key);
			if (currentView != nullptr)
			{
				return currentView;
			}
			return nullptr;
		}

		return it->second;
	}
}

bool Camera::getViewsKeyValues(std::vector<std::string>& keyValues) const
{
	if (views.empty())
	{
		return false;
	}

	if (!keyValues.empty())
	{
		keyValues.clear();
	}

	for (auto&& i : views)
	{
		keyValues.push_back(i.first);
	}

	return true;
}

std::shared_ptr<sf::View> Camera::changeKeyValue(const std::string & oldKeyValue, const std::string& newKeyValue)
{
	auto it = views.find(oldKeyValue);
	if (it == views.end())
	{
		CB_DEFAULT_ERROR_MSG("No View found with key: " + oldKeyValue);
		return nullptr;
	}

	std::shared_ptr<sf::View> tmp = it->second;
	views.erase(it);
	
	views.insert(std::pair<std::string, std::shared_ptr<sf::View>>{ newKeyValue, tmp });

	return views.find(newKeyValue)->second;
}

std::map<std::string, std::shared_ptr<sf::View>>& Camera::getViews()
{
	return views;
}

void Camera::zoomOut()
{
	zoombefore = currentZoom;
	currentZoom--;

	if (currentZoom < -zoomMax)
	{
		currentZoom = -zoomMax;
	}
}

void Camera::zoomIn()
{
	zoombefore = currentZoom;
	currentZoom++;

	if (currentZoom > zoomMax)
	{
		currentZoom = zoomMax;
	}
}

void Camera::resetZoom()
{
	if (!isViewSet())
	{
		float tmprot = currentView->getRotation();
		currentView->reset(sf::FloatRect{
		currentView->getCenter().x - viewSizeDefault.x * .5f, // centered 
		currentView->getCenter().y - viewSizeDefault.y * .5f,
		viewSizeDefault.x, viewSizeDefault.y }); // default currentView size
	}

	setView();
	currentZoom = 0;
	zoombefore = 0;
}

void Camera::updateZoom()
{
	if (zoombefore != currentZoom)
	{
		zoombefore = currentZoom;

		if (!isViewSet())
		{
			float tmprot = currentView->getRotation();
			currentView->reset(sf::FloatRect{
				currentView->getCenter().x - viewSizeDefault.x * .5f, // centered 
				currentView->getCenter().y - viewSizeDefault.y * .5f,
				viewSizeDefault.x, viewSizeDefault.y }); // default currentView size

			currentView->setRotation(tmprot);
			currentView->zoom(1.f + zoomStep * (float)currentZoom);
		}
	}
}

std::string Camera::getNextViewName()
{
	return viewName + std::to_string(viewIndex++);
}

void Camera::setView()
{
	if (!isViewSet())
		return;

	wnd->setView(*currentView);
}

bool Camera::isViewSet() const
{
	if (currentView == nullptr)
	{
		CB_DEFAULT_ERROR_MSG("can't set view. view is nullptr.");
		return false;
	}
	
	return true;
}

std::shared_ptr<sf::View> Camera::addView(const std::string& viewName, const sf::FloatRect& viewRect)
{
	std::pair<std::string, std::shared_ptr<sf::View>> v;

	if (viewName.empty())
	{
		v.first = getNextViewName();
	}
	else
	{
		v.first = viewName;
		viewIndex++;
	}
	v.second = std::make_shared<sf::View>(viewRect);

	auto it = views.insert(v);

	if (it.second == false)
	{
		CB_DEFAULT_ERROR_MSG("Element already existed.");
		return nullptr;
	}

	return it.first->second;
}

bool Camera::removeView(const std::string & viewName)
{
	// std::map<std::string, sf::View>::iterator it = views.find(viewName);
	auto it = views.find(viewName);

	if (it == views.end())
	{
		return false;
	}

	views.erase(it);

	return true;
}

void Camera::removeAllViews()
{
	views.clear();
}

const sf::Vector2f* Camera::getSize() const
{
	if (!isViewSet())
		return nullptr;

	return &currentView->getSize();
}

const sf::Vector2f* Camera::getCenter() const
{
	if (!isViewSet())
		return nullptr; 
	
	return &currentView->getCenter();
}

sf::Vector2f Camera::getMouseWorldPos() const
{
	return wnd->mapPixelToCoords((sf::Vector2i)getMouseWindowPosition());
}

sf::Vector2f Camera::getMouseWorldTilePosCenter(int tileSize) const
{
	sf::Vector2f m{ getMouseWorldPos() };
	m.x = m.x - (int)m.x % tileSize;
	m.y = m.y - (int)m.y % tileSize;

	if (m.x < 0)
		m.x -= tileSize * .5f;
	else
		m.x += tileSize * .5f;

	if (m.y < 0)
		m.y -= tileSize * .5f;
	else
		m.y += tileSize * .5f;

	return m;
}

sf::Vector2f Camera::getTilePositionCenter(float x, float y, int tileSize) const
{
	x = x - (int)x % tileSize;
	y = y - (int)y % tileSize;

	if (x < 0)
		x -= tileSize * .5f;
	else
		x += tileSize * .5f;

	if (y < 0)
		y -= tileSize * .5f;
	else
		y += tileSize * .5f;

	return {x, y};
}

sf::Vector2f Camera::getTopLeftPos() const
{
	sf::Vector2f center = *getCenter();
	sf::Vector2f size = *getSize();
	return { center.x - size.x *.5f, center.y - size.y * .5f };
}

const sf::Vector2f& Camera::getMouseWindowPosition()
{
	return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*wnd));
}

void Camera::setMouseDragButton(sf::Mouse::Button button)
{		
	dragMouseButton = button;
}

void Camera::setStopMoveKey(sf::Keyboard::Key key)
{
	stopMoveKey = key;
}

void Camera::setCenter(sf::Vector2f position)
{
	if (!isViewSet())
		return;

	currentView->setCenter(position);
}

void Camera::setBounds(const sf::FloatRect & bounds)
{
	this->bounds = bounds;
}

void Camera::setMoveable(bool Moveable)
{
	moveable = Moveable;
}

void Camera::setDragable(bool dragable)
{
	this->dragable = dragable;
}

void Camera::setSize(const sf::Vector2f & size)
{
	if (!isViewSet())
		return;

	currentView->setSize(size);
}

void Camera::setViewPort(const sf::FloatRect & viewport)
{
	if (!isViewSet())
		return;

	currentView->setViewport(viewport);
}

void Camera::setBoundaryEnabled(bool enable)
{
	boundaryEnabled = enable;
}

void Camera::setZoomMaximum(int maxState)
{
	this->zoomMax = maxState;
}

void Camera::setZoomStrength(float zoomPerLevel)
{
	this->zoomStep = zoomPerLevel;
}

void Camera::setRotation(float angle)
{
	if (!isViewSet())
		return;

	currentView->setRotation(angle);
}

bool Camera::isMoveable() const
{
	return moveable;
}

bool Camera::isDragable() const
{
	return dragable;
}

bool Camera::isBoundaryEnabled() const
{
	return boundaryEnabled;
}

const sf::FloatRect* Camera::getViewPort() const
{
	if (!isViewSet())
		return nullptr;

	return &currentView->getViewport();
}


}