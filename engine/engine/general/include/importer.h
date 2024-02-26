#pragma once

#include "model.h"
#include "texture.h"

namespace Nebel
{
    void import_texture(Texture &texture, const char* path);
    void import_gltf(Model &model, const char* path);
} // namespace Nebel
