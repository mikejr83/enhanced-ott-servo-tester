#include "settings.h"

#include "OTTMenu.h"

#include <menu.h>
#include <menuIO/serialOut.h>
#include <menuIO/serialIn.h>
#include <menuIO/analogAxisIn.h>
#include <menuIO/keyIn.h>
#include <menuIO/chainStream.h>

using namespace Menu;

confirmExit::confirmExit(constMEM menuNodeShadow &shadow) : menu(shadow) {}

Used confirmExit::printTo(navRoot &root, bool sel, menuOut &out, idx_t idx, idx_t len, idx_t p)
{
    if (idx < 0)
    {
        menu::printTo(root, sel, out, idx, len, p);
    }
    else
    {
        out.printRaw((constText *)F("Exit"), len);
    }
    return idx;
}