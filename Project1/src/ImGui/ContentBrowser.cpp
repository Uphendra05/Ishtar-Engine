#include "ContentBrowser.h"


namespace fs = std::filesystem;

static const std::filesystem::path sAssetPath = "../Project1";

ContentBrowser::ContentBrowser() : mCurrentDirectory(sAssetPath)
{


}

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



    if (mCurrentDirectory != std::filesystem::path(sAssetPath))
    {
        if (ImGui::Button("<-"))
        {
            mCurrentDirectory = mCurrentDirectory.parent_path();
        }
    }

    static float paddingThumbSize = 16.0f;
    static float thumbnailSize = 256;
    float cellSize = paddingThumbSize + thumbnailSize;
    float pandelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = (int) (pandelWidth / cellSize);
    if (columnCount < 1) columnCount = 1;

    ImGui::Columns(columnCount, 0, false);

    for (auto& directoryEntry : fs::directory_iterator(mCurrentDirectory))
    {

        const fs::path& path = directoryEntry.path();
        auto relativePath =  std::filesystem::relative(path, sAssetPath);
        std::string displayName = relativePath.filename().string();

        if (mCurrentDirectory == sAssetPath && !directoryEntry.is_directory())
            continue; 


        ImGui::Button(displayName.c_str(), { thumbnailSize,thumbnailSize });
        ImGui::Text(displayName.c_str());



        if (directoryEntry.is_directory())
        {
           /* if (ImGui::Button(displayName.c_str()))
            {
                mCurrentDirectory /= path.filename();
            }*/
        }
        else
        {
            /*if (ImGui::Button(displayName.c_str()))
            {

            }*/

        }
        
        ImGui::NextColumn();

    }



    ImGui::Columns(1);

    ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
    ImGui::SliderFloat("Padding", &paddingThumbSize, 0, 32);


    ImGui::End();

    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}
