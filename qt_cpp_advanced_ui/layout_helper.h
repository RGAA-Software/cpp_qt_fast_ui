#ifndef LAYOUTHELPER_H
#define LAYOUTHELPER_H

#include <QLayout>

class LayoutHelper {
public:

    static void ClearMarginSpacing(QLayout* layout) {
        layout->setMargin(0);
        layout->setSpacing(0);
    }

};

#endif // LAYOUTHELPER_H
