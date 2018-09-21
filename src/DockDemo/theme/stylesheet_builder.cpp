#include "stylesheet_builder.h"

#include <QColor>
#include <QApplication>
#include <QWidget>


// --- StyleSelector ----------------------------------------------------------

StyleSelector::StyleSelector(StylesheetBuilder& builder, const QString& name) :
    parent(builder),
    name(name)
{
    //
}

StyleSelector& StyleSelector::selector(const QString& name)
{
    return builder().selector(name);
}

StyleSelector &StyleSelector::attr(const QString &attrName)
{
    name += QString("[%1]").arg(attrName);
    return *this;
}

StyleSelector& StyleSelector::attr(const QString& attrName, const QString& attrValue)
{
    name += QString("[%1=\"%2\"]").arg(attrName).arg(attrValue);
    return *this;
}

StyleSelector& StyleSelector::child(const QString& name)
{
    this->name += " " + name;
    return *this;
}

StylesheetBuilder& StyleSelector::builder()
{
    parent.style << QString("%1 {%2}").arg(this->name).arg(this->style.join("; "));
    return parent;
}

StyleSelector& StyleSelector::set(const QString& name, const char* value)
{
    style << QString("%1: %2").arg(name).arg(value);
    return *this;
}

StyleSelector& StyleSelector::set(const QString& name, const QString& value)
{
    style << QString("%1: %2").arg(name).arg(value);
    return *this;
}

StyleSelector& StyleSelector::set(const QString& name, const QColor& value)
{
    return set(name, value.name());
}

StyleSelector &StyleSelector::setBackground(const char *value)
{
    style << QString("background: %1").arg(value);
    return *this;
}

StyleSelector& StyleSelector::setBackground(const QColor& value)
{
    style << QString("background: %1").arg(value.name());
    return *this;
}

StyleSelector& StyleSelector::setBorder(int width, const QColor& value)
{
    style << QString("border: %1px solid %2").arg(width).arg(value.name());
    return *this;
}

StyleSelector& StyleSelector::setBorderBottom(int width, const QColor& value)
{
    style << QString("border-bottom: %1px solid %2").arg(width).arg(value.name());
    return *this;
}

StyleSelector& StyleSelector::setBorderRadius(int radius)
{
    style << QString("border-radius: %1px").arg(radius);
    return *this;
}

StyleSelector& StyleSelector::setColor(const QColor& value)
{
    style << QString("color: %1").arg(value.name());
    return *this;
}

// --- StylesheetBuilder ------------------------------------------------------

StylesheetBuilder::StylesheetBuilder() :
    sel(NULL)
{
    //
}

StylesheetBuilder& StylesheetBuilder::set(const QString& sel, const QString& name, const QString& value)
{
    return selector(sel).set(name, value).builder();
}

StylesheetBuilder& StylesheetBuilder::set(const QString& sel, const QString& name, const QColor& value)
{
    return selector(sel).set(name, value).builder();
}

StylesheetBuilder& StylesheetBuilder::assignToApplication()
{
    qApp->setStyleSheet(toString());
    return *this;
}

StylesheetBuilder& StylesheetBuilder::assignTo(QWidget* widget)
{
    widget->setStyleSheet(toString());
    return *this;
}

StyleSelector& StylesheetBuilder::selector(const QString &name)
{
    sel.reset(new StyleSelector(*this, name));
    return *sel;
}

QString StylesheetBuilder::toString() const
{
    return style.join("\n");
}
