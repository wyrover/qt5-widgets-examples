/*
 * Copyright (c) 2006-2007, Johan Thelin
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 *     * Neither the name of APress nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <QApplication>

#include <QTreeView>

#include "objecttreemodel.h"

#include <QtPlugin>
#if defined(Q_OS_WIN32)
    Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#elif defined(Q_OS_MAC)
    Q_IMPORT_PLUGIN(QCocoaIntegrationPlugin)
#endif

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QObject root;
    root.setObjectName("root");
    QObject *child;
    QObject *foo = new QObject(&root);
    foo->setObjectName("foo");
    child = new QObject(foo);
    child->setObjectName("Mark");
    child = new QObject(foo);
    child->setObjectName("Bob");
    child = new QObject(foo);
    child->setObjectName("Kent");
    QObject *bar = new QObject(&root);
    bar->setObjectName("bar");
//+. main
    child = new QObject(bar);
    child->setObjectName("Ole");
    child = new QObject(bar);
    child->setObjectName("Trond");
    child = new QObject(bar);
    child->setObjectName("Kjetil");
    child = new QObject(bar);
    child->setObjectName("Lasse");
    QObject *baz = new QObject(&root);
    baz->setObjectName("baz");
    child = new QObject(baz);
    child->setObjectName("Bengt");
    child = new QObject(baz);
    child->setObjectName("Sven");
//-. main
    ObjectTreeModel model(&root);
    QTreeView tree;
    tree.setModel(&model);
    tree.show();
    return app.exec();
}
