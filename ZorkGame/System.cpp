#include "System.h"

#include <Windows.h>
#include <fstream>

std::string System::getSaveFilePath(void) {
    wchar_t filename[MAX_PATH] = L"";

    OPENFILENAMEW ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFilter = L"JSON Files\0*.json\0All Files\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrDefExt = L"json";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

    if (GetSaveFileNameW(&ofn)) {
        // convert wide string back to std::string
        std::wstring ws(filename);
        return std::string(ws.begin(), ws.end());
    }
    return "";
}


void System::saveGame(World *world) {
    std::string path = getSaveFilePath();
    nlohmann::json worldJson;

    if (path.empty()) {
        printDialogue("Save cancelled.\n");
        return;
    }
    worldJson = world->toJson();

    std::ofstream file(path);

    if (file.is_open()) {
        file << worldJson.dump(2);
        file.close();
        printDialogue("Game saved successfully.\n");
    }
    else {
        printDialogue("Error saving game.\n");
    }
}
