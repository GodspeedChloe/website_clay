import os
import xml.etree.ElementTree as ET

CONTENT = """
#include "./clay-0.12/clay.h"
#include "./blogcontent.h"

const uint32_t FONT_ID_ETB_ROMAN_ = 4;
Clay_TextElementConfig dateTextConfig  = (Clay_TextElementConfig) { .fontId = FONT_ID_ETB_ROMAN_, .fontSize = 18, .textColor = {255, 255, 255, 255}};
Clay_TextElementConfig titleTextConfig = (Clay_TextElementConfig) { .fontId = FONT_ID_ETB_ROMAN_, .fontSize = 30, .textColor = {255, 255, 255, 255}};
Clay_TextElementConfig bodyTextConfig  = (Clay_TextElementConfig) { .fontId = FONT_ID_ETB_ROMAN_, .fontSize = 20, .textColor = {255, 255, 255, 255}};
Clay_TextElementConfig wordTextConfig = (Clay_TextElementConfig) { .fontId = FONT_ID_ETB_ROMAN_, .fontSize = 23, .textColor = {255, 255, 255, 255}};
Clay_TextElementConfig defTextConfig  = (Clay_TextElementConfig) { .fontId = FONT_ID_ETB_ROMAN_, .fontSize = 20, .textColor = {255, 138, 0, 255}};


void renderBlogPosts(){
    {ACTIVETRANSMISSIONS}
}

void renderLexiconPosts(){
    {LEXICON}
}"""

date_format = "CLAY_TEXT"

def build_date(string):
    return "    CLAY_TEXT(CLAY_STRING(\""+string+"\"),&dateTextConfig);\n"

def build_title(string):
    return "    CLAY_TEXT(CLAY_STRING(\""+string+"\"),&titleTextConfig);\n"

def build_body(string):
    return "    CLAY_TEXT(CLAY_STRING(\""+string+"\"),&bodyTextConfig);\n"

def build_word(string):
    return "    CLAY_TEXT(CLAY_STRING(\""+string+"\"),&wordTextConfig);\n"

def build_def(string):
    return "    CLAY_TEXT(CLAY_STRING(\""+string+"\"),&defTextConfig);\n"

def parse_file(file):
    lines = []
    content =   "CLAY(CLAY_ID(\"POST: "+file+"\"),\n" \
                "    CLAY_LAYOUT({.layoutDirection = CLAY_TOP_TO_BOTTOM,\n" \
                "                 .childGap=20})\n" \
                "   ){\n{TEXT}  }\n"
    with open(file, "r+") as f:
        tree = ET.parse(f)
        root = tree.getroot()
        TEXT = ""
        for item in root.findall('.'):
            for child in item:
                if child.tag == "date":
                    TEXT += build_date(child.text)
                elif child.tag == "title":
                    TEXT += build_title(child.text)
                elif child.tag == "content":
                    TEXT += build_body(child.text)
                elif child.tag == "word":
                    TEXT += build_word(child.text)
                elif child.tag == "def":
                    TEXT += build_def(child.text)
    
    content = content.replace("{TEXT}", TEXT)             
    return content

def sort_files(fs, r):
    return sorted(fs, key=lambda x: x[x.rindex("/"):], reverse=r)

def post_break():
    return "CLAY(CLAY_LAYOUT({.sizing = {CLAY_SIZING_FIXED(20), CLAY_SIZING_FIXED(20)}}),CLAY_RECTANGLE({.color={24, 90, 86, 255},.cornerRadius={3,3,3,3}})){}\n"

def build_active_transmissions(c):
    ACTIVETRANSMISSIONS = ""
    files = []
    with os.scandir("./active_transmissions") as it:
        for entry in it:
            files.append(str(entry.path))
    files = sort_files(files, True)
    for f in files:
        print("Parsing file: "+f)
        content = post_break()
        content += parse_file(f)
        ACTIVETRANSMISSIONS += content
    return c.replace("{ACTIVETRANSMISSIONS}", ACTIVETRANSMISSIONS)

def build_lexicon(c):
    LEXICON = ""
    files = []
    with os.scandir("./lexicon") as it:
        for entry in it:
            files.append(str(entry.path))
    files = sort_files(files, False)
    for f in files:
        print("Parsing file: "+f)
        content = parse_file(f)
        LEXICON += content
    return c.replace("{LEXICON}", LEXICON)
    
def write_content(c):
    with open("blogcontent.c", "w+") as f:
        f.write(c)
        f.close()

def build():
    write_content(build_lexicon(build_active_transmissions(CONTENT)))

if __name__ == '__main__':
    build()