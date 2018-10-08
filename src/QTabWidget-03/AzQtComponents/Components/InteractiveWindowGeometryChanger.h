/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#pragma once

#include <AzQtComponents/AzQtComponentsAPI.h>

#include <QObject>
#include <QPointer>
#include <QWindow>

class QKeyEvent;

namespace AzQtComponents
{
    /* This class is used to implement window resizing and moving through the keyboard.
    * This implement the "Size" and "Move" functionality that can be used by right clicking
    * the title bar.
    */
    class AZ_QT_COMPONENTS_API InteractiveWindowGeometryChanger
        : public QObject
    {
        Q_DISABLE_COPY(InteractiveWindowGeometryChanger)
    public:
        // The ctor changes the mouse cursor and installs a global event filter
        explicit InteractiveWindowGeometryChanger(QWindow* target, QObject* parent);

        // The dtor restores the mouse cursor and uninstalls the event filter
        ~InteractiveWindowGeometryChanger();
    protected:
        bool eventFilter(QObject* watched, QEvent* ev) override;
        virtual void handleKeyPress(QKeyEvent*) = 0;
        virtual void handleMouseMove(QMouseEvent*) = 0;
        void restoreCursorPosition();
        QPointer<QWindow> m_targetWindow;
        const QPoint m_originalCursorPos;
        bool m_restoreCursorAtExit = true;
    };

    // This implementation handles arrow key presses and resizes the window accordingly
    class AZ_QT_COMPONENTS_API InteractiveWindowResizer : public InteractiveWindowGeometryChanger
    {
    public:
        /*
        * Windows resizing works like this, right click title bar, choose "Size"
        * then the first arrow key you press will determine if you're resizing the left, top, bottom or right
        * the second arrow key press will effectively resize the window.
        */
        enum SideToResize
        {
            NoneSide = 0,
            LeftSide = 1,
            RightSide = 2,
            TopSide = 4,
            BottomSide = 8,
        };
        Q_DECLARE_FLAGS(SidesToResize, SideToResize)

        explicit InteractiveWindowResizer(QWindow* target, QObject* parent);

    protected:
        void handleKeyPress(QKeyEvent*) override;
        void handleMouseMove(QMouseEvent*) override;

    private:
        void updateCursor();
        SideToResize keyToSide(int key) const;
        bool sideIsVertical(SidesToResize) const;
        bool sideIsHorizontal(SidesToResize) const;
        bool sideIsCorner(SidesToResize) const;
        SidesToResize m_sideToResize = NoneSide;
    };

    // This implementation handles arrow key presses and moves the window accordingly
    class AZ_QT_COMPONENTS_API InteractiveWindowMover : public InteractiveWindowGeometryChanger
    {
    public:
        explicit InteractiveWindowMover(QWindow* target, QObject* parent);
    protected:
        void handleKeyPress(QKeyEvent*) override;
        void handleMouseMove(QMouseEvent*) override;
        bool m_arrowAlreadyPressed = false;
    };
} // namespace AzQtComponents