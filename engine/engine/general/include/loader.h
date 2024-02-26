#pragma once

#include "model.h"

namespace Nebel
{
    void loadModel(AnimatedModel &model, const char* path);
    void loadModel(StaticModel &model, const char* path);
} // namespace Nebel
