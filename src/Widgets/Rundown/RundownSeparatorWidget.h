#pragma once

#include "../Shared.h"
#include "AbstractRundownWidget.h"
#include "ui_RundownSeparatorWidget.h"

#include "Global.h"

#include "Animations/ActiveAnimation.h"
#include "Commands/AbstractCommand.h"
#include "Commands/AbstractPlayoutCommand.h"
#include "Commands/SeparatorCommand.h"
#include "Events/Inspector/LabelChangedEvent.h"
#include "Models/LibraryModel.h"

#include <stdexcept>

#include <QtCore/QString>
#include <QtCore/QObject>

#include <QtWidgets/QWidget>

class WIDGETS_EXPORT RundownSeparatorWidget : public QWidget, Ui::RundownSeparatorWidget, public AbstractRundownWidget, public AbstractPlayoutCommand
{
    Q_OBJECT

    public:
        explicit RundownSeparatorWidget(const LibraryModel& model, QWidget* parent = 0,
                                        const QString& color = Color::DEFAULT_SEPARATOR_COLOR,
                                        bool active = false, bool inGroup = false, bool compactView = false);

        virtual AbstractRundownWidget* clone();

        virtual bool isGroup() const;
        virtual bool isInGroup() const;
        virtual bool executeCommand(Playout::PlayoutType type);

        virtual AbstractCommand* getCommand();
        virtual LibraryModel* getLibraryModel();

        virtual QString getColor() const;

        virtual void setExpanded(bool /* expanded */) {}
        virtual void setActive(bool active);
        virtual void setInGroup(bool inGroup);
        virtual void setColor(const QString& color);
        virtual void readProperties(boost::property_tree::wptree& pt);
        virtual void writeProperties(QXmlStreamWriter& writer);
        virtual void setCompactView(bool compactView);
        virtual void clearDelayedCommands() {}
        virtual void setUsed(bool /* used */) {}
        virtual void setSelected(bool selected);

    private:
        bool active;
        bool inGroup;
        bool compactView;
        QString color;
        LibraryModel model;
        SeparatorCommand command;
        ActiveAnimation* animation;
        bool selected = false;

        Q_SLOT void labelChanged(const LabelChangedEvent&);
};
