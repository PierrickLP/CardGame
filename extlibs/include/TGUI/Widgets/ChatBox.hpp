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


#ifndef TGUI_CHAT_BOX_HPP
#define TGUI_CHAT_BOX_HPP


#include <TGUI/Widgets/Scrollbar.hpp>
#include <TGUI/Renderers/ChatBoxRenderer.hpp>
#include <TGUI/Text.hpp>
#include <deque>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API ChatBox : public Widget
    {
    public:

        typedef std::shared_ptr<ChatBox> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const ChatBox> ConstPtr; ///< Shared constant widget pointer

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        struct Line
        {
            Text text;
            sf::String string;
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChatBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new chat box widget
        ///
        /// @return The new chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static ChatBox::Ptr create();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another chat box
        ///
        /// @param chatBox  The other chat box
        ///
        /// @return The new chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static ChatBox::Ptr copy(ChatBox::ConstPtr chatBox);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        ///
        /// @return Temporary pointer to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChatBoxRenderer* getRenderer() const
        {
            return aurora::downcast<ChatBoxRenderer*>(m_renderer.get());
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the position of the widget
        ///
        /// @param position  New position
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPosition(const Layout2d& position) override;
        using Transformable::setPosition;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the chat box
        ///
        /// This size does not include the borders.
        ///
        /// @param size   The new size of the chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new line of text to the chat box
        ///
        /// The whole text passed to this function will be considered as one line for the getLine and removeLine functions,
        /// even if it is too long and gets split over multiple lines.
        ///
        /// The default text color and character size will be used.
        ///
        /// @param text  Text that will be added to the chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addLine(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new line of text to the chat box
        ///
        /// The whole text passed to this function will be considered as one line for the getLine and removeLine functions,
        /// even if it is too long and gets split over multiple lines.
        ///
        /// The default text color will be used.
        ///
        /// @param text      Text that will be added to the chat box
        /// @param textSize  Size of the text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addLine(const sf::String& text, unsigned int textSize);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new line of text to the chat box
        ///
        /// The whole text passed to this function will be considered as one line for the getLine and removeLine functions,
        /// even if it is too long and gets split over multiple lines.
        ///
        /// The default character size will be used.
        ///
        /// @param text   Text that will be added to the chat box
        /// @param color  Color of the text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addLine(const sf::String& text, const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new line of text to the chat box
        ///
        /// The whole text passed to this function will be considered as one line for the getLine and removeLine functions,
        /// even if it is too long and gets split over multiple lines.
        ///
        /// @param text      Text that will be added to the chat box
        /// @param color     Color of the text
        /// @param textSize  Size of the text
        /// @param font      Font of the text (nullptr to use default font)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addLine(const sf::String& text, const sf::Color& color, unsigned int textSize, const Font& font = nullptr);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the contents of the requested line
        ///
        /// @param lineIndex  The index of the line of which you request the contents
        ///                   The first line has index 0
        ///
        /// @return The contents of the requested line
        ///         An empty string will be returned when the index is too high
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getLine(std::size_t lineIndex) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the color of the requested line
        ///
        /// @param lineIndex  The index of the line of which you request the color. The first line has index 0
        ///
        /// @return The color of the requested line. The default color (set with setTextColor) when the index is too high
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Color getLineColor(std::size_t lineIndex) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text size of the requested line
        ///
        /// @param lineIndex  The index of the line of which you request the text size. The first line has index 0
        ///
        /// @return The text size of the requested line. The default text size (set with setTextSize) when the index is too high
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getLineTextSize(std::size_t lineIndex) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the font of the requested line
        ///
        /// @param lineIndex  The index of the line of which you request the font. The first line has index 0
        ///
        /// @return The font of the requested line.
        ///         When the index is too high then the default font (set with chatBox->getRenderer()->setFont(font)) is returned.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<sf::Font> getLineFont(std::size_t lineIndex) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes the requested line
        ///
        /// @param lineIndex  The index of the line that should be removed
        ///                   The first line has index 0
        ///
        /// @return True if the line was removed, false if no such line existed (index too high)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeLine(std::size_t lineIndex);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all lines from the chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllLines();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the amount of lines in the chat box
        ///
        /// @return Number of lines in the chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getLineAmount();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a maximum amount of lines in the chat box
        ///
        /// Only the last maxLines lines will be kept. Lines above those will be removed.
        /// Set to 0 to disable the line limit (default).
        ///
        /// @param maxLines  The maximum amount of lines that the chat box can contain
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setLineLimit(std::size_t maxLines);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum amount of lines in the chat box
        ///
        /// Only the last maxLines lines will be kept. Lines above those will be removed.
        /// Disabled when set to 0 (default).
        ///
        /// @return The maximum amount of lines that the chat box can contain
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getLineLimit();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the default character size of the text
        ///
        /// @param size  The new default text size
        ///              The minimum text size is 8
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the default character size of the text
        ///
        /// @return The currently used default text size
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the default color of the text
        ///
        /// @param color  The new default text color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(Color color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the default color of the text
        ///
        /// @return The currently used default text color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getTextColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Lets the first lines start from the top or from the bottom of the chat box
        ///
        /// Note that this only makes a difference when the lines don't fill the entire chat box.
        /// This does not change the order of the lines, new lines will always be below older lines.
        ///
        /// @param startFromTop  Let the first lines be placed at the top of the chat box, or remain at the bottom?
        ///
        /// By default the first lines will be placed at the bottom of the chat box.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setLinesStartFromTop(bool startFromTop = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the first lines start from the top or from the bottom of the chat box
        ///
        /// Note that this only makes a difference when the lines don't fill the entire chat box.
        /// This does not change the order of the lines, new lines will always be below older lines.
        ///
        /// @return Are the first lines displayed at the top of the chat box?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getLinesStartFromTop() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets whether new lines are added below the other lines or above them
        ///
        /// @param newLinesBelowOthers  Should the addLine function insert the line below the existing lines?
        ///
        /// By default the new lines are always added below the others.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setNewLinesBelowOthers(bool newLinesBelowOthers = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether new lines are added below the other lines or above them
        ///
        /// @return Does the addLine function insert the line below the existing lines?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getNewLinesBelowOthers() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(sf::Vector2f pos) const override;

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
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculates the text attribute of the line
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculateLineText(Line& line);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculates all text attributes, recalculate the full text height and update the displayed text
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculateAllLines();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculates the space used by all the lines
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculateFullTextHeight();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the position of the lines
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateDisplayedText();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the position and size of the panel and scrollbar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateRendering();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


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
        // Returns the size without the borders
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getInnerSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() const override
        {
            return std::make_shared<ChatBox>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        unsigned int m_textSize = 18;
        sf::Color m_textColor = sf::Color::Black;

        std::size_t m_maxLines = 0;

        float m_fullTextHeight = 0;

        bool m_linesStartFromTop = false;
        bool m_newLinesBelowOthers = true;

        ScrollbarChildWidget m_scroll;

        std::deque<Line> m_lines;

        Sprite m_spriteBackground;

        // Cached renderer properties
        Borders m_bordersCached;
        Padding m_paddingCached;
        Color   m_backgroundColorCached;
        Color   m_borderColorCached;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TEXT_BOX_HPP
