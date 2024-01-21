#pragma once

#include <menu.h>

class confirmExit : public menu
{
public:
    confirmExit(constMEM menuNodeShadow &shadow);
    Used printTo(navRoot &root, bool sel, menuOut &out, idx_t idx, idx_t len, idx_t p) override;
};