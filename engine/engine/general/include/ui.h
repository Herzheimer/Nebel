#pragma once

#include "transform.h"
#include "texture.h"
#include <vector>
#include <unordered_map>

namespace Nebel
{
    enum class UiType
    {
        UiNull,
        UiImage,
        UiBox,
        UiText,
        UiCustom,
    };
    enum class UiUnitType
    {
        UiCenter,
        UiPixel,
        UiPercent,
        UiEm,
    };
    enum class UiOriginType
    {
        UiOriginCenter,
        UiOriginTopLeft,
        UiOriginTopRight,
        UiOriginBottomLeft,
        UiOriginBottomRight,
        //UiOriginCustom,
    };
    enum class UiAnkerType
    {
        UiAnkerCenter,
        UiAnkerTop,
        UiAnkerLeft,
        UiAnkerRight,
        UiAnkerBottom,
        //UiAnkerCustom,
    };
    enum class UiPositionType
    {
        UiAbsolute,
        UiRelative,
        //UiFlexElement,
        //UiParentPositionType,
    };
    struct UiActionComponent
    {
    };
    struct UiStyleComponent
    {
    };
    struct UiRenderable
    {
    };
    struct UiNode
    {
        UiOriginType origin_type = UiOriginType::UiOriginTopLeft;
        UiAnkerType anker_type_x = UiAnkerType::UiAnkerLeft; // TODO
        UiAnkerType anker_type_y = UiAnkerType::UiAnkerTop; //TODO
        UiPositionType position_type = UiPositionType::UiRelative; //TODO
        Transform2D transform;
        UiUnitType position_unit_x = UiUnitType::UiPercent;
        UiUnitType position_unit_y = UiUnitType::UiPercent;
        UiUnitType scale_unit_x = UiUnitType::UiEm;
        UiUnitType scale_unit_y = UiUnitType::UiEm;
        UiRenderable* element;
        UiType type = UiType::UiNull;
        UiNode* parent = nullptr;
        std::vector<UiNode> children;
        std::vector<UiActionComponent> action_components; //TODO
        std::vector<UiStyleComponent> style_components; //TODO
        glm::mat4 matrix;
        void recalculate();
        void render();
    };
    struct UiImage : UiRenderable
    {
        Texture tex1;
    };
    struct UiBox : UiRenderable
    {
        //
    };
    struct UiPage // : UiNode // : UiRenderable
    {
        std::vector<UiNode> nodes;
    };
    struct UiSystem
    {
        std::vector<UiNode> nodes;
        std::vector<UiPage> pages;
        std::unordered_map<uint32_t, UiImage> ui_images;
        std::unordered_map<uint32_t, UiBox> boxes;
        void render();
    };
} // namespace Nebel
