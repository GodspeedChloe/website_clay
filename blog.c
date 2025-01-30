#define CLAY_EXTEND_CONFIG_RECTANGLE Clay_String link; bool cursorPointer;
#define CLAY_EXTEND_CONFIG_IMAGE Clay_String sourceURL;
#define CLAY_EXTEND_CONFIG_TEXT bool disablePointerEvents;
#define CLAY_IMPLEMENTATION

#include "./clay-0.12/clay.h"

double windowWidth = 1024, windowHeight = 768;
float modelPageOneZRotation = 0;

int font_count = 5;
const uint32_t FONT_ID_CUBE = 0;
const uint32_t FONT_ID_BAYONE = 1;
const uint32_t FONT_ID_SEGA = 2;
const uint32_t FONT_ID_PDARK = 3;
const uint32_t FONT_ID_EHSMB = 4;


Clay_Color almostBlack = {12, 15, 10, 255};
Clay_Color brightYellow = {251,255,18,255};
Clay_Color pinkRed = {255, 32, 110, 255};
Clay_Color brightAqua = {65, 234, 212, 255};
Clay_Color electricBlue = {0, 46, 255, 255};
Clay_Color white = {255, 255, 255, 255};
Clay_Color black = {0, 0, 0, 0};
Clay_Color orange = {255, 138, 0, 255};
Clay_Color darkTeal = {24, 90, 86, 255};

Clay_Sizing layoutExpand = {
    .width = CLAY_SIZING_GROW(),
    .height = CLAY_SIZING_GROW()
};

#define RAYLIB_VECTOR2_TO_CLAY_VECTOR2(vector) (Clay_Vector2) { .x = (vector).x, .y = (vector).y }


void SplashScreen(){

}

void renderBlogDesktop(uint32_t TITLE_FONT_ID){
    CLAY(
            CLAY_ID("OuterContainer"),
            CLAY_RECTANGLE({ .color = almostBlack }),
            CLAY_LAYOUT({
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                .sizing = layoutExpand,
                .padding = {16, 16}
            })
        ){
            CLAY(
                CLAY_ID("HeaderBar"),
                CLAY_RECTANGLE({ 
                    .color = black,
                    .cornerRadius = {8}
                }),
                CLAY_LAYOUT({
                    .sizing = {
                        .height = CLAY_SIZING_FIXED(90),
                        .width = CLAY_SIZING_GROW()
                    }
                })
            ){
                CLAY_TEXT(
                    CLAY_STRING("Chloe\'s Blog"),
                    CLAY_TEXT_CONFIG({
                        .fontId = TITLE_FONT_ID,
                        .fontSize = 46,
                        .textColor = orange
                    })
                );
            }
            CLAY(
                CLAY_ID("LowerContent"),
                CLAY_LAYOUT({
                    .sizing = layoutExpand,
                    .childGap = 10
                })
            ){
                CLAY(
                    CLAY_ID("Nav Left"),
                    CLAY_LAYOUT({
                        .sizing = {.width = CLAY_SIZING_PERCENT(0.1), .height = CLAY_SIZING_GROW()},
                        .padding = {16, 16}
                    }),
                    CLAY_RECTANGLE({
                                .color = orange,
                                .cornerRadius = {.topLeft = 16, .topRight = 0, .bottomLeft = 16, .bottomRight = 0},
                    })
                ){}
                CLAY(
                    CLAY_ID("Blog Content"),
                    CLAY_LAYOUT({
                        .sizing = layoutExpand,
                        .padding = {16, 16}
                    }),
                    CLAY_RECTANGLE({
                                .color = darkTeal,
                                .cornerRadius = {.topLeft = 0, .topRight = 16, .bottomLeft = 0, .bottomRight = 16},
                    })
                ){}
            }
        }
}

void renderBlogMobile(uint32_t TITLE_FONT_ID){
}

typedef struct
{
    Clay_Vector2 clickOrigin;
    Clay_Vector2 positionOrigin;
    bool mouseDown;
} ScrollbarData;

ScrollbarData scrollbarData = (ScrollbarData) {};

Clay_RenderCommandArray CreateLayout(bool mobileScreen, bool splashButtonPressed, int font_id) {

    Clay_BeginLayout(); 
    if (!mobileScreen){    renderBlogDesktop(font_id); }
    else{ renderBlogMobile(font_id); }
    if (splashButtonPressed){
        renderBlogMobile(0);
    }

    return Clay_EndLayout();
}

bool splashButtonPressed = true;
bool debugModeEnabled = true;


CLAY_WASM_EXPORT("UpdateDrawFrame") Clay_RenderCommandArray UpdateDrawFrame(float width, float height, float mouseWheelX, float mouseWheelY, float mousePositionX, float mousePositionY, bool isTouchDown, bool isMouseDown, bool arrowKeyDownPressedThisFrame, bool arrowKeyUpPressedThisFrame, bool dKeyPressedThisFrame, float deltaTime, int font_id) {
    windowWidth = width;
    windowHeight = height;
    Clay_SetLayoutDimensions((Clay_Dimensions) { width, height });


    if (dKeyPressedThisFrame) {
        debugModeEnabled = !debugModeEnabled;
        Clay_SetDebugModeEnabled(debugModeEnabled);
    }

    Clay__debugViewHighlightColor = (Clay_Color) {105,210,231, 120};

    Clay_SetPointerState((Clay_Vector2) {mousePositionX, mousePositionY}, isMouseDown || isTouchDown);

    if (!isMouseDown) {
        scrollbarData.mouseDown = false;
    }

    if (isMouseDown && !scrollbarData.mouseDown && Clay_PointerOver(Clay_GetElementId(CLAY_STRING("ScrollBar")))) {
        Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
        scrollbarData.clickOrigin = (Clay_Vector2) { mousePositionX, mousePositionY };
        scrollbarData.positionOrigin = *scrollContainerData.scrollPosition;
        scrollbarData.mouseDown = true;
    } else if (scrollbarData.mouseDown) {
        Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
        if (scrollContainerData.contentDimensions.height > 0) {
            Clay_Vector2 ratio = (Clay_Vector2) {
                scrollContainerData.contentDimensions.width / scrollContainerData.scrollContainerDimensions.width,
                scrollContainerData.contentDimensions.height / scrollContainerData.scrollContainerDimensions.height,
            };
            if (scrollContainerData.config.vertical) {
                scrollContainerData.scrollPosition->y = scrollbarData.positionOrigin.y + (scrollbarData.clickOrigin.y - mousePositionY) * ratio.y;
            }
            if (scrollContainerData.config.horizontal) {
                scrollContainerData.scrollPosition->x = scrollbarData.positionOrigin.x + (scrollbarData.clickOrigin.x - mousePositionX) * ratio.x;
            }
        }
    }

    if (arrowKeyDownPressedThisFrame) {
        Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
        if (scrollContainerData.contentDimensions.height > 0) {
            scrollContainerData.scrollPosition->y = scrollContainerData.scrollPosition->y - 50;
        }
    } else if (arrowKeyUpPressedThisFrame) {
        Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
        if (scrollContainerData.contentDimensions.height > 0) {
            scrollContainerData.scrollPosition->y = scrollContainerData.scrollPosition->y + 50;
        }
    }

    Clay_UpdateScrollContainers(isTouchDown, (Clay_Vector2) {mouseWheelX, mouseWheelY}, deltaTime);
    bool isMobileScreen = windowWidth < 750;
    if (debugModeEnabled) {
        isMobileScreen = windowWidth < 950;
    }
    return CreateLayout(isMobileScreen, splashButtonPressed, font_id);
    //----------------------------------------------------------------------------------
}


int main(void){
    return 0;
}
