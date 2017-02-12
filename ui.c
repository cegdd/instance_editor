#include "ui.h"

void UI_setslidestate (int state, struct UI* ui)
{
    ui->slidestate = state;
}

int UI_getslidestate(struct UI* ui)
{
    return ui->slidestate;
}
