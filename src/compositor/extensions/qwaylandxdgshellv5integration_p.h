/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWaylandCompositor module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWAYLANDXDGSHELLV5INTEGRATION_H
#define QWAYLANDXDGSHELLV5INTEGRATION_H

#include <QtWaylandCompositor/private/qwaylandquickshellsurfaceitem_p.h>
#include <QtWaylandCompositor/QWaylandXdgSurfaceV5>

QT_BEGIN_NAMESPACE

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

namespace QtWayland {

class XdgShellV5Integration : public QWaylandQuickShellIntegration
{
    Q_OBJECT
public:
    XdgShellV5Integration(QWaylandQuickShellSurfaceItem *item);
    ~XdgShellV5Integration() override;

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private Q_SLOTS:
    void handleStartMove(QWaylandSeat *seat);
    void handleStartResize(QWaylandSeat *seat, QWaylandXdgSurfaceV5::ResizeEdge edges);
    void handleSetTopLevel();
    void handleSetTransient();
    void handleSetMaximized();
    void handleUnsetMaximized();
    void handleMaximizedChanged();
    void handleActivatedChanged();
    void handleSurfaceSizeChanged();

private:
    enum class GrabberState {
        Default,
        Resize,
        Move
    };
    QWaylandQuickShellSurfaceItem *m_item = nullptr;
    QWaylandXdgSurfaceV5 *m_xdgSurface = nullptr;

    GrabberState grabberState;
    struct {
        QWaylandSeat *seat = nullptr;
        QPointF initialOffset;
        bool initialized = false;
    } moveState;

    struct {
        QWaylandSeat *seat = nullptr;
        QWaylandXdgSurfaceV5::ResizeEdge resizeEdges;
        QSizeF initialWindowSize;
        QPointF initialMousePos;
        QPointF initialPosition;
        QSize initialSurfaceSize;
        bool initialized = false;
    } resizeState;

    struct {
        QSize initialWindowSize;
        QPointF initialPosition;
    } maximizeState;

    bool filterMouseMoveEvent(QMouseEvent *event);
    bool filterMouseReleaseEvent(QMouseEvent *event);
};

class XdgPopupV5Integration : public QWaylandQuickShellIntegration
{
    Q_OBJECT
public:
    XdgPopupV5Integration(QWaylandQuickShellSurfaceItem *item);
    ~XdgPopupV5Integration() override;

private Q_SLOTS:
    void handlePopupDestroyed();

private:
    QWaylandQuickShellSurfaceItem *m_item = nullptr;
    QWaylandXdgPopupV5 *m_xdgPopup = nullptr;
    QWaylandXdgShellV5 *m_xdgShell = nullptr;
};

}

QT_END_NAMESPACE

#endif // QWAYLANDXDGSHELLV5INTEGRATION_H
