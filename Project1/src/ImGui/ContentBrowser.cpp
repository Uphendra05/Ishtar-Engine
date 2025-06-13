#include "ContentBrowser.h"


namespace fs = std::filesystem;

static const std::filesystem::path sAssetPath = "../Project1";

ContentBrowser::ContentBrowser() : mCurrentDirectory(sAssetPath)
{
    fileFolderIcon = new Texture("Textures/Content Browser/Filefolder2.png");
    fileIcon = new Texture("Textures/Content Browser/FileIcon.png");

}

ContentBrowser::~ContentBrowser()
{
    delete fileFolderIcon;
    delete fileIcon;
}

void ContentBrowser::OnRender(float windowWidth, float windowHeight)
{


    // isEnable = false;
    if (!isPanelOpen)
    {
        return;
    }


    ImGuiStyle& style = ImGui::GetStyle();


    ImGui::PushStyleColor(ImGuiCol_WindowBg, windowColor);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    if (!ImGui::Begin("Content Browser", &isPanelOpen) || !isEnable)
    {
        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        return;

    }


    isHovered = ImGui::IsWindowHovered();

    


    if (mCurrentDirectory != std::filesystem::path(sAssetPath))
    {
        if (ImGui::Button("<-"))
        {
            mCurrentDirectory = mCurrentDirectory.parent_path();
        }
    }
    

    static float paddingThumbSize = 16.0f;
    static float thumbnailSize = 128.0f;
    float cellSize = paddingThumbSize + thumbnailSize;
    float pandelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = (int) (pandelWidth / cellSize);
    if (columnCount < 1) columnCount = 1;

    ImGui::Columns(columnCount, 0, false);

    if (!fs::exists(mCurrentDirectory) || !fs::is_directory(mCurrentDirectory)) {
        std::cerr << "Invalid directory: " << mCurrentDirectory << "\n";
        mCurrentDirectory = sAssetPath; 
        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        return;
    }

    std::string displayName;
    try {

        for (auto& directoryEntry : fs::directory_iterator(mCurrentDirectory))
        {
            const auto& path = directoryEntry.path();
            auto relativePath = std::filesystem::relative(path, sAssetPath);
            displayName = relativePath.filename().string();


            if (mCurrentDirectory == sAssetPath && !directoryEntry.is_directory())
                continue;

             Texture* tempTexture = directoryEntry.is_directory() ? fileFolderIcon : fileIcon;

            ImGui::PushID(displayName.c_str());
            ImGui::ImageButton((ImTextureID)(intptr_t)tempTexture->id , { thumbnailSize,thumbnailSize });
            if (ImGui::IsItemActive() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                if (directoryEntry.is_directory())
                {

                    mCurrentDirectory /= path.filename();
                }
            }


           
            ImGui::PopID();
            ImGui::Text(displayName.c_str());
            ImGui::NextColumn();

        }

    }
    catch (const fs::filesystem_error& e)
    {
            std::cerr << "Filesystem error: " << e.what() << "\n";
            std::cerr << "Path1: " << e.path1() << "\n";
            std::cerr << "Path2: " << e.path2() << "\n";
    }

    ImGui::Columns(1);

    ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
    ImGui::SliderFloat("Padding", &paddingThumbSize, 0, 32);


    ImGui::End();

    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}
