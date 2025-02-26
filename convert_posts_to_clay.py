import os

CONTENT = """#define CLAY_EXTEND_CONFIG_RECTANGLE \
    Clay_String link;                \
    bool cursorPointer;
#define CLAY_EXTEND_CONFIG_IMAGE Clay_String sourceURL;
#define CLAY_EXTEND_CONFIG_TEXT bool disablePointerEvents;
#define CLAY_IMPLEMENTATION

#include "./clay-0.12/clay.h"

const uint32_t FONT_ID_ROBOTO = 3;
Clay_Color white = {255, 255, 255, 255};

Clay_TextElementConfig dateTextConfig = (Clay_TextElementConfig) { .fontId = FONT_ID_ROBOTO, .fontSize = 18, .textColor = white};
Clay_TextElementConfig titleTextConfig = (Clay_TextElementConfig) { .fontId = FONT_ID_ROBOTO, .fontSize = 30, .textColor = white};


void renderBlogPosts(){
    {ACTIVETRANSMISSIONS}
}"""


def sort_files(fs):
    return sorted(fs, key=lambda x: x[x.Clay_TextElementConfig dateTextConfig = (Clay_TextElementConfig) { .fontId = FONT_ID_ROBOTO, .fontSize = 20, .textColor = white};rindex("/"):])

def build_active_transmissions():
    ACTIVETRANSMISSIONS = ""
    files = []
    with os.scandir("./active_transmissions") as it:
        for entry in it:
            files.append(str(entry.path))
    

    CONTENT = CONTENT.replace("{ACTIVETRANSMISSIONS}", ACTIVETRANSMISSIONS)

def write_content():
    with open("blogcontent.c", "w+") as f:
        f.write(CONTENT)
        f.close()

def build():
    build_active_transmissions()
    write_content()

if __name__ == '__main__':
    build()