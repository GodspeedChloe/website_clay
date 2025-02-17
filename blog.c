#define CLAY_EXTEND_CONFIG_RECTANGLE \
    Clay_String link;                \
    bool cursorPointer;
#define CLAY_EXTEND_CONFIG_IMAGE Clay_String sourceURL;
#define CLAY_EXTEND_CONFIG_TEXT bool disablePointerEvents;
#define CLAY_IMPLEMENTATION

#include "./clay-0.12/clay.h"
#include "blogcontent.h"

double windowWidth = 1024, windowHeight = 768;
float modelPageOneZRotation = 0;

int font_count = 4;
const uint32_t FONT_ID_CUBE = 0;
const uint32_t FONT_ID_BAYONE = 1;
const uint32_t FONT_ID_DEMODE = 2;
const uint32_t FONT_ID_ROBOTO = 3;

Clay_Color almostBlack = {12, 15, 10, 255};
Clay_Color brightYellow = {251, 255, 18, 255};
Clay_Color pinkRed = {255, 32, 110, 255};
Clay_Color brightAqua = {65, 234, 212, 255};
Clay_Color electricBlue = {0, 46, 255, 255};
Clay_Color white = {255, 255, 255, 255};
Clay_Color black = {1, 0, 0, 0};
Clay_Color orange = {255, 138, 0, 255};
Clay_Color darkTeal = {24, 90, 86, 255};

Clay_Sizing layoutExpand = {
    .width = CLAY_SIZING_GROW(),
    .height = CLAY_SIZING_GROW()};

uint32_t CURRCONTENTINDEX = 0;

#define SECTIONCOUNT 3

char CONTENTINDEXES[SECTIONCOUNT][22] = {"Active\nTransmission", "Expanding the Lexicon", "Test"};

#define RAYLIB_VECTOR2_TO_CLAY_VECTOR2(vector) \
    (Clay_Vector2) { .x = (vector).x, .y = (vector).y }

void intToStr(int N, char *str)
{
    int i = 0;

    // Save the copy of the number for sign
    int sign = N;

    // If the number is negative, make it positive
    if (N < 0)
        N = -N;

    // Extract digits from the number and add them to the
    // string
    while (N > 0)
    {

        // Convert integer digit to character and store
        // it in the str
        str[i++] = N % 10 + '0';
        N /= 10;
    }

    // If the number was negative, add a minus sign to the
    // string
    if (sign < 0)
    {
        str[i++] = '-';
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string to get the correct order
    for (int j = 0, k = i - 1; j < k; j++, k--)
    {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}

Clay_String genFPSString(char fps[9])
{
    return (Clay_String){
        .length = (int32_t)9,
        .chars = fps};
}

void HandleContentSectionInteraction(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData)
{
    if (pointerInfo.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
    {
        CURRCONTENTINDEX = (uint32_t)userData;
    }
}

void renderSplashScreen()
{
    CLAY(
        CLAY_ID("Splash"),
        CLAY_LAYOUT({.layoutDirection = CLAY_TOP_TO_BOTTOM,
                     .sizing = {CLAY_SIZING_GROW(), CLAY_SIZING_GROW()},
                     .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}}),
        CLAY_RECTANGLE({.color = pinkRed})) {
            CLAY_TEXT(
                CLAY_STRING("I HATE WEB SCRAPERS"),
                CLAY_TEXT_CONFIG({.fontId = FONT_ID_ROBOTO,
                .fontSize = 40,
                .textColor = white})
            );
        }
}

void renderContentSelection()
{
    int i = 0;
    while (i < SECTIONCOUNT)
    {
        CLAY(
            CLAY_ID(CONTENTINDEXES[i]),
            CLAY_LAYOUT({.layoutDirection = CLAY_TOP_TO_BOTTOM,
                         .sizing = {CLAY_SIZING_GROW(), CLAY_SIZING_FIXED(70)},
                         .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}}),
            CLAY_RECTANGLE({
                .color = almostBlack,
                .cornerRadius = {.topLeft = 16, .topRight = 0, .bottomLeft = 16, .bottomRight = 0},
            }))
        {
            CLAY_TEXT(
                CLAY_STRING(CONTENTINDEXES[i]),
                CLAY_TEXT_CONFIG({.fontId = FONT_ID_ROBOTO,
                                  .fontSize = 12,
                                  .textColor = white,
                                }));
        }
        i++;
    }
}

void renderBlogDesktop(uint32_t TITLE_FONT_ID, char fps[9])
{

    CLAY(
        CLAY_ID("OuterContainer"),
        CLAY_RECTANGLE({.color = almostBlack}),
        CLAY_LAYOUT({.layoutDirection = CLAY_TOP_TO_BOTTOM,
                     .sizing = layoutExpand,
                     .padding = {16, 40}}))
    {
        CLAY(
            CLAY_ID("HeaderBar"),
            CLAY_RECTANGLE({.color = black,
                            .cornerRadius = {8}}),
            CLAY_LAYOUT({.sizing = {
                             .height = CLAY_SIZING_FIXED(90),
                             .width = CLAY_SIZING_GROW()}}))
        {
            CLAY_TEXT(
                CLAY_STRING("Chloe\'s Website"),
                CLAY_TEXT_CONFIG({.fontId = TITLE_FONT_ID,
                                  .fontSize = 46,
                                  .textColor = white}));
        }
        CLAY(
            CLAY_ID("LowerContent"),
            CLAY_LAYOUT({.sizing = layoutExpand,
                         .childGap = 10}))
        {
            CLAY(
                CLAY_ID("Nav Left"),
                CLAY_LAYOUT({.layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = {.width = CLAY_SIZING_PERCENT(0.1), .height = CLAY_SIZING_GROW()}, .padding = {10, 10}, .childGap = 10}),
                CLAY_RECTANGLE({
                    .color = darkTeal,
                    .cornerRadius = {.topLeft = 16, .topRight = 0, .bottomLeft = 16, .bottomRight = 0},
                }))
            {
                renderContentSelection();
            }
            CLAY(
                CLAY_ID("Blog Content"),
                CLAY_LAYOUT({.sizing = layoutExpand,
                             .padding = {16, 16}}),
                CLAY_RECTANGLE({
                    .color = almostBlack,
                    .cornerRadius = {.topLeft = 0, .topRight = 0, .bottomLeft = 0, .bottomRight = 0},
                }))
            {
            }
        }
        CLAY(
            CLAY_ID("FPS counter"),
            CLAY_LAYOUT({.layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = {.width = CLAY_SIZING_FIXED(90), .height = CLAY_SIZING_FIXED(20)}, .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}}),
            CLAY_RECTANGLE({.color = brightYellow}))
        {
            CLAY_TEXT(
                genFPSString(fps),
                CLAY_TEXT_CONFIG({.fontId = FONT_ID_ROBOTO,
                                  .fontSize = 12,
                                  .textColor = almostBlack}));
        }
    }
}

void renderBlogMobile(uint32_t TITLE_FONT_ID, char fps[9])
{
}

typedef struct
{
    Clay_Vector2 clickOrigin;
    Clay_Vector2 positionOrigin;
    bool mouseDown;
} ScrollbarData;

ScrollbarData scrollbarData = (ScrollbarData){};

Clay_RenderCommandArray CreateLayout(bool mobileScreen, bool splashButtonPressed, int font_id, float deltaTime, bool isSplash)
{

    uint32_t fps = (uint32_t)(1 / (deltaTime));

    int i = 10;
    int fps_length = 1;
    while (fps / 10 != 0)
    {
        fps_length++;
        i *= 10;
    }

    char fps_fill[fps_length];
    intToStr(fps, fps_fill);

    int fps_str_length = 5 + fps_length;
    char fps_string[fps_str_length];
    fps_string[0] = 'F';
    fps_string[1] = 'P';
    fps_string[2] = 'S';
    fps_string[3] = ':';
    fps_string[4] = ' ';

    i = 0;
    while (i <= fps_length)
    {
        fps_string[5 + i] = fps_fill[i];
        i++;
    }

    Clay_BeginLayout();
    if (isSplash)
    {
        renderSplashScreen();
    }
    else
    {
        if (!mobileScreen)
        {
            renderBlogDesktop(font_id, fps_string);
        }
        else
        {
            renderBlogMobile(font_id, fps_string);
        }
        if (splashButtonPressed)
        {
            renderBlogMobile(0, fps_string);
        }
    }
    return Clay_EndLayout();
}

bool splashButtonPressed = true;
bool debugModeEnabled = true;

CLAY_WASM_EXPORT("UpdateDrawFrame")
Clay_RenderCommandArray UpdateDrawFrame(float width, float height, float mouseWheelX, float mouseWheelY, float mousePositionX, float mousePositionY, bool isTouchDown, bool isMouseDown, bool arrowKeyDownPressedThisFrame, bool arrowKeyUpPressedThisFrame, bool dKeyPressedThisFrame, float deltaTime, int font_id, bool isSplash)
{
    windowWidth = width;
    windowHeight = height;
    Clay_SetLayoutDimensions((Clay_Dimensions){width, height});

    if (dKeyPressedThisFrame)
    {
        debugModeEnabled = !debugModeEnabled;
        Clay_SetDebugModeEnabled(debugModeEnabled);
    }

    Clay__debugViewHighlightColor = (Clay_Color){105, 210, 231, 120};

    Clay_SetPointerState((Clay_Vector2){mousePositionX, mousePositionY}, isMouseDown || isTouchDown);

    if (!isMouseDown)
    {
        scrollbarData.mouseDown = false;
    }

    if (isMouseDown && !scrollbarData.mouseDown && Clay_PointerOver(Clay_GetElementId(CLAY_STRING("ScrollBar"))))
    {
        Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
        scrollbarData.clickOrigin = (Clay_Vector2){mousePositionX, mousePositionY};
        scrollbarData.positionOrigin = *scrollContainerData.scrollPosition;
        scrollbarData.mouseDown = true;
    }
    else if (scrollbarData.mouseDown)
    {
        Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
        if (scrollContainerData.contentDimensions.height > 0)
        {
            Clay_Vector2 ratio = (Clay_Vector2){
                scrollContainerData.contentDimensions.width / scrollContainerData.scrollContainerDimensions.width,
                scrollContainerData.contentDimensions.height / scrollContainerData.scrollContainerDimensions.height,
            };
            if (scrollContainerData.config.vertical)
            {
                scrollContainerData.scrollPosition->y = scrollbarData.positionOrigin.y + (scrollbarData.clickOrigin.y - mousePositionY) * ratio.y;
            }
            if (scrollContainerData.config.horizontal)
            {
                scrollContainerData.scrollPosition->x = scrollbarData.positionOrigin.x + (scrollbarData.clickOrigin.x - mousePositionX) * ratio.x;
            }
        }
    }

    if (arrowKeyDownPressedThisFrame)
    {
        Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
        if (scrollContainerData.contentDimensions.height > 0)
        {
            scrollContainerData.scrollPosition->y = scrollContainerData.scrollPosition->y - 50;
        }
    }
    else if (arrowKeyUpPressedThisFrame)
    {
        Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
        if (scrollContainerData.contentDimensions.height > 0)
        {
            scrollContainerData.scrollPosition->y = scrollContainerData.scrollPosition->y + 50;
        }
    }

    Clay_UpdateScrollContainers(isTouchDown, (Clay_Vector2){mouseWheelX, mouseWheelY}, deltaTime);
    bool isMobileScreen = windowWidth < 750;
    if (debugModeEnabled)
    {
        isMobileScreen = windowWidth < 950;
    }
    return CreateLayout(isMobileScreen, splashButtonPressed, font_id, deltaTime, isSplash);
    //----------------------------------------------------------------------------------
}

int main(void)
{
    return 0;
}
