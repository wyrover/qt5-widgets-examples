#pragma once

#include <QStringList>
#include <QScopedPointer>


class StylesheetBuilder;
class QWidget;
class StyleSelector;

class StyleSelector
{
    friend class StylesheetBuilder;
private:
    StyleSelector(StylesheetBuilder& builder, const QString& name);
public:
    StyleSelector& selector(const QString& name);
    StyleSelector& attr(const QString& attrName);
    StyleSelector& attr(const QString& attrName, const QString& attrValue);
    StyleSelector& child(const QString& name);
    StylesheetBuilder& builder();
    StyleSelector& set(const QString& name, const char* value);
    StyleSelector& set(const QString& name, const QString& value);
    StyleSelector& set(const QString& name, const QColor& value);
    StyleSelector& setBackground(const char* value);
    StyleSelector& setBackground(const QColor& value);
    StyleSelector& setBorder(int width, const QColor& value);
    StyleSelector& setBorderBottom(int width, const QColor& value);
    StyleSelector& setBorderRadius(int radius);
    StyleSelector& setColor(const QColor& value);
private:
    StylesheetBuilder&  parent;
    QString             name;
    QStringList         style;
};


class StylesheetBuilder
{
    friend class StyleSelector;

public:
    StylesheetBuilder();

public:
    StylesheetBuilder& set(const QString& sel, const QString& name, const QString& value);
    StylesheetBuilder& set(const QString& sel, const QString& name, const QColor& value);
    StyleSelector& selector(const QString& name);
    StylesheetBuilder& assignToApplication();
    StylesheetBuilder& assignTo(QWidget* widget);
    QString toString() const;

private:
    QStringList     style;
    QScopedPointer<StyleSelector>   sel;
};
