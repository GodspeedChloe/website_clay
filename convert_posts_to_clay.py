import os
import xml.etree.ElementTree as ET

CONTENT = """#define CLAY_EXTEND_CONFIG_RECTANGLE \
    Clay_String link;                \
    bool cursorPointer;
#define CLAY_EXTEND_CONFIG_IMAGE Clay_String sourceURL;
#define CLAY_EXTEND_CONFIG_TEXT bool disablePointerEvents;
#define CLAY_IMPLEMENTATION

#include "./clay-0.12/clay.h"

const uint32_t FONT_ID_ROBOTO = 3;
Clay_Color white = {255, 255, 255, 255};

Clay_TextElementConfig dateTextConfig = (Clay_TextElementConfig) { .fontId = FONT_ID_ETB_ROMAN, .fontSize = 18, .textColor = white};
Clay_TextElementConfig titleTextConfig = (Clay_TextElementConfig) { .fontId = FONT_ID_ETB_ROMAN, .fontSize = 30, .textColor = white};


void renderBlogPosts(){
    {ACTIVETRANSMISSIONS}
}"""

def parse_file(file):
    lines = []
    content = ""
    with open(file, "r+") as f:
        tree = ET.parse(f)
        root = tree.getroot()
        for item in root.findall('.'):
            for child in item:
                print(child.tag) 
    return content

def sort_files(fs):
    return sorted(fs, key=lambda x: x[x.rindex("/"):], reverse=True)

def build_active_transmissions(c):
    ACTIVETRANSMISSIONS = ""
    files = []
    with os.scandir("./active_transmissions") as it:
        for entry in it:
            files.append(str(entry.path))
    files = sort_files(files)
    for f in files:
        print("Parsing file: "+f)
        content = parse_file(f)
        ACTIVETRANSMISSIONS += content

    c = c.replace("{ACTIVETRANSMISSIONS}", ACTIVETRANSMISSIONS)

def write_content():
    with open("blogcontent.c", "w+") as f:
        f.write(CONTENT)
        f.close()

def build():
    build_active_transmissions(CONTENT)
    #write_content()

if __name__ == '__main__':
    build()