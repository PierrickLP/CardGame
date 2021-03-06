/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_CONTAINER_HPP
#define TGUI_CONTAINER_HPP


#include <list>

#include <TGUI/Widget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Container widget
    ///
    /// Parent class for widgets that store multiple widgets.
    ///
    /// Signals:
    ///     - Inherited signals from Widget
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API Container : public Widget
    {
      public:

        typedef std::shared_ptr<Container> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const Container> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Copy constructor
        ///
        /// @param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container(const Container& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~Container();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Overload of assignment operator
        ///
        /// @param right  Instance to assign
        ///
        /// @return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container& operator= (const Container& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a list of all the widgets
        ///
        /// @return Vector of all widget pointers
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::vector<Widget::Ptr>& getWidgets() const
        {
            return m_widgets;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a list of the names of all the widgets
        ///
        /// @return Vector of all widget names
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::vector<sf::String>& getWidgetNames() const
        {
            return m_widgetNames;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a widget to the container
        ///
        /// @param widgetPtr   Pointer to the widget you would like to add
        /// @param widgetName  If you want to access the widget later then you must do this with this name
        ///
        /// @warning The widget name should not contain whitespace
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void add(const Widget::Ptr& widgetPtr, const sf::String& widgetName = "");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a pointer to an earlier created widget
        ///
        /// @param widgetName The name that was given to the widget when it was added to the container
        /// @param recursive  Should the function also search for widgets inside containers that are inside this container?
        ///
        /// @return Pointer to the earlier created widget
        ///
        /// @warning This function will return nullptr when an unknown widget name was passed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr get(const sf::String& widgetName, bool recursive = false) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a pointer to an earlier created widget
        ///
        /// @param widgetName The name that was given to the widget when it was added to the container
        /// @param recursive  Should the function also search for widgets inside containers that are inside this container?
        ///
        /// @return Pointer to the earlier created widget.
        ///         The pointer will already be casted to the desired type
        ///
        /// @warning This function will return nullptr when an unknown widget name was passed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <class T>
        typename T::Ptr get(const sf::String& widgetName, bool recursive = false) const
        {
            return std::dynamic_pointer_cast<T>(get(widgetName, recursive));
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a single widget that was added to the container
        ///
        /// @param widget  Pointer to the widget to remove
        ///
        /// @return True when widget is removed, false when widget was not found
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool remove(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all widgets that were added to the container
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void removeAllWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the name of a widget
        ///
        /// @param widget  Widget of which the name should be changed
        /// @param name    New name for the widget
        ///
        /// @return True when the name was changed, false when the widget wasn't part of this container.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setWidgetName(const Widget::Ptr& widget, const std::string& name);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the name of a widget
        ///
        /// @param widget  Widget of which the name should be retrieved
        ///
        /// @return Name of the widget or an empty string when the widget didn't exist or wasn't given a name
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string getWidgetName(const Widget::Ptr& widget) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Focuses a widget
        ///
        /// The previously focused widget will be unfocused.
        ///
        /// @param widget  The widget that has to be focused
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void focusWidget(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Focuses the next widget
        ///
        /// The currently focused widget will be unfocused, even if it was the only widget.
        /// When no widget was focused, the first widget in the container will be focused.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void focusNextWidget();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Focuses the previous widget
        ///
        /// The currently focused widget will be unfocused, even if it was the only widget.
        /// When no widget was focused, the last widget in the container will be focused.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void focusPreviousWidget();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Unfocuses all the widgets
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void unfocusWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Unchecks all the radio buttons
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void uncheckRadioButtons();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the distance between the position of the container and a widget that would be drawn inside
        ///        this container on relative position (0,0)
        ///
        /// @return Offset of the widgets in the container
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getChildWidgetsOffset() const
        {
            return sf::Vector2f{0, 0};
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the child widgets from a text file
        ///
        /// @param filename  Filename of the widget file
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void loadWidgetsFromFile(const std::string& filename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the child widgets to a text file
        ///
        /// @param filename  Filename of the widget file
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void saveWidgetsToFile(const std::string& filename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the child widgets from a string stream
        ///
        /// @param stream  stringstream that contains the widget file
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void loadWidgetsFromStream(std::stringstream& stream);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the child widgets to a text file
        ///
        /// @param stream  stringstream to which the widget file will be added
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void saveWidgetsToStream(std::stringstream& stream);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Places a widget before all other widgets
        ///
        /// @param widget  The widget that should be moved to the front
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveWidgetToFront(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Places a widget behind all other widgets
        ///
        /// @param widget  The widget that should be moved to the back
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveWidgetToBack(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void keyPressed(const sf::Event::KeyEvent& event) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void textEntered(sf::Uint32 key) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseWheelScrolled(float delta, int x, int y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerOnWidget() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerDown() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetUnfocused() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        // Shows the tool tip when the widget is located below the mouse.
        // Returns its tool tip or the tool tip from a child widget if the mouse is on top of the widget.
        // A nullptr is returned when the mouse is not on top of the widget or when the tool tip is empty.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr askToolTip(sf::Vector2f mousePos) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Lowercase name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void rendererChanged(const std::string& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called every frame with the time passed since the last frame.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void update(sf::Time elapsedTime) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When this function is called then all the widgets receive the event (if there are widgets).
        // The function returns true when the event is consumed and false when the event was ignored by all widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool handleEvent(sf::Event& event);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Focuses the next widget in the container. If the last widget was focused then all widgets will be unfocused and
        // this function will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool focusNextWidgetInContainer();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When the tab key is pressed then this function is called. The focus will move to the next widget (if there is one).
        // This function will only work when tabKeyUsageEnabled is true.
        // The function will return true when another widget was focused.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool tabKeyPressed();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Checks above which widget the mouse is standing.
        // If there is no widget below the mouse then this function will return a null pointer.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr mouseOnWhichWidget(sf::Vector2f mousePos);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will call the draw function from all the widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void drawWidgetContainer(sf::RenderTarget* target, const sf::RenderStates& states = sf::RenderStates::Default) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        std::vector<Widget::Ptr> m_widgets;
        std::vector<sf::String>  m_widgetNames;

        Widget::Ptr m_widgetBelowMouse;

        // The id of the focused widget
        std::size_t m_focusedWidget = 0;

        // Did we enter handleEvent directly or because we got a MouseReleased event?
        bool m_handingMouseReleased = false;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @internal
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API GuiContainer : public Container
    {
    public:

        typedef std::shared_ptr<GuiContainer> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const GuiContainer> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        GuiContainer();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Doesn't has any effect
        ///
        /// @param size  Ignored
        ///
        /// The window size cannot be changed by a widget.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(const Layout2d& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// Returns false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(sf::Vector2f pos) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function does nothing.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns a nullptr.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() const override
        {
            return nullptr;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        sf::RenderTarget* m_window = nullptr;

        friend class Gui; // Required to let Gui access protected members from container and Widget

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_CONTAINER_HPP
