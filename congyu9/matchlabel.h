#ifndef MATCHLABEL_H
#define MATCHLABEL_H

#include <QLabel>

class MatchLabel : public QLabel
{
    Q_OBJECT

public:
    explicit MatchLabel(QWidget* parent=nullptr);

    void play();
};

#endif
