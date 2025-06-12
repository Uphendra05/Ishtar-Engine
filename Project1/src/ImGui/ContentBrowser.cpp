#include "ContentBrowser.h"

void ContentBrowser::OnRender(float windowWidth, float windowHeight)
{

    // isEnable = false;
    if (!isPanelOpen)
    {
        return;
    }


    ImGuiStyle& style = ImGui::GetStyle();

    float lineHeight = ImGui::GetFontSize() + style.FramePadding.y * 2;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, windowColor);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    if (!ImGui::Begin("Content Browser", &isPanelOpen) || !isEnable)
    {
        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        return;

    }

    ImVec2 viewPortPanelSize = ImGui::GetContentRegionAvail();

    isHovered = ImGui::IsWindowHovered();

    float cameraAspectRatio = viewPortRes.x / viewPortRes.y;
    float viewportRatio = viewPortPanelSize.x / viewPortPanelSize.y;


    ImVec2 renderSize;
    ImVec2 renderPos;
    ImVec2 padding;


    if (viewportRatio > cameraAspectRatio)
    {
        renderSize.y = viewPortPanelSize.y;
        renderSize.x = renderSize.y * cameraAspectRatio;
        renderPos.x = (viewPortPanelSize.x - renderSize.x) * 0.5f;
        renderPos.y = 0;
    }
    else
    {
        renderSize.x = viewPortPanelSize.x;
        renderSize.y = renderSize.x / cameraAspectRatio;
        renderPos.x = 0;
        renderPos.y = (viewPortPanelSize.y - renderSize.y) * 0.5f;

    }

    renderPos.y += lineHeight;

    renderPos.x *= -0.0005f;

   

    ImGui::End();

    ImGui::PopStyleColor();
    ImGui::PopStyleVar();

}
