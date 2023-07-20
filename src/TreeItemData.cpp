#include "inc/TreeItemData.h"

#include <QDebug>

TreeItemData::TreeItemData(QObject* parent) : QObject(parent)
{
    m_text = "";
    m_indentation = 0;
    m_type = "";
    m_icon = "";
}

TreeItemData::TreeItemData(const TreeItemData& other)
{
    m_text = other.m_text;
    m_indentation = other.m_indentation;
    m_icon = other.m_icon;
    m_type = other.m_type;
}

TreeItemData::~TreeItemData()
{
}

QString TreeItemData::text()
{
    return m_text;
}

void TreeItemData::setText(const QString& text)
{
    m_text = text;
    emit textChanged();
}

int TreeItemData::indentation()
{
    return m_indentation;
}

void TreeItemData::setIndentation(int indentation)
{
    m_indentation = indentation;
    emit indentationChanged();
}

QString TreeItemData::icon()
{
    return m_icon;
}

void TreeItemData::setIcon(const QString& icon)
{
    m_icon = icon;
    emit iconChanged();
}

QString TreeItemData::type()
{
    return m_type;
}

void TreeItemData::setType(const QString& type)
{
    m_type = type;
    setIcon(iconMap.value(type, ""));
}
